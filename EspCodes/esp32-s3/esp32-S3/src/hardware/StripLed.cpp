#include "StripLed.h"
#include <string.h>

// =====================
// WS2812 TIMING (ESP32 RMT)
// =====================
#define RMT_RES_HZ 10000000 // 10MHz = 100ns tick

#define T0H 3
#define T1H 7
#define T_TOTAL 10

StripLed::StripLed(gpio_num_t gpio, uint16_t ledCount)
{
    pin = gpio;
    count = ledCount;

    state = false;
    brightness = 100;
    effect = NONE;
    hue = 0;

    pixels = new uint8_t[count * 3];
    memset(pixels, 0, count * 3);
}

// =====================
void StripLed::init()
{
    rmt_tx_channel_config_t cfg = {
        .gpio_num = pin,
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = RMT_RES_HZ,
        .mem_block_symbols = 64,
        .trans_queue_depth = 4,
        .flags = {}
    };

    rmt_new_tx_channel(&cfg, &tx_channel);
    rmt_enable(tx_channel);
}

// =====================
void StripLed::startTask()
{
    xTaskCreate(taskHandler, "strip_led", 4096, this, 5, &taskHandle);
}

void StripLed::taskHandler(void* arg)
{
    StripLed* self = (StripLed*)arg;

    while (1)
    {
        self->loop();
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}

// =====================
void StripLed::loop()
{
    if (!state) return;

    switch (effect)
    {
        case RAINBOW: applyRainbow(); break;
        case FADE: applyFade(); break;
        default: break;
    }
}

// =====================
bool StripLed::isOn() const
{
    return state;
}

void StripLed::powerOn()
{
    state = true;
}

void StripLed::powerOff()
{
    state = false;

    memset(pixels, 0, count * 3);
    sendFrame();
}

// =====================
void StripLed::setBrightness(uint8_t b)
{
    brightness = (b > 100) ? 100 : b;
}

// =====================
void StripLed::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    if (!state || effect != NONE) return;

    float k = brightness / 100.0f;

    r *= k;
    g *= k;
    b *= k;

    for (int i = 0; i < count; i++)
    {
        pixels[i * 3 + 0] = g;
        pixels[i * 3 + 1] = r;
        pixels[i * 3 + 2] = b;
    }

    sendFrame();
}

// =====================
void StripLed::setEffect(Effect e)
{
    effect = e;
}

// =====================
// EFFECTS
// =====================
void StripLed::applyRainbow()
{
    hue++;

    float k = brightness / 100.0f;

    uint8_t r = (hue);
    uint8_t g = (255 - hue);
    uint8_t b = (hue / 2);

    r *= k; g *= k; b *= k;

    for (int i = 0; i < count; i++)
    {
        pixels[i * 3 + 0] = g;
        pixels[i * 3 + 1] = r;
        pixels[i * 3 + 2] = b;
    }

    sendFrame();
}

void StripLed::applyFade()
{
    static int v = 0;
    static int dir = 1;

    v += dir * 5;

    if (v >= 255) { v = 255; dir = -1; }
    if (v <= 0)   { v = 0;   dir = 1; }

    uint8_t val = (uint8_t)(v * (brightness / 100.0f));

    for (int i = 0; i < count; i++)
    {
        pixels[i * 3 + 0] = val;
        pixels[i * 3 + 1] = 0;
        pixels[i * 3 + 2] = 0;
    }

    sendFrame();
}

// =====================
// WS2812 RMT ENCODING (CORRETO)
// =====================
static inline void encode_bit(bool bit, rmt_symbol_word_t &sym)
{
    if (bit)
    {
        sym.level0 = 1;
        sym.duration0 = T1H;
        sym.level1 = 0;
        sym.duration1 = T_TOTAL - T1H;
    }
    else
    {
        sym.level0 = 1;
        sym.duration0 = T0H;
        sym.level1 = 0;
        sym.duration1 = T_TOTAL - T0H;
    }
}

void StripLed::sendFrame()
{
    if (!tx_channel || !state) return;

    const int maxSymbols = count * 24;
    static rmt_symbol_word_t symbols[3000];

    int idx = 0;

    // WS2812 = GRB
    for (int i = 0; i < count; i++)
    {
        uint8_t g = pixels[i * 3 + 0];
        uint8_t r = pixels[i * 3 + 1];
        uint8_t b = pixels[i * 3 + 2];

        uint8_t data[3] = { g, r, b };

        for (int j = 0; j < 3; j++)
        {
            for (int bit = 7; bit >= 0; bit--)
            {
                encode_bit(data[j] & (1 << bit), symbols[idx++]);
            }
        }
    }

    rmt_transmit_config_t cfg = {};
    cfg.loop_count = 0;

    rmt_transmit(tx_channel, nullptr, symbols, idx * sizeof(rmt_symbol_word_t), &cfg);
}