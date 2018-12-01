#ifndef CONSTANTLIGHTMODE_H
#define CONSTANTLIGHTMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

class ConstantLightMode: public State<Gnulight, ButtonEvent> {
public:
	ConstantLightMode(Gnulight &gnulight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	bool handleEvent(const ButtonEvent &event) override;
};

#endif
