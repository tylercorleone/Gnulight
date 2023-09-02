#ifndef CONSTANT_LIGHT_MODE_H
#define CONSTANT_LIGHT_MODE_H

#include "config.h"

#include "Components.h"

class KissLight;

class ConstantLightMode : public DeviceAware<KissLight>, public State<ButtonEvent> {
public:
    ConstantLightMode(KissLight &kissLight);

protected:
    virtual bool onEntering(ButtonEvent *event) override;

    virtual bool onEventHandling(ButtonEvent *event) override;
};

#endif
