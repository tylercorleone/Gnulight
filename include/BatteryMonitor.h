#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>
#include <stddef.h>
#include <Task.h>

class Gnulight;

class BatteryMonitor: public Task,
		public DeviceAware<Gnulight>,
		public Component {
public:
	BatteryMonitor(Gnulight &gnulight, Battery &battery);
	const Battery &battery;
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	virtual void onEmptyBattery();
	float remainingChargeCausingStepdown = 1.0f;
};

#endif
