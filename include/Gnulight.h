#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "gnulight_config.h"

#include <Components.h>
#include <GnulightLightnessDimmer.h>

#include "GnulightLightDriver.h"
#include "ConstantLightMode.h"
#include "ParameterCheckMode.h"
#include "OffMode.h"
#include "StrobeMode.h"
#include "BatteryMonitor.h"
#include "TempMonitor.h"

class Gnulight : public GenericDevice {
	friend class GnulightHelper;
	friend class TempMonitor;
	friend class BatteryMonitor;
	friend class OffMode;
	friend class ConstantLightMode;
	friend class StrobeMode;
	friend class ParameterCheckMode;
public:
	Gnulight(GnulightLightDriver &brightnessDriver, const char *deviceName =
			"Gnulight");
	Button button { *this , " button"};
protected:
	virtual void onSetup() override;
	void setState(OnOffState state);
	virtual void onSwitchOn();
	virtual void onSwitchOff();

	/*
	 * Main components
	 */
	GnulightLightDriver &lightDriver;
	GnulightLightnessDimmer lightnessDimmer { lightDriver, *this };

	/*
	 * Optional components
	 */
	BatteryMonitor *pBatteryMonitor = nullptr;
	TempMonitor *pTempMonitor = nullptr;

	/*
	 * Modes
	 */
	OffMode offMode {*this};
	ConstantLightMode constantLightMode {*this};
	StrobeMode strobeMode {*this};
	ParameterCheckMode parameterCheckMode {*this};
};

#include "Gnulight_cpp.h"
#include "GnulightLightDriver_cpp.h"
#include <GnulightLightnessDimmer_cpp.h>
#include "ConstantLightMode_cpp.h"
#include "ParameterCheckMode_cpp.h"
#include "OffMode_cpp.h"
#include "StrobeMode_cpp.h"
#include "BatteryMonitor_cpp.h"
#include "TempMonitor_cpp.h"
#include "GnulightHelper.h"

#endif
