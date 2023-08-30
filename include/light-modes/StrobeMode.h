#ifndef STROBEMODE_H
#define STROBEMODE_H

#include "config.h"

#include "Components.h"

class KissLight;

#define SIGNAL_TYPES_COUNT 3

class StrobeMode: public State<KissLight, ButtonEvent> {
public:
	StrobeMode(KissLight &kissLight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
	void startStrobe();
	const SignalType signalTypes[SIGNAL_TYPES_COUNT] = {
			SignalType::SINUSOIDAL_WAVE, SignalType::TRIANGULAR_WAVE,
			SignalType::SQUARE_WAVE };
	SignalGenerator *signalGenerator;
	float levelMax = 0.0f;
	uint8_t strobeIndex = 0;
	uint16_t periodMultiplierX1000 = 1000UL;
};

#endif
