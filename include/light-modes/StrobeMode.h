#ifndef STROBE_MODE_H
#define STROBE_MODE_H

#include "Components.h"

class KissLight;

#define SIGNAL_TYPES_COUNT 3

class StrobeMode : public DeviceAware<KissLight>, public State<ButtonEvent> {
public:
    explicit StrobeMode(KissLight &kissLight);

protected:
    bool onEntering(ButtonEvent *event) override;

    bool onExiting(ButtonEvent *event) override;

    bool onEventHandling(ButtonEvent *event) override;

    void setupStrobe();

    const SignalType signalTypes[SIGNAL_TYPES_COUNT] = {
            SignalType::SINUSOIDAL_WAVE,
            SignalType::TRIANGULAR_WAVE,
            SignalType::SQUARE_WAVE};
    SignalGenerator signalGenerator;
    float levelMax = 0.0f;
    uint8_t signalTypeIndex = 0;
    uint16_t periodMultiplierX1000 = 1000UL;
};

#endif
