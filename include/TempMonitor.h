#ifndef LIGHTMONITOR_H
#define LIGHTMONITOR_H

#include "gnulight_config.h"

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include <Components.h>

class Gnulight;

#define TEMP_MONITOR_INTERVAL_MS 10000
#define EMITTER_TARGET_TEMPERATURE 50.0f
#define TEMPERATURE_MAX_ERROR 500.0f
#define CURRENT_ACTIVATION_THRESHOLD 0.2f

class TempMonitor: public Task, public DeviceAware<Gnulight>, public Named {
public:
	TempMonitor(Gnulight &gnulight, float (*temperatureReadFunction)());
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	float (*readTemperature)();
private:
	float calculateTemperatureCurrentLimit(float temperature);
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
