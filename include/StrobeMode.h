#ifndef STROBEMODE_H
#define STROBEMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

#define STROBE_TYPES_COUNT 5

#define ON_OFF_STROBE_PERIOD_MS 500UL
#define BEACON_STROBE_PERIOD_MS 4000UL
#define BEACON_STROBE_DUTY_CYCLE 0.01
#define DISCO_STROBE_PERIOD_MS 80UL
#define DISCO_STROBE_DUTY_CYCLE 0.2
#define LEVEL_REFRESH_INTERVAL_MS 30UL

#define PERIODICAL_SEQUENCE_STROBES_PERIOD_MS 2000UL

#define MIN_POTENTIOMETER_LEVEL MIN_LIGHT_CURRENT_ABOVE_ZERO

enum StrobeTypes {
	SINUSOIDAL_STROBE = 0,
	LINEAR_STROBE = 1,
	ON_OFF_STROBE = 2,
	BEACON_STROBE = 3,
	DISCO_STROBE = 4
};

class StrobeMode: public State<Gnulight, ButtonEvent> {
public:
	StrobeMode(Gnulight &gnulight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
	static uint32_t switchLightStatus(StrobeMode *_this);
	static float sinWave(uint32_t millis, uint32_t periodMs);
	static float triangularWave(uint32_t millis, uint32_t periodMs);
	FunctionsSequenceTask& toggleLightStatusTask = SequenceTaskBuilder::begin(
			StrobeMode::switchLightStatus, this).thenRepeat();
	StrobeTypes currentStrobeType = SINUSOIDAL_STROBE;
	float varName = 0.0;
	uint16_t periodMultiplierX1000 = 1000UL;
};

#endif
