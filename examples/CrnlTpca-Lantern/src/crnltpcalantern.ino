#include "crnl_tpca_lantern_config.h"

#include "CrnlTpcaLantern.h"

#include <Arduino.h>
#include <SPI.h>
#include <PWM.h>
#include <LowPower.h>
#include <avr/power.h>

void setupButton();
void setupLedCurrentDriver();
float readBatteryVoltage();
float readTemperature();

CrnlTpcaLantern *lantern;
LithiumBattery battery {2.8, 3.2, 4.17, 0.053, readBatteryVoltage};

void setup() {	
#ifdef INFO
	Serial.begin(9600);
#else
    power_usart0_disable(); // 0.1 mA (28.7 mA)
#endif

	lantern = new CrnlTpcaLantern();
    pinMode(BATTERY_SENSING_PIN, INPUT);
    pinMode(TEMPERATURE_SENSING_PIN, INPUT);
    setupLedCurrentDriver();
    
	GnulightCustomizer::customize(*lantern)
		.setBattery(battery)
		.setTemperatureReadFunction(readTemperature);

	setupButton();
	lantern->Setup();
}

void loop() {
	lantern->Loop(WDTO_X);
}

void setupButton() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonStateChangeISR, CHANGE);
}

void setupLedCurrentDriver() {
    Timer1_Initialize();
    SetPinFrequency(LED_PIN, 122);
    SPI.begin();
    digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void buttonStateChangeISR() {
	digitalRead(BUTTON_PIN) == LOW ?
			lantern->button.setState(ButtonState::PRESSED) : lantern->button.setState(ButtonState::RELEASED);
}

float readBatteryVoltage() {
	analogRead(BATTERY_SENSING_PIN);
	return 5.0f * analogRead(BATTERY_SENSING_PIN) / 1023;
}

#define V_OUT (analogRead(TEMPERATURE_SENSING_PIN) * 5.0f / 1023.0f)
#define V_0 0.5
#define T_C 0.01

float readTemperature() {
    analogRead(TEMPERATURE_SENSING_PIN);
    // it is a MCP9700A-E/TO
    return (V_OUT - V_0) / T_C;
}
