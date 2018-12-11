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
public:
	Gnulight(GnulightLightDriver &lightDriver, const char *name = "Gnulight");
	void setState(OnOffState state);
	OnOffState getState();

	/* Main components */
	Button button { *this , " button"};
	GnulightLightDriver &lightDriver;
	GnulightLightnessDimmer lightnessDimmer { lightDriver, taskManager };

	/* Optional components */
	BatteryMonitor *pBatteryMonitor = nullptr;
	TempMonitor *pTempMonitor = nullptr;

	/* Function modes */
	OffMode offMode {*this};
	ConstantLightMode constantLightMode {*this};
	StrobeMode strobeMode {*this};
	ParameterCheckMode parameterCheckMode {*this};
protected:
	virtual void onSetup() override;
	virtual void onSwitchOn();
	virtual void onSwitchOff();
private:
	OnOffState powerState = OnOffState::OFF;
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
