#ifndef GNULIGHTLIGHTDRIVER_H
#define GNULIGHTLIGHTDRIVER_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>

class GnulightLightDriver: public CappablePotentiometer {
	friend class Gnulight;
public:
	GnulightLightDriver(const char *name = "lightDrv");
	void updateLevelMaxLimit();
	void setBatteryCausedLimit(float limit);
	void setTemperatureCausedLimit(float limit);
private:
	float battCausedLimit = 1.0f;
	float tempCausedLimit = 1.0f;
	GradualCappablePotentiometerActuator *maxBrightnessSetter;
};

#endif
