#ifndef GNULIGHTLIGHTDIMMER_H
#define GNULIGHTLIGHTDIMMER_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>

#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.00035f
#define MAIN_LEVELS_NUM 3
#define SUBLEVELS_NUM 2

enum LightLevelIndex {
	MIN, MED, MAX
};

class GnulightLightDimmer: public LightDimmer {
public:
	GnulightLightDimmer(Potentiometer &currentPotentiometer, TaskManager &taskManager);
	using LightDimmer::setLevel;
	void setLevel(float level, uint32_t transitionDurationMs);
	LightLevelIndex getCurrentMainLevel();
	float setMainLevel(LightLevelIndex, uint32_t transitionDurationMs = 0);
	float setNextMainLevel(uint32_t transitionDurationMs = 0);
	float setNextSubLevel(uint32_t transitionDurationMs = 0);
protected:
	LightLevelIndex currentMainLevelIndex = LightLevelIndex::MAX;
	GradualPotentiometerActuator *gradualLevelSetter;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { {
			MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f }, { 0.2f, 0.5f }, { 0.75f, 1.0f } };
};

#endif
