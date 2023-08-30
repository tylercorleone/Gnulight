#ifndef KISS_LIGHT_H
#define KISS_LIGHT_H

#include "config.h"

#include <Components.h>
#include <KissLightLightnessDimmer.h>

#include "KissLightLightDriver.h"
#include "light-modes/ConstantLightMode.h"
#include "light-modes/ParameterCheckMode.h"
#include "OffMode.h"
#include "light-modes/StrobeMode.h"
#include "BatteryMonitor.h"
#include "TempMonitor.h"

class KissLight : public GenericDevice {
public:
	KissLight(KissLightLightDriver &lightDriver, const char *name = "KissLight");
	void setState(OnOffState state);
	OnOffState getState();

	/* Main components */
	Button button { *this, "  button" };
	KissLightLightDriver &lightDriver;
	KissLightLightnessDimmer lightnessDimmer { lightDriver, *this };

	/* Optional components */
	BatteryMonitor *pBatteryMonitor = nullptr;
	TempMonitor *pTempMonitor = nullptr;

	/* Function modes */
	OffMode offMode { *this };
	ConstantLightMode constantLightMode { *this };
	StrobeMode strobeMode { *this };
	ParameterCheckMode parameterCheckMode { *this };
protected:
	virtual void onSetup() override;
	virtual void onSwitchOn();
	virtual void onSwitchOff();
private:
	OnOffState powerState = OnOffState::OFF;
};

#include "KissLight_cpp.h"
#include "KissLightLightDriver_cpp.h"
#include <KissLightLightnessDimmer_cpp.h>
#include "light-modes/ConstantLightMode_cpp.h"
#include "light-modes/ParameterCheckMode_cpp.h"
#include "OffMode_cpp.h"
#include "light-modes/StrobeMode_cpp.h"
#include "BatteryMonitor_cpp.h"
#include "TempMonitor_cpp.h"
#include "KissLightHelper.h"

#endif
