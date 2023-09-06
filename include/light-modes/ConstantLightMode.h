#ifndef CONSTANT_LIGHT_MODE_H
#define CONSTANT_LIGHT_MODE_H

#include <Components.h>

class KissLight;

class ConstantLightMode : public DeviceAware<KissLight>, public State<ButtonEvent> {
public:
    explicit ConstantLightMode(KissLight &kissLight);

protected:
    bool onEntering(ButtonEvent *event) override;

    bool onEventHandling(ButtonEvent *event) override;
};

#endif
