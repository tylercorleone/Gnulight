#include "custom_gnulight.h"
#include "demonstration_utils.h"
#include "BuiltinLedDriver.h"
#include "PwmTask.h"

BuiltinLedDriver ledDriver;
PwmTask pwmTask { LED_PIN }; // see PwmTask.h
Gnulight gnulight { ledDriver };

void setup() {
#ifdef LOG_ENABLED
	Serial.begin(9600);
#endif
	pinMode(LED_PIN, OUTPUT);

	/*
	 * An helper class that simplifies the configuration
	 * of battery and temperature monitors
	 */
	GnulightHelper::customize(gnulight)
		.configureBatteryMonitor(0.0f, 1.0f, readBatteryVoltage);

	gnulight.setup();

	/* Lets set MEDIUM and HIGH levels to the
	 * highest available for those groups */
	sendSingleClick(); // switch ON on HIGH
	sendTwoClicks(); // select H2 as HIGH level
	sendSingleClick(); // switch OFF

	sendTwoClicks(); // switch ON on MED
	sendTwoClicks(); // select M2 as MED level
	sendSingleClick(); // switch OFF

	gnulight.StartTask(&pwmTask);
	gnulight.StartTask(&demoSequence);
}

void loop() {
	gnulight.Loop();
}

