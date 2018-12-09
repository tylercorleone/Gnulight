#ifndef OFFMODE_H
#define OFFMODE_H

#include <Components.h>

class Gnulight;

class OffMode: public State<Gnulight, ButtonEvent> {
public:
	OffMode(Gnulight &gnulight);
protected:
	bool onEnterState() override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
};

#endif
