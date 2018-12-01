#ifndef GNULIGHT_CONFIG_H
#define GNULIGHT_CONFIG_H

/*
 ***********************************************************
 * Default Gnulight's configuration values.                *
 * You can override one or more of them simply redefining  *
 * the value before including <Gnulight.h> in your project *
 ***********************************************************
 */

/* Main light levels (lightness) */
#ifndef LEVEL_LOW_1
#define LEVEL_LOW_1 0.001
#endif
#ifndef LEVEL_LOW_2
#define LEVEL_LOW_2 0.02
#endif
#ifndef LEVEL_MED_1
#define LEVEL_MED_1 0.2f
#endif
#ifndef LEVEL_MED_2
#define LEVEL_MED_2 0.5f
#endif
#ifndef LEVEL_HIGH_1
#define LEVEL_HIGH_1 0.75f
#endif
#ifndef LEVEL_HIGH_2
#define LEVEL_HIGH_2 1.0f
#endif

/* Main level change duration (milliseconds) */
#ifndef MAIN_LEVEL_TRANSITION_DURATION_MS
#define MAIN_LEVEL_TRANSITION_DURATION_MS 300
#endif

/* Strobe mode */
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

/* Battery monitor */
#ifndef BATTERY_LEVEL_MONITOR_INTERVAL_MS
#define BATTERY_LEVEL_MONITOR_INTERVAL_MS 15000
#endif
#ifndef FILTERED_RECHARGE_AMOUNT
#define FILTERED_RECHARGE_AMOUNT 0.15f
#endif

/* Temperature monitor */
#ifndef TEMP_MONITOR_INTERVAL_MS
#define TEMP_MONITOR_INTERVAL_MS 10000
#endif
#ifndef TEMP_MONITOR_EMITTER_TARGET_TEMPERATURE
#define TEMP_MONITOR_EMITTER_TARGET_TEMPERATURE 50.0f
#endif
#ifndef TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD
#define TEMP_MONITOR_LEVEL_ACTIVATION_THRESHOLD 0.1f
#endif

/* Parameter check mode */
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
 * Step-up/step-down duration
 * (due to battery/temperature monitor)
 */
#ifndef STEP_UP_DOWN_DURATION_MS
#define STEP_UP_DOWN_DURATION_MS 2000
#endif

/* Milliseconds between each level increment/decrement step */
#ifndef DELAY_BETWEEN_LEVEL_CHANGE_MS
#define DELAY_BETWEEN_LEVEL_CHANGE_MS 30
#endif

#endif
