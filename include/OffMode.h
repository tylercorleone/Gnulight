#ifndef OFFMODE_H
#define OFFMODE_H

#include <Components.h>

class KissLight;

class OffMode: public State<KissLight, ButtonEvent> {
public:
	OffMode(KissLight &kissLight);
protected:
	bool onEnterState() override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
};

#endif
