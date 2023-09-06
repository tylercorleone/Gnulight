#ifndef PARAMETER_CHECK_MODE_H
#define PARAMETER_CHECK_MODE_H

#include <Components.h>

class KissLight;

class ParameterCheckMode : public DeviceAware<KissLight>, public State<ButtonEvent>, private Task {
public:
    static ButtonEvent BATTERY_CHECK_MSG;
    static ButtonEvent LAMP_TEMPERATURE_CHECK_MSG;

    explicit ParameterCheckMode(KissLight &kissLight);

protected:
    bool onEntering(ButtonEvent *event) override;

    bool onExiting(ButtonEvent *event) override;

    void OnUpdate(uint32_t deltaTime) override;

    int8_t strobesForIntegerPartCount = 0;
    int8_t strobesForDecimalPartCount = 0;
};

#endif
