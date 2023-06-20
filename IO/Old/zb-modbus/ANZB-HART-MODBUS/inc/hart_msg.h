#ifndef __HART_MSG_DEF_H__
#define __HART_MSG_DEF_H__

////////////////////////////////////////////////////////////////////////////////
//
// HART message format
// This is just an excerpt from unknown internet source.
// Use it at your own risk. I don't have any official spec for this.
// -hkim-
//
// DO NOT TRUST THIS. THIS IS JUST A COPY FROM INTERNET
//
// | PREAMBLE | START | ADDR | [EXP] | COM | BCNT | [STATUS] | [DATA] | CHK |
//
// PREAMBLE   :   between 5 and 20 bytes. all 0xff
//
// START      :   1 byte. may have one of several values, indicating the type of message
//
// ADDR       :   either 1 byte or 5 bytes
//                master : 1 bit , 1 for primary master, 0 for secondary master
//                slave addr : 4 bit in short frame format
//                             38 bit in long frame format
//
// EXP        :   optional. up to 3 additional bytes.
//                bit 5 and 6 of START byte indicates the number of EXP bytes
//
// COM        :   command. 1 byte
//
// BCNT       :   byte count. contains the number of bytes to follow in status
//                and data bytes
//
// STATUS     :   optional. 2 bytes when present. only in slave response
//
// DATA       :   optional. 0 to 253 bytes formally.
//
// CHK        :   checksum. 1 byte. XORed from START byte to the end of data.
////////////////////////////////////////////////////////////////////////////////

#define HART_PREAMBLE_MIN_LENGTH          5   // Should be 5
#define HART_PREAMBLE_MAX_LENGTH          20

#define HART_ADDR_LEN_IN_SHORT            1
#define HART_ADDR_LEN_IN_LONG             5

#define HART_MAX_EXPANSION                3

#define HART_STATUS_LENGTH                2

#define HART_MAX_DATA_LENGTH              253

#define HART_MSG_START_FROM_MASTER_TO_SLAVE       0x82
#define HART_MSG_START_FROM_SLAVE_TO_MASTER       0x06
#define HART_MSG_START_FROM_SLAVE_TO_MASTER_LONG  0x86

typedef unsigned char     hart_data_t;

////////////////////////////////////////////////////////////////////////////////
//
// HART message parser
//
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
  HartMessageParsing_Pass,
  HartMessageParsing_Error,
  HartMessageParsing_Complete,
} HartMessageParsingStatus;

typedef enum
{
  HartMessageAddressFormat_Short,
  HartMessageAddressFormat_Long,
} HartMessageAddressFormat;

typedef enum
{
  HartMessageType_MasterToSlave,
  HartMessageType_SlaveToMaster,
  HartMessageType_BurstFromMaster,
} HartMessageType;

typedef enum
{
  HartMessageErrorCode_OK,
  HartMessageErrorCode_OutOfBound,
  HartMessageErrorCode_ByteCountInSlaveResponse,
  HartMessageErrorCode_InvalidPreambleInBegin,
  HartMessageErrorCode_NotEnoughPreamble,
  HartMessageErrorCode_ExcessivePreamble,
  HartMessageErrorCode_UnknownStartDelimeter,
} HartMessageErrorCode;

typedef struct __hart_message_parser HartMessageParser;

typedef HartMessageParsingStatus (*hart_message_state)(HartMessageParser* parser, hart_data_t rxb);

struct __hart_message_parser
{
  // message parsing state
  hart_message_state        parsing_state;
  volatile uint16_t         rx_ndx;         
  volatile uint16_t         rx_buf_size;
  volatile hart_data_t*     rx_buf_ptr;

  // temporary counter depending on message context
  uint16_t                            state_dependent_cnt;
  volatile uint8_t                    exp_cnt;
  volatile uint8_t                    byte_cnt;
  volatile uint8_t                    data_cnt;
  volatile uint8_t                    csum;
  volatile HartMessageAddressFormat   address_fmt;
  volatile HartMessageType            msg_type;

  // protocol field pointers
  volatile hart_data_t*     start_ptr;
  volatile hart_data_t*     addr_ptr;
  volatile hart_data_t*     exp_ptr;
  volatile hart_data_t*     cmd_ptr;
  volatile hart_data_t*     status_ptr;
  volatile hart_data_t*     data_ptr;
  volatile float            Current;
  volatile uint8_t          UnitId[4];
  volatile float            ProsData[4];

  // error diagnostic
  volatile HartMessageErrorCode      err_msg;
};


extern void hart_msg_parser_init(
    HartMessageParser* parser,            // parser contex block
    volatile hart_data_t* rx_buf,         // preallocated rx buffer
    uint16_t rx_buf_size);                // rx buffer size


extern void hart_msg_parser_reset(HartMessageParser* parser);
extern uint8_t hart_msg_calc_csum(const uint8_t* buf, uint16_t len);
extern HartMessageParsingStatus hart_msg_parser_handle_byte(HartMessageParser* parser, hart_data_t rxb);


////////////////////////////////////////////////////////////////////////////////
//
// HART message encoder
//
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  volatile hart_data_t*       tx_buf;
  uint16_t                    tx_buf_size;
  uint16_t                    tx_ndx;
  uint8_t                     preamble_len;
} HartMessageEncoder;

extern void hart_msg_encoder_init(HartMessageEncoder* encoder, volatile uint8_t* tx_buf,  uint16_t tx_buf_size);
extern void hart_msg_encoder_reset(HartMessageEncoder* encoder);
extern uint8_t hart_msg_encoder_preamble(HartMessageEncoder* encoder, uint8_t num_preamble);
extern uint8_t hart_msg_encoder_short_start(HartMessageEncoder* encoder, uint8_t start, uint8_t addr, uint8_t cmd);
extern uint8_t hart_msg_encoder_long_start(HartMessageEncoder* encoder, uint8_t start, uint8_t* addr, uint8_t cmd);
extern uint8_t hart_msg_encoder_status_data(HartMessageEncoder* encoder, uint8_t* status, uint8_t* data, uint8_t data_len);
extern uint8_t hart_msg_encoder_data(HartMessageEncoder* encoder, uint8_t* data, uint8_t data_len);
extern uint8_t hart_msg_encoder_calc_csum(HartMessageEncoder* encoder);

#endif //!__HART_MSG_DEF_H__
