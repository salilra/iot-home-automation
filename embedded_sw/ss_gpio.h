/* Copyright(C) Shubhra Rajadhyaksha, Salil Rajadhyaksha.
 * Copying, re-distributing or sharing without permission of the authors
 * is strictly prohibited.
 * 
 * Author: Salil Rajadhyaksha
 * Date: June 4, 2016
 */
#include <stdbool.h>
 
//TODO-this should be mapped from physical pins
/************************** Pin maps****************************************/
#define GPIO_PIN_03 (03)
#define GPIO_PIN_22 (22)
#define GPIO_PIN_29 (29)
/***************************************************************************/
 
#define SS_RELAY_REGULAR_LAMP GPIO_PIN_22
#define SS_RELAY_FAN          GPIO_PIN_03
#define SS_RELAY_LAVA_LAMP    GPIO_PIN_29

#define SS_GPIO_EXPORT_STR       "/sys/class/gpio/export"
#define SS_GPIO_VALUE_DIR_STR    "/sys/class/gpio/export/gpio/gpio"


//#define SS_GPIO_VAL_STR(int num) SS_GPIO_VALUE_DIR_STR

inline void ss_dump_pinout(void) {
    system("gpio readall");
}

int ss_gpio_cfg(uint8_t mode, uint8_t pin);
int ss_gpio_write(uint8_t pin, bool value);
