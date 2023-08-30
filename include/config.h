#ifndef KISS_LIGHT_CONFIG_H
#define KISS_LIGHT_CONFIG_H

/*
 ************************************************************
 * Default KissLight's configuration values.                *
 * You can override one or more of them simply redefining   *
 * the value before including <KissLight.h> in your project *
 ************************************************************
 */

/* KissLightLightnessDimmer configuration - some consideration about lightness and light intensity */
#ifndef LEVEL_LOW_1
#define LEVEL_LOW_1 0.01f // moonlight mode. Some configurations could have some issues with such a small values. In these cases use a higher value.
#endif
#ifndef LEVEL_LOW_2
#define LEVEL_LOW_2 0.05f
#endif
#ifndef LEVEL_MED_1
#define LEVEL_MED_1 0.2f
#endif
#ifndef LEVEL_MED_2
#define LEVEL_MED_2 0.5f // 50% lightness -> 18% light intensity
#endif
#ifndef LEVEL_HIGH_1
#define LEVEL_HIGH_1 0.75f // 75% lightness -> 48% light intensity, that is, almost full lightness at the half power consumption
#endif
#ifndef LEVEL_HIGH_2
#define LEVEL_HIGH_2 1.0f
#endif

#ifndef MAIN_LEVEL_TRANSITION_DURATION
#define MAIN_LEVEL_TRANSITION_DURATION MsToTaskTime(300)
#endif

#ifndef LIGHTNESS_TO_BRIGHTNESS_CONVERSION
#define LIGHTNESS_TO_BRIGHTNESS_CONVERSION(lightness) cieLabConversion(lightness)
#endif

/* StrobeMode configuration */
#ifndef STROBE_ON_OFF_INIT_PERIOD_MS
#define STROBE_ON_OFF_INIT_PERIOD_MS 500
#endif
#ifndef STROBE_BEACON_PERIOD_MS
#define STROBE_BEACON_PERIOD_MS 4000
#endif
#ifndef STROBE_BEACON_DUTY_CYCLE
#define STROBE_BEACON_DUTY_CYCLE 0.01f
#endif
#ifndef STROBE_DISCO_PERIOD_MS
#define STROBE_DISCO_PERIOD_MS 80
#endif
#ifndef STROBE_DISCO_DUTY_CYCLE
#define STROBE_DISCO_DUTY_CYCLE 0.2f
#endif
#ifndef STROBE_LEVEL_REFRESH_INTERVAL_MS
#define STROBE_LEVEL_REFRESH_INTERVAL_MS 30
#endif
#ifndef STROBE_PERIODICAL_SEQUENCE_PERIOD_MS
#define STROBE_PERIODICAL_SEQUENCE_PERIOD_MS 2000
#endif

/* BatteryMonitor configuration */
#ifndef BATTERY_MONITOR_INTERVAL_MS
#define BATTERY_MONITOR_INTERVAL_MS 15000
#endif
#ifndef BATTERY_MONITOR_FILTERED_RECHARGE_AMOUNT
#define BATTERY_MONITOR_FILTERED_RECHARGE_AMOUNT 0.15f
#endif

// Function that maps power-source's charge level to light level
// Used to step down the light driver (e.g. led current driver)
// When returns 0.0 the "onEmptyBattery" callback gets called
#ifndef BATTERY_CHARGE_TO_LIGHT_LIMIT
#define BATTERY_CHARGE_TO_LIGHT_LIMIT(charge) batteryChargeToLightLimit(charge)
inline float batteryChargeToLightLimit(float charge) {
	if (charge <= 0.0f) {
		return 0.0;
	} else if (charge < 0.05f) {
		return 0.05f;
	} else if (charge < 0.15f) {
		return 0.1f;
	} else if (charge < 0.25f) {
		return 0.25f;
	} else if (charge < 0.35f) {
		return 0.5f;
	}

	return 1.0f;
}
#endif

#ifndef BATTERY_MONITOR_ON_EMPTY_BATTERY
#define BATTERY_MONITOR_ON_EMPTY_BATTERY this->onEmptyBattery
#endif

/* TemperatureMonitor configuration */
#ifndef TEMP_MONITOR_INTERVAL_MS
#define TEMP_MONITOR_INTERVAL_MS 10000
#endif

#ifndef TEMP_MONITOR_EMITTER_TARGET_TEMPERATURE
#define TEMP_MONITOR_EMITTER_TARGET_TEMPERATURE 50.0f
#endif

#ifndef TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD
#define TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD 0.1f
#endif

// Function that maps the emitter's temperature to light level
// Used to step down the light driver (e.g. led current driver)
#ifndef TEMP_TO_LIGHT_LIMIT
#define TEMP_TO_LIGHT_LIMIT(temperature) TempMonitor::temperatureToLightLimit(temperature)
#endif

/* ParameterCheckMode configuration */
#ifndef PAR_CHECK_STROBE_PERIOD_MS
#define PAR_CHECK_STROBE_PERIOD_MS 800UL
#endif

#ifndef PAR_CHECK_DIGIT_DUTY_CYCLE
#define PAR_CHECK_DIGIT_DUTY_CYCLE 0.15f
#endif

#ifndef PAR_CHECK_COMMA_DUTY_CYCLE
#define PAR_CHECK_COMMA_DUTY_CYCLE 1.0f
#endif

/*
 * Total step-up/step-down duration
 * e.g. caused by battery/temperature imposed limit
 */
#ifndef STEP_UP_DOWN_DURATION
#define STEP_UP_DOWN_DURATION MsToTaskTime(2000)
#endif

/*
 * Delay between level's increment/decrement steps
 * e.g. main level change, battery or temperature step-up/step-down etc.
 */
#ifndef DELAY_BETWEEN_LEVEL_CHANGE
#define DELAY_BETWEEN_LEVEL_CHANGE MsToTaskTime(30)
#endif

/* Logging configuration */
#ifndef LOG_LEVEL
#define LOG_LEVEL DEBUG_LEVEL
#endif

#ifndef LOG_SUBSTRING_BUFFER_SIZE
#define LOG_SUBSTRING_BUFFER_SIZE 20
#endif

#endif
