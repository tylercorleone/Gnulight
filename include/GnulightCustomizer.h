#ifndef GNULIGHTCUSTOMIZER_H
#define GNULIGHTCUSTOMIZER_H

#include "gnulight_config.h"

#include "Gnulight.h"

class GnulightCustomizer {
public:
	static GnulightCustomizer customize(Gnulight &gnulight);
	GnulightCustomizer setBattery(Battery &battery);
	GnulightCustomizer setTemperatureReadFunction(float (*temperatureReadFunction)());
	Gnulight* build();
private:
	GnulightCustomizer(Gnulight &instance);
	Gnulight &instance;
};

inline GnulightCustomizer::GnulightCustomizer(Gnulight &instance) :
		instance(instance) {

}

inline GnulightCustomizer GnulightCustomizer::customize(Gnulight &gnulight) {
	return GnulightCustomizer { gnulight };
}

inline GnulightCustomizer GnulightCustomizer::setTemperatureReadFunction(
		float (*temperatureReadFunction)()) {
	instance.tempMonitor = new TempMonitor(instance,
			temperatureReadFunction);
	return *this;
}

inline GnulightCustomizer GnulightCustomizer::setBattery(Battery &battery) {
	instance.batteryMonitor = new BatteryMonitor(instance, battery);
	return *this;
}

#endif
