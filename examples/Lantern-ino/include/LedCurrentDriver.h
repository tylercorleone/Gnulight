#ifndef LEDCURRENTDRIVER_H
#define LEDCURRENTDRIVER_H

#include "custom_kisslight.h"

class LedCurrentDriver: public KissLightLightDriver {
public:
	LedCurrentDriver();
	void setup();
	void onSetLevel(float level) override;
};

#endif
