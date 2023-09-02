#include "KissLightLightnessDimmer.h"

inline KissLightLightnessDimmer::KissLightLightnessDimmer(KissLight &kissLight) :
        LightnessDimmer(kissLight.lightDriver, "lightnessDimmer", KISS_LIGHT_LOG_LEVEL),
        DeviceAware(kissLight) {
    gradualLevelSetter = new GradualPotentiometerActuator(DELAY_BETWEEN_LEVEL_CHANGE,
                                                          getDevice().getTaskManager(),
                                                          *this,
                                                          "lightnessActuator",
                                                          KISS_LIGHT_LOG_LEVEL);
}

inline void KissLightLightnessDimmer::setLevel(float level, uint32_t duration) {
    gradualLevelSetter->setLevelGradually(level, duration); // will set the level on this instance itself, gradually
}

inline MainLightLevel KissLightLightnessDimmer::getCurrentMainLevel() {
    return mainLightLevels[currentMainLevelIndex];
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float KissLightLightnessDimmer::setMainLevel(MainLightLevel level, uint32_t duration) {
    currentMainLevelIndex = level;
    float mainLevel = MAIN_LEVEL;
    logger.info("setting main level %i (%f)", level, mainLevel);
    setLevel(mainLevel, duration);
    return mainLevel;
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
