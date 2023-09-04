#define LEVEL_LOW_1 0.33 // In order to make it visible
#define LEVEL_MED_1 0.66
#define LEVEL_HIGH_1 1.0

#include <KissLight.h>
#include "BuiltinLedDriver.h"
#include "utils/demonstration_utils.h"

BuiltinLedDriver ledDriver;
KissLight kissLight{ledDriver};

void setup() {
#ifdef SIMPLE_LOGGER_APPENDER_ENABLED
    Serial.begin(9600);
#endif

    kissLight.lightDriver.logger.setLogLevel(LogLevel::TRACE);
    kissLight.lightnessDimmer.logger.setLogLevel(LogLevel::TRACE);
    kissLight.lightnessDimmer.setMinValue(
            0.1f); // TODO: calculate actual lightness that result in 1% to ws2812fx

    ws2812fx.init();
    ws2812fx.setColor(0xFF0000);
    ws2812fx.setMode(FX_MODE_STATIC);
    ws2812fx.start();

    /*
     * A helper class that can be used to simplify the configuration
     */
    KissLightHelper::customize(kissLight)
            .configureBatteryMonitor(3.2f, 4.2f, readBatteryVoltage);

    kissLight.initialize();

    // this is need only to simulate the button interaction!
    kissLight.getTaskManager().StartTask(&demoSequence);
}

void loop() {
    kissLight.loop();
    ws2812fx.service();
}

