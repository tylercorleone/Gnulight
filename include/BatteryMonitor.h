#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include "config.h"

#include <Components.h>
#include <stdint.h>
#include <stddef.h>
#include <Task.h>

class KissLight;

class BatteryMonitor: public Task,
		public DeviceAware<KissLight>,
		public Component {
public:
	BatteryMonitor(KissLight &kissLight, Battery &battery);
	const Battery &battery;
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	virtual void onEmptyBattery();
	float remainingChargeCausingStepdown = 1.0f;
};

#endif
