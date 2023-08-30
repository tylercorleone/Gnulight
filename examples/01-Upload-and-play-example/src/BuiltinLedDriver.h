#include "config.h"
#include <WS2812FX.h>

#define LED_COUNT 1

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

class BuiltinLedDriver: public KissLightLightDriver {
private:
	void onSetLevel(float level) override {
        ws2812fx.setBrightness(level * 100);
    }
};
