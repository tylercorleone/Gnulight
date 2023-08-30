#include "KissLightLightnessDimmer.h"

inline void powerOffKissLight(KissLight *kissLight) {
	kissLight->enterState(kissLight->offMode);
}

inline KissLightLightnessDimmer::KissLightLightnessDimmer(
		Potentiometer &brightnessPotentiometer, KissLight &kissLight) :
		LightnessDimmer(brightnessPotentiometer, "lightnessDimmer"), DeviceAware(
				kissLight) {
	gradualLevelSetter = new GradualPotentiometerActuator(
			DELAY_BETWEEN_LEVEL_CHANGE, Device().getTaskManager(), *this);
}

inline void KissLightLightnessDimmer::setLevel(float level, uint32_t duration) {
	gradualLevelSetter->setLevel(level, duration);
}

inline MainLightLevel KissLightLightnessDimmer::getCurrentMainLevel() {
	return mainLightLevels[currentMainLevelIndex];
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float KissLightLightnessDimmer::setMainLevel(MainLightLevel levelIndex,
		uint32_t duration) {
	currentMainLevelIndex = levelIndex;
	setLevel(MAIN_LEVEL, duration);
	return MAIN_LEVEL;
}

#undef MAIN_LEVEL

inline float KissLightLightnessDimmer::setNextMainLevel(uint32_t duration) {
	MainLightLevel nextMainLevel = mainLightLevels[(currentMainLevelIndex + 1)
			% MAIN_LEVELS_COUNT];
	return setMainLevel(nextMainLevel, duration);
}

inline float KissLightLightnessDimmer::setNextSubLevel(uint32_t duration) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1)
					% SUBLEVELS_COUNT;
	return setMainLevel(mainLightLevels[currentMainLevelIndex], duration);
}
