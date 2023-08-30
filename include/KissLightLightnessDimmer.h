#ifndef KISS_LIGHT_LIGHTNESS_DIMMER_H
#define KISS_LIGHT_LIGHTNESS_DIMMER_H

#include "config.h"

#include <Components.h>
#include <stdint.h>

#define MAIN_LEVELS_COUNT 3
#define SUBLEVELS_COUNT 2

enum MainLightLevel {
	MIN, MED, MAX
};

class KissLight;

class KissLightLightnessDimmer: public LightnessDimmer, public DeviceAware<KissLight> {
public:
	KissLightLightnessDimmer(Potentiometer &currentPotentiometer, KissLight &kissLight);
	using LightnessDimmer::setLevel;
	void setLevel(float level, uint32_t duration);
	MainLightLevel getCurrentMainLevel();
	float setMainLevel(MainLightLevel, uint32_t duration = 0);
	float setNextMainLevel(uint32_t duration = 0);
	float setNextSubLevel(uint32_t duration = 0);
protected:
	MainLightLevel mainLightLevels[MAIN_LEVELS_COUNT] = { MainLightLevel::MIN,
			MainLightLevel::MED, MainLightLevel::MAX };
	int currentMainLevelIndex = 2;
	GradualPotentiometerActuator *gradualLevelSetter;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_COUNT] = { 0, 0, 0 };
	const float mainLevels[MAIN_LEVELS_COUNT][SUBLEVELS_COUNT] = { {
			LEVEL_LOW_1, LEVEL_LOW_2 }, { LEVEL_MED_1, LEVEL_MED_2 }, { LEVEL_HIGH_1, LEVEL_HIGH_2 } };
};

#endif
