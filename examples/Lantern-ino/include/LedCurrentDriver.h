#ifndef LEDCURRENTDRIVER_H
#define LEDCURRENTDRIVER_H

#include "custom_gnulight.h"

class LedCurrentDriver: public GnulightLightDriver {
public:
	LedCurrentDriver();
	void setup();
	void onSetLevel(float level) override;
};

#endif
