/**
  **************************************************************************
  * @file     at32f421_board.h
  * @version  v2.0.6
  * @date     2022-05-20
  * @brief    header file for at-start board. set of firmware functions to
  *           manage leds and push-button. initialize delay function.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#ifndef __AT32F421_BOARD_H
#define __AT32F421_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "at32f421.h"

#include "mcu_wdt.h"

/** @addtogroup AT32F421_board
  * @{
  */

/** @addtogroup BOARD
  * @{
  */

/** @defgroup BOARD_pins_definition
  * @{
  */

/**
  * this header include define support list:
  * 1. at-start-f421 v1.x boards
  * if define AT_START_F421_V1, the header file support at-start-f421 v1.x board
  */

#if !defined (AT_START_F421_V1)
#error "please select first the board at-start device used in your application (in at32f421_board.h file)"
#endif

/******************** define led ********************/
typedef enum
{
  LED2                                   = 0,
  LED3                                   = 1,
  LED4                                   = 2
} led_type;

#define LED_NUM                          3

#if defined (AT_START_F421_V1)
#define LED2_PIN                         GPIO_PINS_6
#define LED2_GPIO                        GPIOF
#define LED2_GPIO_CRM_CLK                CRM_GPIOF_PERIPH_CLOCK

#define LED3_PIN                         GPIO_PINS_7
#define LED3_GPIO                        GPIOF
#define LED3_GPIO_CRM_CLK                CRM_GPIOF_PERIPH_CLOCK

#define LED4_PIN                         GPIO_PINS_11
#define LED4_GPIO                        GPIOB
#define LED4_GPIO_CRM_CLK                CRM_GPIOB_PERIPH_CLOCK
#endif

/**************** define print uart ******************/
#define PRINT_UART                       USART1
#define PRINT_UART_CRM_CLK               CRM_USART1_PERIPH_CLOCK
#define PRINT_UART_TX_PIN                GPIO_PINS_9
#define PRINT_UART_TX_GPIO               GPIOA
#define PRINT_UART_RX_PIN                GPIO_PINS_10
#define PRINT_UART_RX_GPIO               GPIOA
#define PRINT_UART_TX_GPIO_CRM_CLK       CRM_GPIOA_PERIPH_CLOCK
#define PRINT_UART_TX_PIN_SOURCE         GPIO_PINS_SOURCE9
#define PRINT_UART_TX_PIN_MUX_NUM        GPIO_MUX_1
#define PRINT_UART_RX_PIN_SOURCE         GPIO_PINS_SOURCE10
#define PRINT_UART_RX_PIN_MUX_NUM        GPIO_MUX_1

void uart_print_init(uint32_t baudrate);
void print_at_info();
void print_welcome();


/******************* define button *******************/
typedef enum
{
  USER_BUTTON                            = 0,
  NO_BUTTON                              = 1
} button_type;

#define USER_BUTTON_PIN                  GPIO_PINS_0
#define USER_BUTTON_PORT                 GPIOA
#define USER_BUTTON_CRM_CLK              CRM_GPIOA_PERIPH_CLOCK

/**
  * @}
  */

/** @defgroup BOARD_exported_functions
  * @{
  */

/******************** functions ********************/
void at32_board_init(void);

/* led operation function */
void at32_led_init(led_type led);
void at32_led_on(led_type led);
void at32_led_off(led_type led);
void at32_led_toggle(led_type led);

/* button operation function */
void at32_button_init(void);
button_type at32_button_press(void);
uint8_t at32_button_state(void);

/* delay function */
void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);



/* I2C  */
#define I2C2_SCL_PIN                     GPIO_PINS_0
#define I2C2_SCL_GPIO_PORT               GPIOA
#define I2C2_SCL_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

#define I2C2_SDA_PIN                     GPIO_PINS_1
#define I2C2_SDA_GPIO_PORT               GPIOA
#define I2C2_SDA_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

/*  RS485  */
#define RS485_UART                       USART2
#define RS485_UART_CRM_CLK               CRM_USART2_PERIPH_CLOCK
#define RS485_UART_TX_PIN                GPIO_PINS_2
#define RS485_UART_TX_GPIO               GPIOA
#define RS485_UART_RX_PIN                GPIO_PINS_3
#define RS485_UART_RX_GPIO               GPIOA
#define RS485_UART_TX_GPIO_CRM_CLK       CRM_GPIOA_PERIPH_CLOCK
#define RS485_UART_TX_PIN_SOURCE         GPIO_PINS_SOURCE2
#define RS485_UART_TX_PIN_MUX_NUM        GPIO_MUX_1
#define RS485_UART_RX_PIN_SOURCE         GPIO_PINS_SOURCE3
#define RS485_UART_RX_PIN_MUX_NUM        GPIO_MUX_1


#define RS485_EN_PIN                     GPIO_PINS_4
#define RS485_EN_GPIO_PORT               GPIOA
#define RS485_EN_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

void uart_rs485_init(uint32_t baudrate);
void rs485_en_gpio_init();

/*  Button    */
#define BUTTON_PIN                     GPIO_PINS_7
#define BUTTON_GPIO_PORT               GPIOA
#define BUTTON_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

/*  power switch control   */
#define POWER_52V_PIN                     GPIO_PINS_1
#define POWER_52V_GPIO_PORT               GPIOB
#define POWER_52V_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define POWER_12V_PIN                     GPIO_PINS_2
#define POWER_12V_GPIO_PORT               GPIOB
#define POWER_12V_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

/*   PWM     */
#define PWM_1_PIN                     GPIO_PINS_8
#define PWM_1_GPIO_PORT               GPIOA
#define PWM_1_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK
#define PWM_2_PIN                     GPIO_PINS_11
#define PWM_2_GPIO_PORT               GPIOA
#define PWM_2_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

#define PWM_1_PIN_SOURCE               GPIO_PINS_SOURCE8
#define PWM_2_PIN_SOURCE               GPIO_PINS_SOURCE11

#define PWM_TIMER_DIV                  120
#define PWM_REF_FREQ                   1000
#define PWM_FREQ_POINTS                7
#define PWM_FREQ_STEP                  1
#define PWM_DUTY_STEP                  30

#define PWM_DEFAULT_FREQ               1000
#define PWM_DEFAULT_DUTY               50

void timer_pwm_config();
uint16_t get_pwm_freq();
uint16_t check_pwm_freq(uint16_t frequency);
void set_pwm_freq(uint16_t frequency);
void check_pwm_freq_duty();
uint8_t get_pwm_duty1();
uint8_t get_pwm_duty2();
void set_pwm_duty1(uint8_t duty);
void set_pwm_duty2(uint8_t duty);
void set_pwm_channel_duty(uint8_t channel, uint8_t duty);
void pwm_set_default_value();
void pwm_load_value(uint16_t freq, uint16_t duty1, uint16_t duty2);

/*   Ethernet reset   */
#define ETH_RESET_PIN                     GPIO_PINS_12
#define ETH_RESET_GPIO_PORT               GPIOA
#define ETH_RESET_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK



/*    LED    */
#define LED_RUN_PIN                     GPIO_PINS_6
#define LED_RUN_GPIO_PORT               GPIOB
#define LED_RUN_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define LED_ETH_PIN                     GPIO_PINS_7
#define LED_ETH_GPIO_PORT               GPIOB
#define LED_ETH_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define LED_NET_PIN                     GPIO_PINS_8
#define LED_NET_GPIO_PORT               GPIOB
#define LED_NET_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

void led_gpio_init();
void led_run_on();
void led_run_off();
void led_run_toggle();

void led_eth_on();
void led_eth_off();
void led_eth_toggle();

void led_net_on();
void led_net_off();
void led_net_toggle();

void led_shining_pattern();

void simu_uart_tx();
void cust_printf(char* format, ...);


/*    at uart    */
#define AT_RX_BUFFER_LEN  256

void send_response_str(char *str);
void send_response_ok();
void send_response_timeout();
void send_response_error(char* code);
void send_response_str_raw(char* str);

void start_timer();
void stop_timer();


/*   Timer3   */
void timer3_config();

/*   I2C   */
#define I2C2_SCL_PIN                     GPIO_PINS_0
#define I2C2_SCL_GPIO_PORT               GPIOA
#define I2C2_SCL_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

#define I2C2_SDA_PIN                     GPIO_PINS_1
#define I2C2_SDA_GPIO_PORT               GPIOA
#define I2C2_SDA_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

#define I2C2_PORT                        I2C2
#define I2C2_CLK                         CRM_I2C2_PERIPH_CLOCK

#define I2C2_SPEED                       100000
#define I2C2_ADDRESS                     0xA0
#define EEPROM_ADDRESS                   0xA0

#define I2C_TIMEOUT                      0xFFFFFF

void i2c2_init();

/*    at uart    */
uint8_t get_at_rx_flag();
uint8_t reset_at_rx_flag();
uint8_t check_at_rx_empty();
uint8_t read_at_rx_tail();
void at_rx_take(uint8_t data);
void at_rx_check();

/*   sys state     */
#define EEPROM_FLASH_ADDRESS_START       (0x08000000 + 1024 * 60)

#define SECTOR_SIZE                      1024

#define PARAM_PWM_ADDRESS   (EEPROM_FLASH_ADDRESS_START)
#define PARAM_VO_ADDRESS    (EEPROM_FLASH_ADDRESS_START + 1*SECTOR_SIZE)
#define PARAM_MAGIC         0x1E1F

void check_params();
void save_param_pwm(uint16_t freq, uint16_t duty1, uint16_t duty2);
void save_param_vo_relay(uint16_t* state, uint16_t len);
void restore_default_value();


/*    vo    */
#define PWR_52V_PIN                     GPIO_PINS_1
#define PWR_52V_GPIO_PORT               GPIOB
#define PWR_52V_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define PWR_12V_PIN                     GPIO_PINS_2
#define PWR_12V_GPIO_PORT               GPIOB
#define PWR_12V_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

/*   Relay control    */
#define RELAY_1_PIN                     GPIO_PINS_3
#define RELAY_1_GPIO_PORT               GPIOB
#define RELAY_1_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define RELAY_2_PIN                     GPIO_PINS_4
#define RELAY_2_GPIO_PORT               GPIOB
#define RELAY_2_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define RELAY_3_PIN                     GPIO_PINS_5
#define RELAY_3_GPIO_PORT               GPIOB
#define RELAY_3_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define RELAY_GPIO_PORT                 GPIOB
#define VO_RELAY_GPIO_PORT                 GPIOB

#define PWR_52V_DEFAULT                 0
#define PWR_12V_DEFAULT                 0
#define RELAY_1_DEFAULT                 0
#define RELAY_2_DEFAULT                 0
#define RELAY_3_DEFAULT                 0

#define PWR_52V_ID                 0
#define PWR_12V_ID                 1
#define RELAY_1_ID                 2
#define RELAY_2_ID                 3
#define RELAY_3_ID                 4

void vo_gpio_init();
uint16_t get_state_pwr_52v();
uint16_t get_state_pwr_12v();
uint16_t get_state_relay(uint16_t channel);
void vo_52v_on();
void vo_52v_off();
void vo_12v_on();
void vo_12v_off();
void vo_set_gpio(uint16_t channel, uint16_t value);
void vo_relay_set_default_value();
void vo_relay_load_value(uint16_t p52v,
		uint16_t p12v,
		uint16_t r1,
		uint16_t r2,
		uint16_t r3);
void relay_set_gpio(uint16_t channel, uint16_t value);




/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

