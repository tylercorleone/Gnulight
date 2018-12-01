#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>
#include <stddef.h>
#include <Task.h>

class Gnulight;

class BatteryMonitor: public Task, public DeviceAware<Gnulight>, public Named {
public:
	BatteryMonitor(Gnulight &gnulight, Battery &battery);
	const Battery &battery;
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	float calculateInstantaneousMaxCurrent(float remainingCharge);
	void onEmptyBattery();
	float remainingChargeCausingStepdown = 1.0f;
};

#endif
