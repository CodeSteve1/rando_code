#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static const uint8_t image_data_dev_off[512] = {
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙██████∙∙∙∙∙∙███████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙█████████∙∙∙∙████████∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙███∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙██∙∙██████∙∙∙∙∙∙∙█████∙∙∙∙█████████∙∙∙██∙∙∙∙∙██∙∙∙██∙∙∙∙∙███████∙∙███████∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙███∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙███∙████████∙∙∙∙∙██████∙∙∙∙█████████∙∙∙██∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙██∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙██∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙██∙∙██∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙███∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙███∙██████∙∙∙∙∙∙██∙∙∙∙∙███∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙███████∙∙∙∙∙███∙∙∙∙██∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙██████∙∙∙██████∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙██∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙███∙███∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙███∙██∙∙∙∙∙∙∙∙∙∙∙∙█████∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙████∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙██∙∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙████∙∙∙████████∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙███████∙∙∙∙███████∙∙∙∙█████████∙∙∙██∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙█████∙∙∙∙∙███████∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙█████████∙∙∙∙∙█████∙∙∙∙█████████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙███████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc1, 0xf8, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0xfe, 0x1f, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0x07, 0x18, 0x07, 0x00, 0x33, 0xf0, 0x1f, 0x0f, 0xf8, 0xc1, 0x8c, 0x1f, 0xcf, 0xe0, 0x07, 
    0xc3, 0x03, 0x98, 0x03, 0x00, 0x77, 0xf8, 0x3f, 0x0f, 0xf8, 0xc2, 0x02, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x01, 0x98, 0x03, 0x00, 0xe0, 0xc0, 0x70, 0x0c, 0x00, 0x02, 0x02, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x01, 0x98, 0x03, 0x81, 0xc0, 0xc0, 0x60, 0x0c, 0x00, 0x04, 0x01, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x01, 0xdf, 0x81, 0x83, 0x80, 0xc0, 0x60, 0x0c, 0x00, 0x04, 0x01, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x00, 0xdf, 0xc1, 0xc3, 0x00, 0xc0, 0x60, 0x0f, 0xf0, 0x04, 0x01, 0x1f, 0x8f, 0xc0, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0xc7, 0x00, 0xc0, 0x60, 0x0f, 0xf0, 0x04, 0x01, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0xee, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x04, 0x01, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0x6c, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x02, 0x02, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x01, 0xd8, 0x00, 0x7c, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x02, 0x02, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x07, 0x98, 0x00, 0x38, 0x00, 0xc0, 0x70, 0x0c, 0x00, 0xc1, 0x8c, 0x10, 0x08, 0x00, 0x07, 
    0xc3, 0x0f, 0x1f, 0xe0, 0x38, 0x03, 0xf8, 0x7f, 0x0f, 0xf8, 0xc0, 0x70, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0x7c, 0x1f, 0xc0, 0x18, 0x07, 0xfc, 0x1f, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


static const uint8_t image_data_dev_on[512] = {
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙██████∙∙∙∙∙∙███████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙█████████∙∙∙∙████████∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙███∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙██∙∙██████∙∙∙∙∙∙∙█████∙∙∙∙█████████∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙███∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙███∙████████∙∙∙∙∙██████∙∙∙∙█████████∙∙∙██∙∙∙∙∙∙██∙∙∙██∙∙∙∙∙∙██∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙██∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙██∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙∙██∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙██∙∙██∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙███∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙∙█∙█∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙███∙██████∙∙∙∙∙∙██∙∙∙∙∙███∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙∙█∙█∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙███████∙∙∙∙∙███∙∙∙∙██∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙∙█∙∙█∙∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙██∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙███∙███∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙█∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙∙∙██∙██∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙∙∙█∙∙∙∙█∙∙∙∙█∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙∙∙███∙██∙∙∙∙∙∙∙∙∙∙∙∙█████∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙∙█∙∙∙∙∙█∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙∙████∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙█∙∙∙∙∙∙∙█∙∙∙∙∙█∙∙∙∙∙█∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙∙∙∙████∙∙∙████████∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙███████∙∙∙∙███████∙∙∙∙█████████∙∙∙██∙∙∙∙∙∙██∙∙∙██∙∙∙∙∙∙█∙∙∙∙∙∙█∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙██∙█████∙∙∙∙∙███████∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙█████████∙∙∙∙∙█████∙∙∙∙█████████∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙█∙∙∙∙∙∙█∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙███████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙█∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc1, 0xf8, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0xfe, 0x1f, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc3, 0x07, 0x18, 0x07, 0x00, 0x33, 0xf0, 0x1f, 0x0f, 0xf8, 0xc0, 0x38, 0x04, 0x02, 0x00, 0x07, 
    0xc3, 0x03, 0x98, 0x03, 0x00, 0x77, 0xf8, 0x3f, 0x0f, 0xf8, 0xc0, 0xc6, 0x06, 0x02, 0x00, 0x07, 
    0xc3, 0x01, 0x98, 0x03, 0x00, 0xe0, 0xc0, 0x70, 0x0c, 0x00, 0x01, 0x01, 0x06, 0x02, 0x00, 0x07, 
    0xc3, 0x01, 0x98, 0x03, 0x81, 0xc0, 0xc0, 0x60, 0x0c, 0x00, 0x01, 0x01, 0x05, 0x02, 0x00, 0x07, 
    0xc3, 0x01, 0xdf, 0x81, 0x83, 0x80, 0xc0, 0x60, 0x0c, 0x00, 0x02, 0x00, 0x85, 0x02, 0x00, 0x07, 
    0xc3, 0x00, 0xdf, 0xc1, 0xc3, 0x00, 0xc0, 0x60, 0x0f, 0xf0, 0x02, 0x00, 0x84, 0x82, 0x00, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0xc7, 0x00, 0xc0, 0x60, 0x0f, 0xf0, 0x02, 0x00, 0x84, 0x42, 0x00, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0xee, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x02, 0x00, 0x84, 0x42, 0x00, 0x07, 
    0xc3, 0x00, 0xd8, 0x00, 0x6c, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x02, 0x00, 0x84, 0x22, 0x00, 0x07, 
    0xc3, 0x01, 0xd8, 0x00, 0x7c, 0x00, 0xc0, 0x60, 0x0c, 0x00, 0x01, 0x01, 0x04, 0x12, 0x00, 0x07, 
    0xc3, 0x07, 0x98, 0x00, 0x38, 0x00, 0xc0, 0x70, 0x0c, 0x00, 0xc1, 0x01, 0x04, 0x12, 0x00, 0x07, 
    0xc3, 0x0f, 0x1f, 0xe0, 0x38, 0x03, 0xf8, 0x7f, 0x0f, 0xf8, 0xc0, 0xc6, 0x04, 0x0a, 0x00, 0x07, 
    0xc3, 0x7c, 0x1f, 0xc0, 0x18, 0x07, 0xfc, 0x1f, 0x0f, 0xf8, 0x00, 0x38, 0x04, 0x0a, 0x00, 0x07, 
    0xc3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x00, 0x07, 
    0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Replace with your network credentials
const char* ssid = "Gts";
const char* password = "steve12345";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliary variable to store the current output state
String output26State = "off";

// Assign output variable to GPIO pin
const int output26 = 26;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // Initialize the output variable as output
  pinMode(output26, OUTPUT);
  // Set output to LOW
  digitalWrite(output26, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIO on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
              doshit1on();
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
              doshit1off();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off button 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>");
            client.println("html { font-family: Arial; display: flex; justify-content: center; align-items: center; height: 100%; background: linear-gradient(135deg, #71b7e6, #9b59b6); }");
            client.println("body { margin: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }");
            client.println(".container { text-align: center; background: white; padding: 20px; border-radius: 10px; box-shadow: 0px 0px 20px rgba(0, 0, 0, 0.1); }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; transition: background-color 0.3s ease; border-radius: 5px; }");
            client.println(".button:hover { background-color: #45a049; }");
            client.println(".button2 { background-color: #555555; }");
            client.println(".button2:hover { background-color: #333333; }");
            client.println("h1 { color: #333; }");
            client.println("p { font-size: 1.2rem; color: #666; }");
            client.println("</style></head>");
            
            // Web Page Heading
            client.println("<body><div class=\"container\"><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF button for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("</div></body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void doshit1on(){
  display.clearDisplay();
  display.drawBitmap(0, 0, image_data_dev_on, 128, 64, 1);
  Serial.println("device_ON display_works");
  display.display();

}

void doshit1off(){
  display.clearDisplay();
  display.drawBitmap(0, 0, image_data_dev_off, 128, 64, 1);
  
  display.display();

}