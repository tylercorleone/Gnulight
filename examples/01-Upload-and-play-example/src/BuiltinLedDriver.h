#include <KissLight.h>
#include <WS2812FX.h>

#define LED_PIN 2 // ESP32-C3-0.42's multi color LED pin

WS2812FX ws2812fx = WS2812FX(1, LED_PIN, NEO_RGB + NEO_KHZ800);

class BuiltinLedDriver : public LightDriver {
private:
    void onSetLevel(float level) override {
        ws2812fx.setBrightness(level * 100);
    }
};
