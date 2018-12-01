#include "GnulightLightDimmer.h"

inline GnulightLightDimmer::GnulightLightDimmer(Potentiometer &brightnessPotentiometer,
		TaskManager &taskManager) :
		LightDimmer(brightnessPotentiometer) {
	setName("lightDrv");

	gradualLevelSetter = new GradualPotentiometerActuator(
			MsToTaskTime(DELAY_BETWEEN_LEVEL_CHANGE_MS), taskManager, *this);
}

inline void GnulightLightDimmer::setLevel(float level, uint32_t transitionDurationMs) {
	traceIfNamed("setLevel(%f, %u)", level, transitionDurationMs);

	gradualLevelSetter->setLevel(level, transitionDurationMs);
}

inline LightLevelIndex GnulightLightDimmer::getCurrentMainLevel() {
	return currentMainLevelIndex;
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float GnulightLightDimmer::setMainLevel(LightLevelIndex levelIndex,
		uint32_t transitionDurationMs) {
	currentMainLevelIndex = levelIndex;
	setLevel(MAIN_LEVEL, transitionDurationMs);
	return MAIN_LEVEL;
}

#undef MAIN_LEVEL

inline float GnulightLightDimmer::setNextMainLevel(uint32_t transitionDurationMs) {
	return setMainLevel((currentMainLevelIndex + 1) % MAIN_LEVELS_NUM,
			transitionDurationMs);

}

inline float GnulightLightDimmer::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1) % SUBLEVELS_NUM;
	return setMainLevel(currentMainLevelIndex, transitionDurationMs);
}
