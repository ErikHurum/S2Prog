#ifndef __HART_GPIO_DEF_H__
#define __HART_GPIO_DEF_H__

#include "hart_common.h"
#include "hart.h"

#define AD7715_PORT     PORTL
#define AD7715_PIN      PINL
#define AD7715_SCLK     __BIT_MASK(0)             // PL0
#define AD7715_MISO     __BIT_MASK(1)             // PL1
#define AD7715_MOSI     __BIT_MASK(2)             // PL2

#define AD7715_CLK_LO()          (AD7715_PORT &= ~AD7715_SCLK)
#define AD7715_CLK_HI()          (AD7715_PORT |=  AD7715_SCLK)
#define AD7715_MISO_READ()       (AD7715_PIN & AD7715_MISO)
#define AD7715_MOSI_LO()         (AD7715_PORT &= ~AD7715_MOSI)
#define AD7715_MOSI_HI()         (AD7715_PORT |=  AD7715_MOSI)

extern void hart_gpio_power_on(hart_channel_t chnl);
extern void hart_gpio_power_off(hart_channel_t chnl);
extern void hart_gpio_mux_enable(hart_mux_t mux);
extern void hart_gpio_mux_disable(hart_mux_t mux);
extern void hart_gpio_channel_select(hart_channel_t chnl);
extern void hart_gpio_adc_channel_select(hart_channel_t chnl);
extern void hart_gpio_adc_reset(uint8_t hi);
extern void hart_gpio_modem_rx_enable(hart_modem_t modem);
extern void hart_gpio_modem_rx_enable_irq(hart_modem_t modem);
extern void hart_gpio_modem_rx_disable(hart_modem_t modem);
extern void hart_gpio_modem_rx_disable_irq(hart_modem_t modem);
extern void hart_gpio_debug_led(uint8_t on);

extern void hart_gpio_init(void);

#endif /* !__HART_GPIO_DEF_H__ */
