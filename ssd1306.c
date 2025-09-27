/*
 * Free software, check the license, do what you want with it.
 */

#include "ssd1306.h"
#include <string.h>

static i2c_inst_t *ssd1306_i2c;
static uint8_t ssd1306_address;
static uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Send command helper function.
static void ssd1306_send_command(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    i2c_write_blocking(ssd1306_i2c, ssd1306_address, data, 2, false);
}

// Display initialization function.
void ssd1306_init(i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin, uint8_t addr) {
    ssd1306_i2c = i2c;
    ssd1306_address = addr;

    // Set up SDA and SCL
    i2c_init(i2c, 400 * 1000); // 400kHz I2C
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    // Initialization flow
    ssd1306_send_command(0xA8); // Initiate set MUX ratio
    ssd1306_send_command(0x3F); // 64 pixel height (COM0-COM63)
    ssd1306_send_command(0xD3); // Initiate set display offset
    ssd1306_send_command(0x00); // Don't offset display
    ssd1306_send_command(0x40); // Set display start line to the top
    ssd1306_send_command(0xA0); // Set segment re-map (column address 0 is mapped to SEG0) (left-right)
    ssd1306_send_command(0xC0); // Set COM output scan direction to COM63-COM0 (top-bottom) ok i think its actually bottom-top but idk this is confusing,.
    ssd1306_send_command(0xDA); // Set COM pins hardware configuration
    ssd1306_send_command(0x02); // Sequential COM pin configuration (not alternating)
    ssd1306_send_command(0x81); // Initiate set contrast control for BANK0
    ssd1306_send_command(0x7F); // Set to mid-brightness
    ssd1306_send_command(0xA4); // Disable having entire display on
    ssd1306_send_command(0xA6); // Set display to normal mode (A7 is "inverted", think light vs. dark mode)
    ssd1306_send_command(0xD5); // Display clock divide ratio; need to investigate this
    ssd1306_send_command(0x80); // Set oscillator frequency Fosc; need to investigate this
    ssd1306_send_command(0x8D); // Initiate enable charge pump regulator - literally what even is this
    ssd1306_send_command(0x14); // Enable charge pump
    ssd1306_send_command(0xAF); // Turn display on (AE for sleep mode)
}