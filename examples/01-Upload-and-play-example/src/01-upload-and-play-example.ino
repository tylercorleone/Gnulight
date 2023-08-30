#include "config.h"
#include "utils/demonstration_utils.h"
#include "BuiltinLedDriver.h"

BuiltinLedDriver ledDriver;
KissLight kissLight { ledDriver };

void setup() {
#ifdef LOG_ENABLED
	Serial.begin(9600);
#endif

    ws2812fx.init();
    ws2812fx.setColor(0xFF0000);
    ws2812fx.setMode(FX_MODE_STATIC);
    ws2812fx.start();

	/*
	 * A helper class that simplifies the configuration
	 * of battery and temperature monitors
	 */
	KissLightHelper::customize(kissLight)
		.configureBatteryMonitor(3.2f, 4.2f, readBatteryVoltage); // 3.2 V and 4.2 V are just an examle

	// initializes the task manager
	kissLight.setup();

	kissLight.getTaskManager().StartTask(&demoSequence);
}

void loop() {
    kissLight.loop();
    ws2812fx.service();
}

