#include "KissLightLightnessDriver.h"

inline KissLightLightnessDriver::KissLightLightnessDriver(LightDriver &lightDriver, TaskManager &taskManager) :
        LightnessDriver(DELAY_BETWEEN_LEVEL_CHANGE_MS, taskManager, lightDriver, "lightnessDriver",
                        KISS_LIGHT_DEFAULT_APPENDER_LEVEL) {}

inline MainLightLevel KissLightLightnessDriver::getCurrentMainLevel() {
    return mainLightLevels[currentMainLevelIndex];
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

inline float KissLightLightnessDriver::setMainLevel(MainLightLevel level, uint32_t duration) {
    currentMainLevelIndex = level;
    float mainLevel = MAIN_LEVEL;
    logger.info("setting main level %i (%f)", level, mainLevel);
    setLevelGradually(mainLevel, duration);
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
