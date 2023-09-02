#ifndef OFF_MODE_H
#define OFF_MODE_H

#include <Components.h>

class KissLight;

class OffMode : public DeviceAware<KissLight>, public State<ButtonEvent> {
public:
    OffMode(KissLight &kissLight);

protected:
    bool onEntering(ButtonEvent *event) override;

    bool onExiting(ButtonEvent *event) override;

    bool onEventHandling(ButtonEvent *event) override;
};

#endif
