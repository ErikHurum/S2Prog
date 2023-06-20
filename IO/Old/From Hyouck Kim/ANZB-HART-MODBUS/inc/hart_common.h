#ifndef __HART_COMMON_DEF_H__
#define __HART_COMMON_DEF_H__

#define HART_MAX_CHANNEL                12

#ifndef COMMON_TYPES_DEFINED
//
// no idea why freaking IAR doesn't define this basic integer types
//
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;
typedef signed long int int32_t;
typedef unsigned long int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

#endif

#define hart_for_each_channel(c)            for(c = hart_channel_0; c <= hart_channel_11; c++)
#define hart_for_each_task_channel(c, task) for(c = task->start_chnl; c <= task->end_chnl; c++)


typedef enum
{
  HartChannelStatus_Responding,
  HartChannelStatus_No_Response,
  HartChannelStatus_Invalid_Response,
} HartChannelStatus;

typedef enum
{
  HartChannelPowerStatus_ON,
  HartChannelPowerStatus_OFF,
} HartChannelPowerStatus;

typedef enum
{
  HartChannelStatItem_RX_INVALID,
  HartChannelStatItem_RX_CSUM,
  HartChannelStatItem_RX_TIMEOUT,
  HartChannelStatItem_TOTAL_REQS,
  HartChannelStatItem_TOTAL_SUCCESS,
} HartChannelStatItem;

typedef enum
{
  hart_channel_0    = 0,
  hart_channel_1,
  hart_channel_2,
  hart_channel_3,
  hart_channel_4,
  hart_channel_5,
  hart_channel_6,
  hart_channel_7,
  hart_channel_8,
  hart_channel_9,
  hart_channel_10,
  hart_channel_11,
} hart_channel_t;

typedef enum
{
  hart_mux_0    = 0,
  hart_mux_1,
  hart_mux_2,
} hart_mux_t;

typedef enum
{
  hart_modem_0  = 0,
  hart_modem_1,
  hart_modem_2,
} hart_modem_t;

typedef struct
{
  hart_channel_t                    chnl_num;
  //
  // basic channel status
  //
  volatile HartChannelStatus        status;
  volatile HartChannelPowerStatus   power_status;

  //
  // diagnostic status
  //

  //
  // channel stats
  //
  volatile uint32_t                 rx_invalid_msg;
  volatile uint32_t                 rx_csum_err;
  volatile uint32_t                 rx_timeout;
  volatile uint32_t                 total_reqs;
  volatile uint32_t                 total_success;

  //
  // XXX
  // any channel specific process data goes here
  //
  volatile float                    ma_feedback;          // measured mA. 10 = 1 mA
  volatile float                    hart_current;
  volatile float                    distance;
  volatile float                    level;

  uint32_t  last_access_time;

} HartChannel;

extern HartChannel* hart_channel_get_with_lock(hart_channel_t chnl_num);
extern void hart_channel_put_with_unlock(HartChannel* chnl);
extern void hart_channel_power_on_off(hart_channel_t chnl_num, uint8_t on);
extern uint16_t hart_get_rsp_delay(void);
extern void hart_set_rsp_delay(uint16_t delay);
extern void hart_reset_eeprom(void);

#endif //!__HART_COMMON_DEF_H__
