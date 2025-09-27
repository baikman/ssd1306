/*
 * Free software, check the license, do what you want with it.
 */

#ifndef SSD1306_H
#define SSD1306_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// 128x64
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// I2C address (usually either 0x3C or 0x3D, check your specific display)
#define SSD1306_I2C_ADDR 0x3C

// API
void ssd1306_init(i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin, uint8_t addr);
void ssd1306_clear(void);

#endif