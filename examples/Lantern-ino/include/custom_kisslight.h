#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SIMPLE_LOGGER_APPENDER_LEVEL APPENDER_LEVEL_OFF
#define LEVEL_LOW_1 0.001
/* I want to be alerted when entering idle state
 * (no tasks running) to debug the onIdle method
 */
#define DEBUG_ENTERING_IDLE_STATE
#include <KissLight.h>

#define BUTTON_PIN 2
#define DEVICES_VCC_PIN 5
#define LED_PIN 9
#define BATTERY_SENSING_PIN A2
#define TEMPERATURE_SENSING_PIN A1

#ifdef SIMPLE_LOGGER_APPENDER_ENABLED
#define WDTO_X WDTO_2S
#else
#define WDTO_X WDTO_500MS
#endif

#endif
