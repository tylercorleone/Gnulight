#ifndef GNULIGHTLIGHTDIMMER_H
#define GNULIGHTLIGHTDIMMER_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>

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
			LEVEL_LOW_1, LEVEL_LOW_2 }, { LEVEL_MED_1, LEVEL_MED_2 }, { LEVEL_HIGH_1, LEVEL_HIGH_2 } };
};

#endif
