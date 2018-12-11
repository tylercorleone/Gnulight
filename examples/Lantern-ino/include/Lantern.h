#ifndef LANTERN_H
#define LANTERN_H

#include "custom_gnulight.h"
#include "LedCurrentDriver.h"

float readBatteryVoltage();

class Lantern: public Gnulight {
public:
	Lantern();
protected:
	void onSetup() override;
	void onSwitchOn() override;
	void onSwitchOff() override;
	void onIdle() override;
	LedCurrentDriver ledCurrentDriver;
	LithiumBattery battery { 2.8, 3.2, 4.17, 0.053, readBatteryVoltage };
};

#endif
