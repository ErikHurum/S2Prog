#include <stdio.h>
#include "hart_common.h"
#include "hart_msg.h"
#include "externals.h"

////////////////////////////////////////////////////////////////////////////////
//
// internal defines
//
////////////////////////////////////////////////////////////////////////////////
#define HART_PARSER_ERR(__parser__, __err_msg__)                      \
  __parser__->err_msg   = __err_msg__;                                \
  hart_msg_parser_move_state(__parser__, hart_msg_state_blackhole);   \
  return HartMessageParsing_Error;

#define HART_PUT_RX_DATA(__parser__, __rxb__)                           \
  if(hart_msg_put_rx_data(__parser__, __rxb__) == 0)                    \
  {                                                                     \
    hart_msg_parser_move_state(__parser__, hart_msg_state_blackhole);   \
    return HartMessageParsing_Error;                                    \
  }

#define HART_ENCODER_PUT(__encoder__, __d__)                  \
  if(hart_msg_encoder_put_data(__encoder__, __d__) != 1)     \
  {                                                           \
    return 0;                                                 \
  }

#define HART_MARK_DPTR(parser, ptr)\
  ptr = &(parser->rx_buf_ptr[parser->rx_ndx]);



////////////////////////////////////////////////////////////////////////////////
//
// private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static inline HartMessageParsingStatus hart_msg_parser_move_state(HartMessageParser *parser, hart_message_state state);

static HartMessageParsingStatus hart_msg_state_begin(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_preamble(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_start_char(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_address(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_expansion(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_command(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_bytecount(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_status(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_data(HartMessageParser *parser, hart_data_t rxb);
static HartMessageParsingStatus hart_msg_state_checksum(HartMessageParser *parser, hart_data_t rxb);

static HartMessageParsingStatus hart_msg_state_blackhole(HartMessageParser *parser, hart_data_t rxb);

////////////////////////////////////////////////////////////////////////////////
//
// utilities
//
////////////////////////////////////////////////////////////////////////////////
static inline HartMessageParsingStatus
hart_msg_parser_move_state(HartMessageParser *parser, hart_message_state state) {
	parser->parsing_state = state;

	return HartMessageParsing_Pass;
}

static inline HartMessageParsingStatus
hart_msg_move_and_invoke_state(HartMessageParser *parser, hart_message_state state, hart_data_t rxb) {
	hart_msg_parser_move_state(parser, state);

	return state(parser, rxb);
}


/*
 *
 * returns
 * 1 ok
 * 0 when buffer overflow
 *
 */
static inline int
hart_msg_put_rx_data(HartMessageParser *parser, hart_data_t rxb) {
	uint16_t      r_ndx     = parser->rx_ndx;
	uint16_t      buf_size  = parser->rx_buf_size;
	volatile hart_data_t *buf       = parser->rx_buf_ptr;

	if (r_ndx < buf_size) {
		buf[r_ndx] = rxb;
		r_ndx++;
		parser->rx_ndx = r_ndx;
		return 1;
	}

	parser->err_msg = HartMessageErrorCode_OutOfBound;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
//
// private parsing state machine
//
////////////////////////////////////////////////////////////////////////////////
static HartMessageParsingStatus
hart_msg_state_begin(HartMessageParser *parser, hart_data_t rxb) {
	if (rxb != 0xff) {
		HART_PARSER_ERR(parser, HartMessageErrorCode_InvalidPreambleInBegin);
	}

	parser->state_dependent_cnt   = 1;

	return hart_msg_parser_move_state(parser, hart_msg_state_preamble);
}

static HartMessageParsingStatus
hart_msg_state_preamble(HartMessageParser *parser, hart_data_t rxb) {
	if (rxb != 0xff) {
		if (parser->state_dependent_cnt >= HART_PREAMBLE_MIN_LENGTH) {
			// ok. we can accept it as start byte
			return hart_msg_move_and_invoke_state(parser, hart_msg_state_start_char, rxb);
		}

		HART_PARSER_ERR(parser, HartMessageErrorCode_NotEnoughPreamble);
	}

	parser->state_dependent_cnt++;

	if (parser->state_dependent_cnt > HART_PREAMBLE_MAX_LENGTH) {
		// excessive preamble
		HART_PARSER_ERR(parser, HartMessageErrorCode_ExcessivePreamble);
	}
	return HartMessageParsing_Pass;
}

static HartMessageParsingStatus
hart_msg_state_start_char(HartMessageParser *parser, hart_data_t rxb) {
	HART_MARK_DPTR(parser, parser->start_ptr);

	HART_PUT_RX_DATA(parser, rxb);

	//
	// a) extract out type of message
	//      master -> slave
	//      slave -> master
	//      burst from slave
	// b) extract out address format
	//      short frame
	//      long frame
	// c) extract out expansion count
	//
	if (rxb == HART_MSG_START_FROM_MASTER_TO_SLAVE) {
		// mater to slave delimiter
		parser->msg_type              = HartMessageType_MasterToSlave;
		parser->address_fmt           = HartMessageAddressFormat_Long;
	} else if (rxb == HART_MSG_START_FROM_SLAVE_TO_MASTER) {
		// slave to master delimiter
		parser->msg_type              = HartMessageType_SlaveToMaster;
		parser->address_fmt           = HartMessageAddressFormat_Short;
	} else if (rxb == HART_MSG_START_FROM_SLAVE_TO_MASTER_LONG) {
		// slave to master delimiter
		parser->msg_type              = HartMessageType_SlaveToMaster;
		parser->address_fmt           = HartMessageAddressFormat_Long;
		{
			char FloatBuf[4] = { parser->rx_buf_ptr[13], parser->rx_buf_ptr[12], parser->rx_buf_ptr[11], parser->rx_buf_ptr[10] };
			parser->Current             = *((float *)FloatBuf);
		}
		for (int i = 0; i < 4; i++) {
			int Offset = i * 5;
			char FloatBuf[4] = { parser->rx_buf_ptr[18 + Offset], parser->rx_buf_ptr[17 + Offset], parser->rx_buf_ptr[16 + Offset], parser->rx_buf_ptr[15 + Offset] };
			float *ProsVal              = (float *)FloatBuf;
			parser->UnitId[i] = parser->rx_buf_ptr[14 + Offset];
			parser->ProsData[i] = *ProsVal;
		}
	} else {
		HART_PARSER_ERR(parser, HartMessageErrorCode_UnknownStartDelimeter);
	}

	parser->state_dependent_cnt   = 0;

	//
	// XXX FIXME burst from slave is not yet implemented
	//

	//
	// XXX FIXME EXP is not yet implemented
	//
	parser->exp_cnt               = 0;

	return hart_msg_parser_move_state(parser, hart_msg_state_address);
}

static HartMessageParsingStatus
hart_msg_state_address(HartMessageParser *parser, hart_data_t rxb) {
	if (parser->state_dependent_cnt == 0) {
		HART_MARK_DPTR(parser, parser->addr_ptr);
	}

	HART_PUT_RX_DATA(parser, rxb);

	parser->state_dependent_cnt++;

	switch (parser->address_fmt) {
	case HartMessageAddressFormat_Long:
		if (parser->state_dependent_cnt != 5) {
			return HartMessageParsing_Pass;
		}

		//
		// fall through
		//
	case HartMessageAddressFormat_Short:
		if (parser->exp_cnt == 0) {
			parser->state_dependent_cnt = 0;
			return hart_msg_parser_move_state(parser, hart_msg_state_command);
		} else {
			parser->state_dependent_cnt = 0;
			return hart_msg_parser_move_state(parser, hart_msg_state_expansion);
		}
		break;
	}

	return HartMessageParsing_Pass;
}

static HartMessageParsingStatus
hart_msg_state_expansion(HartMessageParser *parser, hart_data_t rxb) {
	if (parser->state_dependent_cnt == 0) {
		HART_MARK_DPTR(parser, parser->exp_ptr);
	}

	HART_PUT_RX_DATA(parser, rxb);

	parser->state_dependent_cnt++;

	if (parser->state_dependent_cnt == parser->exp_cnt) {
		return hart_msg_parser_move_state(parser, hart_msg_state_command);
	}

	return HartMessageParsing_Pass;
}

static HartMessageParsingStatus
hart_msg_state_command(HartMessageParser *parser, hart_data_t rxb) {
	HART_MARK_DPTR(parser, parser->cmd_ptr);

	HART_PUT_RX_DATA(parser, rxb);

	return hart_msg_parser_move_state(parser, hart_msg_state_bytecount);
}

static HartMessageParsingStatus
hart_msg_state_bytecount(HartMessageParser *parser, hart_data_t rxb) {
	if (parser->msg_type == HartMessageType_SlaveToMaster && rxb < 2) {
		HART_PARSER_ERR(parser, HartMessageErrorCode_ByteCountInSlaveResponse);
	}

	parser->byte_cnt = rxb;

	HART_PUT_RX_DATA(parser, rxb);

	//
	// response from slave
	// has status word
	//
	if (parser->msg_type == HartMessageType_SlaveToMaster) {
		parser->state_dependent_cnt = 0;
		return hart_msg_parser_move_state(parser, hart_msg_state_status);
	}

	//
	// either from master or burst from slave
	// no status word
	//
	parser->status_ptr  = NULL;
	if (parser->byte_cnt == 0) {
		// no data
		parser->data_cnt    = 0;
		parser->data_ptr    = NULL;
		return hart_msg_parser_move_state(parser, hart_msg_state_checksum);
	}

	// some data
	parser->data_cnt = parser->byte_cnt;
	parser->state_dependent_cnt = 0;
	return hart_msg_parser_move_state(parser, hart_msg_state_data);
}

static HartMessageParsingStatus
hart_msg_state_status(HartMessageParser *parser, hart_data_t rxb) {
	if (parser->state_dependent_cnt == 0) {
		HART_MARK_DPTR(parser, parser->status_ptr);
	}

	HART_PUT_RX_DATA(parser, rxb);

	parser->state_dependent_cnt++;

	if (parser->state_dependent_cnt == 2) {
		// no data
		if (parser->byte_cnt == 2) {
			parser->data_cnt    = 0;
			parser->data_ptr    = NULL;
			return hart_msg_parser_move_state(parser, hart_msg_state_checksum);
		}

		// some data
		parser->data_cnt = parser->byte_cnt - 2;
		parser->state_dependent_cnt = 0;
		return hart_msg_parser_move_state(parser, hart_msg_state_data);
	}
	return HartMessageParsing_Pass;
}

static HartMessageParsingStatus
hart_msg_state_data(HartMessageParser *parser, hart_data_t rxb) {
	if (parser->state_dependent_cnt == 0) {
		HART_MARK_DPTR(parser, parser->data_ptr);
	}

	HART_PUT_RX_DATA(parser, rxb);

	parser->state_dependent_cnt++;
	if (parser->state_dependent_cnt == parser->data_cnt) {
		return hart_msg_parser_move_state(parser, hart_msg_state_checksum);
	}

	return HartMessageParsing_Pass;
}

static HartMessageParsingStatus
hart_msg_state_checksum(HartMessageParser *parser, hart_data_t rxb) {
	parser->csum = rxb;
	return HartMessageParsing_Complete;
}

static HartMessageParsingStatus
hart_msg_state_blackhole(HartMessageParser *parser, hart_data_t rxb) {
	return HartMessageParsing_Pass;
}

////////////////////////////////////////////////////////////////////////////////
//
// parser public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_msg_parser_init(HartMessageParser *parser, volatile hart_data_t *rx_buf, uint16_t rx_buf_size) {
	parser->rx_buf_ptr    = rx_buf;
	parser->rx_buf_size   = rx_buf_size;

	hart_msg_parser_reset(parser);
}


HartMessageParsingStatus
hart_msg_parser_handle_byte(HartMessageParser *parser, hart_data_t rxb) {
	return parser->parsing_state(parser, rxb);
}

void
hart_msg_parser_reset(HartMessageParser *parser) {
	parser->start_ptr             = NULL;
	parser->addr_ptr              = NULL;
	parser->exp_ptr               = NULL;
	parser->cmd_ptr               = NULL;
	parser->status_ptr            = NULL;
	parser->data_ptr              = NULL;

	parser->state_dependent_cnt   = 0;
	parser->exp_cnt               = 0;
	parser->byte_cnt              = 0;
	parser->data_cnt              = 0;
	parser->csum                  = 0;
	parser->address_fmt           = HartMessageAddressFormat_Short;
	parser->msg_type              = HartMessageType_SlaveToMaster;

	parser->rx_ndx                = 0;

	parser->err_msg               = HartMessageErrorCode_OK;

	hart_msg_parser_move_state(parser, hart_msg_state_begin);
}

uint8_t hart_msg_calc_csum(const uint8_t *buf, uint16_t len) {
	uint8_t     csum = 0;
	for (uint16_t i = 0; i < len; i++) {
		csum = csum ^ buf[i];
	}
	return csum;
}

////////////////////////////////////////////////////////////////////////////////
//
// encoder utilities
//
////////////////////////////////////////////////////////////////////////////////
/*
 * returns
 *
 * 1 on ok
 * 0 on buffer overflow
 *
 */
static inline uint8_t
hart_msg_encoder_put_data(HartMessageEncoder *encoder, hart_data_t d) {
	if (encoder->tx_ndx >= encoder->tx_buf_size) {
		return 0;
	}
	encoder->tx_buf[encoder->tx_ndx] = d;
	encoder->tx_ndx++;

	return 1;
}


////////////////////////////////////////////////////////////////////////////////
//
// encoder public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_msg_encoder_init(HartMessageEncoder *encoder, volatile uint8_t *tx_buf,  uint16_t tx_buf_size) {
	encoder->tx_buf         = tx_buf;
	encoder->tx_buf_size    = tx_buf_size;

	hart_msg_encoder_reset(encoder);
}

void
hart_msg_encoder_reset(HartMessageEncoder *encoder) {
	encoder->tx_ndx         = 0;
	encoder->preamble_len   = 0;
}

uint8_t
hart_msg_encoder_preamble(HartMessageEncoder *encoder, uint8_t num_preamble) {
	uint8_t     i;

	encoder->preamble_len   = num_preamble;

	for (i = 0; i < num_preamble; i++) {
		HART_ENCODER_PUT(encoder, 0xff);
	}
	return 1;
}

uint8_t
hart_msg_encoder_short_start(HartMessageEncoder *encoder, uint8_t start, uint8_t addr, uint8_t cmd) {
	HART_ENCODER_PUT(encoder, start);
	HART_ENCODER_PUT(encoder, addr);
	HART_ENCODER_PUT(encoder, cmd);

	return 1;
}

uint8_t
hart_msg_encoder_long_start(HartMessageEncoder *encoder, uint8_t start, uint8_t *addr, uint8_t cmd) {
	uint8_t   i;

	HART_ENCODER_PUT(encoder, start);

	for (i = 0; i < 5; i++) {
		HART_ENCODER_PUT(encoder, addr[i]);
	}

	HART_ENCODER_PUT(encoder, cmd);

	return 1;
}

uint8_t
hart_msg_encoder_status_data(HartMessageEncoder *encoder, uint8_t *status, uint8_t *data, uint8_t data_len) {
	uint8_t   bcnt,
		i;

	bcnt = 2 + data_len;

	HART_ENCODER_PUT(encoder, bcnt);

	HART_ENCODER_PUT(encoder, status[0]);
	HART_ENCODER_PUT(encoder, status[1]);

	for (i = 0; i < data_len; i++) {
		HART_ENCODER_PUT(encoder, data[i]);
	}

	return 1;
}

uint8_t
hart_msg_encoder_data(HartMessageEncoder *encoder, uint8_t *data, uint8_t data_len) {
	uint8_t   bcnt,
		i;

	bcnt = data_len;

	HART_ENCODER_PUT(encoder, bcnt);

	for (i = 0; i < data_len; i++) {
		HART_ENCODER_PUT(encoder, data[i]);
	}

	return 1;
}

uint8_t
hart_msg_encoder_calc_csum(HartMessageEncoder *encoder) {
	uint8_t   csum;

	csum = hart_msg_calc_csum((const uint8_t *)&encoder->tx_buf[encoder->preamble_len], encoder->tx_ndx - encoder->preamble_len);

	HART_ENCODER_PUT(encoder, csum);

	return 1;
}
