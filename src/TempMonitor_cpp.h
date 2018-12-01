#include "TempMonitor.h"
#include <float.h>

inline TempMonitor::TempMonitor(Gnulight &gnulight,
		float (*temperatureReadFunction)() = nullptr) :
		Task(MsToTaskTime(TEMP_MONITOR_INTERVAL_MS)), DeviceAware(gnulight), Named(
				"lightMonitor"), readTemperature(temperatureReadFunction) {
}

inline bool TempMonitor::OnStart() {
	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	tempCausedLimit = 1.0f;
	OnUpdate(0);
	return true;
}

inline void TempMonitor::OnStop() {
	Device().brightnessDriver.setTemperatureCausedLimit(1.0f);
}

inline void TempMonitor::OnUpdate(uint32_t deltaTime) {
	if (Device().brightnessDriver.getLevel()
			>= TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD) {
		float temperature = readTemperature();
		tempCausedLimit = calculateTemperatureCurrentLimit(temperature);

		debugIfNamed("temp.: %f, limit: %f", temperature, tempCausedLimit);

		Device().brightnessDriver.setTemperatureCausedLimit(tempCausedLimit);
	}
}

inline float TempMonitor::calculateTemperatureCurrentLimit(float temperature) {
	float PIDvar = getTemperaturePIDVar(temperature);
	float limit = tempCausedLimit * (1.0f + PIDvar);

	traceIfNamed("PID: %f", PIDvar);

	return _constrain(limit, 0.0f, 1.0f);
}

inline float TempMonitor::getTemperaturePIDVar(float temperature) {
	float dt = TEMP_MONITOR_INTERVAL_MS / 1000.0f;

	float temperatureError = TEMP_MONITOR_EMITTER_TARGET_TEMPERATURE - temperature;

	temperatureErrorIntegral += temperatureError * dt;
	temperatureErrorIntegral = _constrain(temperatureErrorIntegral,
			-TEMP_MONITOR_TEMP_INTEGRAL_MAX, TEMP_MONITOR_TEMP_INTEGRAL_MAX);

	float derivative = calculateDerivate(temperatureError, temperatureError_1,
			temperatureError_2, dt);

	temperatureError_2 = temperatureError_1;
	temperatureError_1 = temperatureError;

	traceIfNamed("P: %f, I: %f, D: %f", Kp * temperatureError, Ki * temperatureErrorIntegral, Kd * derivative);

	return Kp * temperatureError + Ki * temperatureErrorIntegral
			+ Kd * derivative;
}

inline float TempMonitor::calculateDerivate(float f_t, float f_t_1, float f_t_2,
		float dt) {
	if (f_t_2 == FLT_MAX) {
		if (f_t_1 == FLT_MAX) {
			return 0.0f;
		} else {
			return (f_t - f_t_1) / dt;
		}
	}
	return (3.0f * f_t - 4.0f * f_t_1 + f_t_2) / (2.0f * dt);
}

