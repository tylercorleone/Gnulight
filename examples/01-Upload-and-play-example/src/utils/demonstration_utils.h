#include <KissLight.h>
#include "ProcedureBuilder.h"

extern KissLight kissLight;

static ButtonEvent SINGLE_CLICK = ButtonEvent::ofClicks(1);
static ButtonEvent TRIPLE_CLICK = ButtonEvent::ofClicks(3);
static ButtonEvent LONG_PRESS = ButtonEvent::ofLongPresses(1);

void sendSingleClick() {
    kissLight.receiveEvent(&SINGLE_CLICK);
}

void sendThreeClicks() {
    kissLight.receiveEvent(&TRIPLE_CLICK);
}

void sendLongPress() {
    kissLight.receiveEvent(&LONG_PRESS);
}

float readBatteryVoltage() {
    return 3.7f; // fixed 3.7 V for demonstration. Actual voltage should be read using an input pin.
}

Procedure &demoSequence = ProcedureBuilder::begin(sendLongPress, 2000) // LOW level for 2 seconds
        .then(sendLongPress, 2000) // then MEDIUM level for 2 seconds
        .then(sendLongPress, 2000) // then HIGH level for 2 seconds
        .then(sendSingleClick, 1000) // then OFF for 1 second
        .then(sendThreeClicks, 5000) // then strobe mode for 5 seconds
        .then(sendSingleClick, 2000) // then OFF for 2 seconds
        .thenRepeat();
