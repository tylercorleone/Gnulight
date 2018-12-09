#ifndef GNULIGHTHELPER_H
#define GNULIGHTHELPER_H

#include "gnulight_config.h"

#include "Gnulight.h"

class GnulightHelper {
public:
	static GnulightHelper customize(Gnulight &gnulight);
	GnulightHelper configureBatteryMonitor(Battery &battery);
	GnulightHelper configureBatteryMonitor(float voltageEmpty,
			float voltageFull, float (*readVoltageFunc)());
	GnulightHelper configureTemperatureMonitor(float (*temperatureReadFunc)());
	Gnulight* build();
private:
	GnulightHelper(Gnulight &instance);
	Gnulight &instance;
};

inline GnulightHelper::GnulightHelper(Gnulight &instance) :
		instance(instance) {

}

inline GnulightHelper GnulightHelper::customize(Gnulight &gnulight) {
	return GnulightHelper { gnulight };
}

inline GnulightHelper GnulightHelper::configureBatteryMonitor(
		Battery &battery) {
	instance.pBatteryMonitor = new BatteryMonitor(instance, battery);
	return *this;
}

inline GnulightHelper GnulightHelper::configureBatteryMonitor(
		float voltageEmpty, float voltageFull, float (*readVoltageFunc)()) {
	LinearCapacityBattery *pBattery = new LinearCapacityBattery(voltageEmpty,
			voltageFull, readVoltageFunc);
	instance.pBatteryMonitor = new BatteryMonitor(instance, *pBattery);
	return *this;
}

inline GnulightHelper GnulightHelper::configureTemperatureMonitor(
		float (*temperatureReadFunc)()) {
	instance.pTempMonitor = new TempMonitor(instance, temperatureReadFunc);
	return *this;
}

#endif
