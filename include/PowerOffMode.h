#ifndef POWEROFFMODE_H
#define POWEROFFMODE_H

#include <Components.h>

class Gnulight;

class PowerOffMode: public State<Gnulight, ButtonEvent> {
public:
	PowerOffMode(Gnulight &gnulight);
protected:
	bool onEnterState() override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
};

#endif
