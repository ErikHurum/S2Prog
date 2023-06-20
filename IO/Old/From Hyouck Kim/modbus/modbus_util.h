/*
 * modbus_util.h
 *
 */ 


#ifndef MODBUS_UTIL_H_
#define MODBUS_UTIL_H_

extern MBException prveMBError2Exception( MBErrorCode eErrorCode );
extern uint8_t xMBUtilGetBits( uint8_t * ucByteBuf, uint16_t usBitOffset, uint8_t ucNBits );
extern void xMBUtilSetBits( uint8_t * ucByteBuf, uint16_t usBitOffset, uint8_t ucNBits, uint8_t ucValue );

typedef struct
{
  uint16_t  min;
  uint16_t  max;
} modbus_address_range_t;

static uint8_t
modbus_check_address_range(uint16_t begin, uint16_t end, const modbus_address_range_t* ranges, int num_ranges)
{
  for(int i = 0; i < num_ranges; i++)
  {
    if(begin >= ranges[i].min && begin <= ranges[i].max &&
        end >= ranges[i].min && end <= ranges[i].max)
    {
      return TRUE;
    }
  }
  return FALSE;
}

#endif /* MODBUS_UTIL_H_ */
