#include "custom_gnulight.h"
#include "ProcedureBuilder.h"

extern Gnulight gnulight;

/*
 * Utility functions
 */
void sendSingleClick() {
	gnulight.receiveEvent(ButtonEvent(1, 0));
}

void sendTwoClicks() {
	gnulight.receiveEvent(ButtonEvent(2, 0));
}

void sendThreeClicks() {
	gnulight.receiveEvent(ButtonEvent(3, 0));
}

void sendFourClicks() {
	gnulight.receiveEvent(ButtonEvent(4, 0));
}

void sendHold() {
	gnulight.receiveEvent(ButtonEvent(0, 1));
}

float readBatteryVoltage() {
	// just for demonstration
	return 0.4f;
}

Procedure &demoSequence = ProcedureBuilder::begin(sendHold, 3000) // switch ON on LOW level for three seconds
		.then(sendHold, 3000) // then enter MEDIUM level
		.then(sendHold, 3000) // then enter HIGH level
		.then(sendSingleClick, 1000) // then switch OFF for one second
		.then(sendThreeClicks, 0) // then select StrobeMode
		.then(sendHold, 8000) // set the HIGH level and stay ON for eight seconds
		.then(sendSingleClick, 1000) // then switch OFF for one second
		.then(sendFourClicks, 6000) // then enter BatteryChackMode
		.thenRepeat();
