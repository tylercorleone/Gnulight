#ifndef KISS_LIGHT_H
#define KISS_LIGHT_H

#include <Components.h>

#include "LightDriver.h"
#include "KissLightLightnessDriver.h"
#include "BatteryMonitor.h"
#include "TempMonitor.h"
#include "light-modes/ConstantLightMode.h"
#include "light-modes/ParameterCheckMode.h"
#include "light-modes/OffMode.h"
#include "light-modes/StrobeMode.h"
#include "KissLightHelper.h"

class KissLight : public Device<ButtonEvent> {
public:
    explicit KissLight(LightDriver &lightDriver);

    void switchTo(OnOffState state);

    OnOffState getPowerState();

    /* Main components */
    Button button{*this, "button"};
    LightDriver &lightDriver;
    KissLightLightnessDriver lightnessDriver{lightDriver, taskManager};

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

#endif
