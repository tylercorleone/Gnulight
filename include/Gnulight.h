#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "gnulight_config.h"

#include <Components.h>

#include "BrightnessDriver.h"
#include "GnulightLightDimmer.h"
#include "ConstantLightMode.h"
#include "ParameterCheckMode.h"
#include "PowerOffMode.h"
#include "StrobeMode.h"
#include "BatteryMonitor.h"
#include "TempMonitor.h"

class Gnulight : public GenericDevice {
	friend class GnulightCustomizer;
	friend class TempMonitor;
	friend class BatteryMonitor;
	friend class PowerOffMode;
	friend class ConstantLightMode;
	friend class StrobeMode;
	friend class ParameterCheckMode;
public:
	Gnulight(BrightnessDriver &brightnessDriver, const char *deviceName =
			"Gnulight");
	Button button { *this };
protected:
	virtual void onSetup() override;
	virtual void onPowerOn();
	virtual void onPowerOff();
private:
	void switchPower(OnOffState state);

	/*
	 * Main components
	 */
	BrightnessDriver &brightnessDriver;
	GnulightLightDimmer lightDimmer { brightnessDriver, *this };

	/*
	 * Optional components
	 */
	BatteryMonitor *batteryMonitor = nullptr;
	TempMonitor *tempMonitor = nullptr;

	/*
	 * Modes
	 */
	PowerOffMode powerOffMode {*this};
	ConstantLightMode constantLightMode {*this};
	StrobeMode strobeMode {*this};
	ParameterCheckMode parameterCheckMode {*this};
};

#include "Gnulight_cpp.h"
#include "BrightnessDriver_cpp.h"
#include "GnulightLightDimmer_cpp.h"
#include "ConstantLightMode_cpp.h"
#include "ParameterCheckMode_cpp.h"
#include "PowerOffMode_cpp.h"
#include "StrobeMode_cpp.h"
#include "BatteryMonitor_cpp.h"
#include "TempMonitor_cpp.h"
#include "GnulightCustomizer.h"

#endif
