#ifndef LANTERN_H
#define LANTERN_H

#include "custom_kisslight.h"
#include "LedCurrentDriver.h"

float readBatteryVoltage();

class Lantern: public KissLight {
public:
	Lantern();
protected:
	void onSetup() override;
	void onSwitchOn() override;
	void onSwitchOff() override;
	void onIdle();
	LedCurrentDriver ledCurrentDriver;
	LithiumBattery battery { readBatteryVoltage, 2.8, 3.2, 4.17, 0.053 };
};

#endif
