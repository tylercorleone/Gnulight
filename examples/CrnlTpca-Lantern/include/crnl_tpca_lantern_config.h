#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define INFO
#define DEBUG
#define TRACE

/**********   PIN MAPPING   **********/
#define BUTTON_PIN 2
#define DEVICES_VCC_PIN 5
#define LED_PIN 9

#define BATTERY_SENSING_PIN A2
#define TEMPERATURE_SENSING_PIN A1

#define USE_WDT

#ifdef INFO
#define WDTO_X WDTO_2S
#else
#define WDTO_X WDTO_500MS
#endif

#endif
