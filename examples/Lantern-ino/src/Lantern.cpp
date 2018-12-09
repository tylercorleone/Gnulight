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

	// disable watchdog so it doesn't wake us up
	wdt_reset();
	wdt_disable();

	LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

	// enable watch dog after wake up
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
