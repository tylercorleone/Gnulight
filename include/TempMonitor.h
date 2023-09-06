#ifndef TEMP_MONITOR_H
#define TEMP_MONITOR_H

#include <Components.h>

class KissLight;

class TempMonitor : public Task, public DeviceAware<KissLight>, public Component {
public:
    TempMonitor(KissLight &kissLight, float (*temperatureReadFunction)());

    bool OnStart() override;

    void OnStop() override;

    void OnUpdate(uint32_t deltaTime) override;

    float (*readTemperature)();

private:
    float temperatureToLightLimit(float temperature);

    float getTemperaturePIDVar(float temperature);

    float temperatureErrorIntegral = -1;
    float temperatureError_1 = -1;
    float temperatureError_2 = -1;
    float Kp = 0.001f;
    float Ki = 0.000015f;
    float Kd = 0.5f;
    float tempCausedLimit = 1.0f;
};

#endif
