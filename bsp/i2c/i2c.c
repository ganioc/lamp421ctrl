/*
 * i2c.c
 *
 *  Created on: 2023 Mar 8
 *      Author: ruffman
 */

#include "at32f421_board.h"
#include "i2c_application.h"

i2c_handle_type hi2cx;

void i2c2_init(){
	hi2cx.i2cx = I2C2_PORT;

	i2c_config(&hi2cx);
}


/**
  * @brief  initializes peripherals used by the i2c.
  * @param  none
  * @retval none
  */
void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
	cust_printf("\r\n\r\ni2c_lowlevel_init called\r\n");

  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2C2_PORT)
  {
	cust_printf("init i2c2__z\r\n");

    /* i2c periph clock enable */
    crm_periph_clock_enable(I2C2_CLK, TRUE);
    crm_periph_clock_enable(I2C2_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2C2_SDA_GPIO_CLK, TRUE);


    gpio_default_para_init(&gpio_initstructure);
    // enable iomux clock,
    //crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    // remap i2c2 pf6/pf7,
    // gpio_pin_remap_config(I2C1_GMUX_0010,TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2C2_SCL_PIN;
    gpio_init(I2C2_SCL_GPIO_PORT, &gpio_initstructure);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE0, GPIO_MUX_1);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2C2_SDA_PIN;
    gpio_init(I2C2_SDA_GPIO_PORT, &gpio_initstructure);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE1, GPIO_MUX_1);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2C2_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2C2_ADDRESS);
  }
}
