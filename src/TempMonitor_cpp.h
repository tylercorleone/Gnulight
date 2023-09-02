#include "TempMonitor.h"
#include <float.h>

inline TempMonitor::TempMonitor(KissLight &kissLight,
                                float (*temperatureReadFunction)() = nullptr) :
        Task(MsToTaskTime(TEMP_MONITOR_INTERVAL_MS)), DeviceAware(kissLight), Component(
        " tempMon"), readTemperature(temperatureReadFunction) {
}

inline bool TempMonitor::OnStart() {
    temperatureErrorIntegral = 0.0f;
    temperatureError_1 = temperatureError_2 = FLT_MAX;
    tempCausedLimit = 1.0f;
    setRemainingTime(0);
    return true;
}

inline void TempMonitor::OnStop() {
    getDevice().lightDriver.setTemperatureCausedLimit(1.0f);
}

inline void TempMonitor::OnUpdate(uint32_t deltaTime) {
    if (getDevice().lightDriver.getLevel()
        >= TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD) {

        float temperature = readTemperature();
        logger.debug("%f deg.", temperature);

        tempCausedLimit = TEMP_TO_LIGHT_LIMIT(temperature);
        getDevice().lightDriver.setTemperatureCausedLimit(tempCausedLimit);
    }
}

inline float TempMonitor::temperatureToLightLimit(float temperature) {
    float limit = tempCausedLimit * (1.0f + getTemperaturePIDVar(temperature));
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

    logger.trace("P: %f, I: %f, D: %f", Kp * temperatureError, Ki * temperatureErrorIntegral, Kd * derivative);

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

