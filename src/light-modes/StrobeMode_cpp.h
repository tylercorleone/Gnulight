#include "light-modes/StrobeMode.h"

inline StrobeMode::StrobeMode(KissLight &kissLight) :
        DeviceAware(kissLight),
        State("StrobeMode", KISS_LIGHT_LOG_LEVEL),
        signalGenerator(SignalGenerator(kissLight.getTaskManager(),
                                        kissLight.lightnessDriver,
                                        MsToTaskTime(STROBE_LEVEL_REFRESH_INTERVAL_MS),
                                        State<ButtonEvent>::getIdentifier(),
                                        logger.getLogLevel())) {}

#define THE_PERIOD MsToTaskTime(((uint32_t) STROBE_PERIODICAL_SEQUENCE_PERIOD_MS * periodMultiplierX1000) / 1000)

inline bool StrobeMode::onEntering(ButtonEvent *event) {
    // light should already be OFF
    levelMax = getDevice().lightnessDriver.setMainLevel(
            getDevice().lightnessDriver.getCurrentMainLevel()); // this doesn't turn the light ON, just used to read the level
    getDevice().lightnessDriver.setLevel(0.0f);
    setupStrobe();
    getDevice().lightnessDriver.setState(OnOffState::ON);
    return true;
}

inline bool StrobeMode::onExiting(ButtonEvent *event) {
    signalGenerator.stop();
    return true;
}

inline bool StrobeMode::onEventHandling(ButtonEvent *event) {
    switch (event->getClicksCount()) {
        case 0:
            // long press
            levelMax = getDevice().lightnessDriver.setNextMainLevel();
            break;
        case 1:
            getDevice().enterState(getDevice().offMode);
            return true;
        case 2:
            signalTypeIndex = (signalTypeIndex + 1) % SIGNAL_TYPES_COUNT;
            break;
        case 3:
            if (periodMultiplierX1000 <= 32000) {
                periodMultiplierX1000 *= 2;
            }
            break;
        case 4:
            if (periodMultiplierX1000 > 125) {
                periodMultiplierX1000 /= 2;
            }
            break;
        default:
            return false;
    }

    setupStrobe();
    return true;
}

inline void StrobeMode::setupStrobe() {
    float maxLevel = _max(LEVEL_LOW_2, levelMax);

    switch (signalTypes[signalTypeIndex]) {
        case SignalType::TRIANGULAR_WAVE:
            signalGenerator.triangularWave(LEVEL_LOW_1, maxLevel, THE_PERIOD);
            break;
        case SignalType::SINUSOIDAL_WAVE:
            signalGenerator.triangularWave(LEVEL_LOW_1, maxLevel, THE_PERIOD);
            break;
        default:
            signalGenerator.triangularWave(LEVEL_LOW_1, maxLevel, THE_PERIOD);
    }
}

#undef THE_PERIOD
