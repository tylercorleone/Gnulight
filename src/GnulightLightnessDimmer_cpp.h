#include "GnulightLightnessDimmer.h"

inline GnulightLightnessDimmer::GnulightLightnessDimmer(
		Potentiometer &brightnessPotentiometer, TaskManager &taskManager) :
		LightnessDimmer(brightnessPotentiometer, "lnssDimm") {
	gradualLevelSetter = new GradualPotentiometerActuator(DELAY_BETWEEN_LEVEL_CHANGE, taskManager, *this);
}

inline void GnulightLightnessDimmer::setLevel(float level, uint32_t duration) {
	debugIfNamed("setLevel(%f, %u)", level, duration);

	gradualLevelSetter->setLevel(level, duration);
}

inline MainLightLevel GnulightLightnessDimmer::getCurrentMainLevel() {
	return mainLightLevels[currentMainLevelIndex];
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float GnulightLightnessDimmer::setMainLevel(MainLightLevel levelIndex,
		uint32_t duration) {
	currentMainLevelIndex = levelIndex;
	setLevel(MAIN_LEVEL, duration);
	return MAIN_LEVEL;
}

#undef MAIN_LEVEL

inline float GnulightLightnessDimmer::setNextMainLevel(uint32_t duration) {
	MainLightLevel nextMainLevel = mainLightLevels[(currentMainLevelIndex + 1)
			% MAIN_LEVELS_COUNT];
	return setMainLevel(nextMainLevel, duration);
}

inline float GnulightLightnessDimmer::setNextSubLevel(uint32_t duration) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1)
					% SUBLEVELS_COUNT;
	return setMainLevel(mainLightLevels[currentMainLevelIndex], duration);
}
