//
//
//
#include <M5Unified.h>  // Arduino / ESP-IDF Library for M5Stack Series
#include <unit_asr.hpp> // for Unit ASR

//
//
//
ASRUnit asr;


//
//
//
void setup()
{
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    cfg.output_power = true;
    cfg.clear_display = true;
    cfg.led_brightness = 96;

    M5.begin(cfg);

}

//
//
//
void loop()
{
    M5.update();
    delay(10000);
}
