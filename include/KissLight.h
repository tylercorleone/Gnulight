#ifndef KISS_LIGHT_H
#define KISS_LIGHT_H

#include "config.h"

#include <Components.h>
#include <KissLightLightnessDimmer.h>

#include "LightDriver.h"
#include "light-modes/ConstantLightMode.h"
#include "light-modes/ParameterCheckMode.h"
#include "light-modes/OffMode.h"
#include "light-modes/StrobeMode.h"
#include "BatteryMonitor.h"
#include "TempMonitor.h"

class KissLight : public Device<ButtonEvent> {
public:
    KissLight(LightDriver &lightDriver, const char *name = "KissLight");

    void switchTo(OnOffState state);

    OnOffState getPowerState();

    /* Main components */
    Button button{*this, "button"};
    LightDriver &lightDriver;
    KissLightLightnessDimmer lightnessDimmer{lightDriver, *this};

    /* Optional components */
    BatteryMonitor *pBatteryMonitor = nullptr;
    TempMonitor *pTempMonitor = nullptr;

    /* Function modes */
    OffMode offMode{*this};
    ConstantLightMode constantLightMode{*this};
    StrobeMode strobeMode{*this};
    ParameterCheckMode parameterCheckMode{*this};
protected:
    virtual void onSwitchOn() {}; // to customize the switch on phase

    virtual void onSwitchOff() {}; // to customize the switch off phase

private:
    OnOffState currentPowerState = OnOffState::OFF;
};

#include "KissLight_cpp.h"
#include "LightDriver_cpp.h"
#include <KissLightLightnessDimmer_cpp.h>
#include "light-modes/ConstantLightMode_cpp.h"
#include "light-modes/ParameterCheckMode_cpp.h"
#include "light-modes/OffMode_cpp.h"
#include "light-modes/StrobeMode_cpp.h"
#include "BatteryMonitor_cpp.h"
#include "TempMonitor_cpp.h"
#include "KissLightHelper.h"

#endif
