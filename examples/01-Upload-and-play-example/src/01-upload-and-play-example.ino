#include "custom_gnulight.h"
#include "demonstration_utils.h"
#include "BuiltinLedDriver.h"
#include "PwmTask.h"

BuiltinLedDriver ledDriver;
Gnulight gnulight { ledDriver };
PwmTask pwmTask { LED_PIN, gnulight.getTaskManager()};

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

	// initializes the task manager
	gnulight.setup();

	/* Lets set MEDIUM and HIGH levels to the
	 * highest available for those groups */
	sendTwoClicks(); // switch ON on MED
	sendTwoClicks(); // select M2 as MED level
	sendHold(); // switch on HIGH level
	sendTwoClicks(); // select H2 as HIGH level
	gnulight.enterState(gnulight.offMode); // switch OFF

	gnulight.getTaskManager().StartTask(&demoSequence);
}

void loop() {
	gnulight.loop();
}

