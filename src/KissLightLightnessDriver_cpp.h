#include "KissLightLightnessDriver.h"

inline KissLightLightnessDriver::KissLightLightnessDriver(Potentiometer &lightDriver, TaskManager &taskManager) :
        LightnessDriver(lightDriver, "lightnessDriver", KISS_LIGHT_LOG_LEVEL),
        gradualLevelSetter(GradualPotentiometerActuator(DELAY_BETWEEN_LEVEL_CHANGE,
                                                        taskManager,
                                                        *this,
                                                        Component::getIdentifier(),
                                                        logger.getLogLevel())) {}

inline void KissLightLightnessDriver::setLevel(float level, uint32_t duration) {
    gradualLevelSetter.setLevelGradually(level, duration); // will set the level on this instance itself, gradually
}

inline MainLightLevel KissLightLightnessDriver::getCurrentMainLevel() {
    return mainLightLevels[currentMainLevelIndex];
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float KissLightLightnessDriver::setMainLevel(MainLightLevel level, uint32_t duration) {
    currentMainLevelIndex = level;
    float mainLevel = MAIN_LEVEL;
    logger.info("setting main level %i (%f)", level, mainLevel);
    setLevel(mainLevel, duration);
    return mainLevel;
}

#undef MAIN_LEVEL

inline float KissLightLightnessDriver::setNextMainLevel(uint32_t duration) {
    MainLightLevel nextMainLevel = mainLightLevels[(currentMainLevelIndex + 1)
                                                   % MAIN_LEVELS_COUNT];
    return setMainLevel(nextMainLevel, duration);
}

inline float KissLightLightnessDriver::setNextSubLevel(uint32_t duration) {
    currentSubLevelsIndexes[currentMainLevelIndex] =
            (currentSubLevelsIndexes[currentMainLevelIndex] + 1)
            % SUB_LEVELS_COUNT;
    return setMainLevel(mainLightLevels[currentMainLevelIndex], duration);
}
