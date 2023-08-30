#ifndef LIGHTMONITOR_H
#define LIGHTMONITOR_H

#include "config.h"

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include <Components.h>

class KissLight;

#define TEMP_MONITOR_TEMP_INTEGRAL_MAX 500.0f

class TempMonitor: public Task, public DeviceAware<KissLight>, public Component {
public:
	TempMonitor(KissLight &kissLight, float (*temperatureReadFunction)());
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	float (*readTemperature)();
private:
	float temperatureToLightLimit(float temperature);
	float getTemperaturePIDVar(float temperature);
	float calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt);
	float temperatureErrorIntegral;
	float temperatureError_1, temperatureError_2;
	float Kp = 0.001f;
	float Ki = 0.000015f;
	float Kd = 0.5f;
	float tempCausedLimit = 1.0f;
};

#endif
