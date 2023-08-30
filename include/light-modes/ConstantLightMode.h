#ifndef CONSTANTLIGHTMODE_H
#define CONSTANTLIGHTMODE_H

#include "config.h"

#include "Components.h"

class KissLight;

class ConstantLightMode: public State<KissLight, ButtonEvent> {
public:
	ConstantLightMode(KissLight &kissLight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	bool handleEvent(const ButtonEvent &event) override;
};

#endif
