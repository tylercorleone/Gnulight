#include "light-modes/StrobeMode.h"

inline StrobeMode::StrobeMode(KissLight &kissLight) :
        DeviceAware(kissLight),
        State("StrobeMode") {
    signalGenerator = new SignalGenerator(kissLight.getTaskManager(),
                                          kissLight.lightnessDimmer,
                                          MsToTaskTime(STROBE_LEVEL_REFRESH_INTERVAL_MS));
}

#define THE_PERIOD MsToTaskTime(((uint32_t) STROBE_PERIODICAL_SEQUENCE_PERIOD_MS * periodMultiplierX1000) / 1000)

inline bool StrobeMode::onEntering(ButtonEvent *event) {
    // light should already be OFF
    levelMax = getDevice().lightnessDimmer.setMainLevel(getDevice().lightnessDimmer.getCurrentMainLevel());
    getDevice().lightnessDimmer.setLevel(0.0f);
    setupStrobe();
    getDevice().lightnessDimmer.setState(OnOffState::ON);
    return true;
}

inline bool StrobeMode::onExiting(ButtonEvent *event) {
    signalGenerator->stop();
    return true;
}

inline bool StrobeMode::onEventHandling(ButtonEvent *event) {
    switch (event->getClicksCount()) {
        case 0:
            // long press
            levelMax = getDevice().lightnessDimmer.setNextMainLevel();
            break;
        case 1:
            getDevice().enterState(getDevice().offMode, event);
            return true;
        case 2:
            strobeIndex = (strobeIndex + 1) % SIGNAL_TYPES_COUNT;
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
    logger.trace("mode %d", strobeIndex);

    signalGenerator->start(signalTypes[strobeIndex], LEVEL_LOW_1, _max(LEVEL_LOW_2, levelMax), THE_PERIOD);
}

#undef THE_PERIOD
