#ifndef STROBEMODE_H
#define STROBEMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

#define STROBE_TYPES_COUNT 5

enum StrobeTypes {
	SINUSOIDAL_WAVE, TRIANGULAR_WAVE, ON_OFF_STROBE, BEACON_STROBE, DISCO_STROBE
};

class StrobeMode: public State<Gnulight, ButtonEvent> {
public:
	StrobeMode(Gnulight &gnulight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
	static uint32_t onUpdate(StrobeMode *_this);
	static float sinWave(uint32_t millis, uint32_t periodMs);
	static float triangularWave(uint32_t millis, uint32_t periodMs);
	Procedure &toggleLightStatusTask = ProcedureBuilder::begin(
			StrobeMode::onUpdate, this).thenRepeat();
	const StrobeTypes strobes[STROBE_TYPES_COUNT] = { SINUSOIDAL_WAVE,
			TRIANGULAR_WAVE, ON_OFF_STROBE, BEACON_STROBE, DISCO_STROBE };
	uint8_t strobeIndex = 0;
	uint32_t t_0 = -1;
	float waveMaxLevel = 0.0;
	uint16_t periodMultiplierX1000 = 1000UL;
};

#endif
