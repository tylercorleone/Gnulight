#include "GnulightLightnessDimmer.h"

inline void powerOffGnulight(Gnulight *gnulight) {
	gnulight->enterState(gnulight->offMode);
}

inline GnulightLightnessDimmer::GnulightLightnessDimmer(
		Potentiometer &brightnessPotentiometer, Gnulight &gnulight) :
		LightnessDimmer(brightnessPotentiometer, "lnssDimm"), DeviceAware(
				gnulight) {
	gradualLevelSetter = new GradualPotentiometerActuator(
			DELAY_BETWEEN_LEVEL_CHANGE, Device().getTaskManager(), *this);
	RunnableFunction *downShutter = new RunnableFunction(powerOffGnulight,
			&Device());
	gradualLevelSetter->then(*downShutter);
}

inline void GnulightLightnessDimmer::setLevel(float level, uint32_t duration) {
	logger.debug("setLevel(%f, %u)", level, duration);
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

inline void GnulightLightnessDimmer::dimThenShutdown(uint32_t duration) {
	gradualLevelSetter->setLevel(0.0f, duration, false);
}
