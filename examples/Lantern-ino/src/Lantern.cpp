#include "../include/Lantern.h"
#include <LowPower.h>

float readTemperature();

Lantern::Lantern() :
		Gnulight(ledCurrentDriver, "Lantern") {
}

void Lantern::onSetup() {
	ledCurrentDriver.setup();
	pBatteryMonitor = new BatteryMonitor(*this, battery);
	pTempMonitor = new TempMonitor(*this, readTemperature);
	Gnulight::onSetup();
}

void Lantern::onSwitchOn() {
	digitalWrite(DEVICES_VCC_PIN, HIGH);
}

void Lantern::onSwitchOff() {
	digitalWrite(DEVICES_VCC_PIN, LOW);
	onIdle();
}

void Lantern::onIdle() {
	// disable watchdog
	wdt_reset();
	wdt_disable();

	if (getState() == OnOffState::OFF) {
		LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
	} else {

#ifdef LOG_ENABLED
		LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_ON,
				SPI_OFF, USART0_ON, TWI_OFF);
#else
		LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_ON,
				SPI_OFF, USART0_OFF, TWI_OFF);
#endif

	}

	// enable watch dog
	wdt_reset();
	wdt_enable(WDTO_X);
}

float readBatteryVoltage() {
	analogRead(BATTERY_SENSING_PIN);
	return 5.0f * analogRead(BATTERY_SENSING_PIN) / 1023;
}

#define V_OUT (analogRead(TEMPERATURE_SENSING_PIN) * 5.0f / 1023.0f)
#define V_0 0.5
#define T_C 0.01

/*
 * MCP9700A-E/TO thermometer
 */
float readTemperature() {
    analogRead(TEMPERATURE_SENSING_PIN);
    return (V_OUT - V_0) / T_C;
}
