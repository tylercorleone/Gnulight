#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <DeviceAware.h>
#include <components/Component.h>
#include <task_includer.h>
#include <components/batteries/Battery.h>

class KissLight;

class BatteryMonitor : public Task,
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
