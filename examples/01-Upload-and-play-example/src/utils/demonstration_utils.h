#include "config.h"
#include "ProcedureBuilder.h"

extern KissLight kissLight;

/*
 * Utility functions
 */
void sendSingleClick() {
	kissLight.receiveEvent(ButtonEvent(1, 0));
}

void sendTwoClicks() {
	kissLight.receiveEvent(ButtonEvent(2, 0));
}

void sendThreeClicks() {
	kissLight.receiveEvent(ButtonEvent(3, 0));
}

void sendFourClicks() {
	kissLight.receiveEvent(ButtonEvent(4, 0));
}

void sendHold() {
	kissLight.receiveEvent(ButtonEvent(0, 1));
}

float readBatteryVoltage() {
	return 3.7f; // fixed 3.7 V for demonstration. Actual voltage should be read using an input pin.
}

Procedure &demoSequence = ProcedureBuilder::begin(sendHold, 2000) // LOW level for 2 seconds
		.then(sendHold, 2000) // then MEDIUM level for 2 seconds
		.then(sendHold, 2000) // then HIGH level for 2 seconds
		.then(sendSingleClick, 1000) // then OFF for 1 second
		.then(sendThreeClicks, 0) // then strobe mode
		.then(sendHold, 5000) // set HIGH level and stay for 5 seconds
		.then(sendSingleClick, 1000) // then OFF for one second
		.thenRepeat();
