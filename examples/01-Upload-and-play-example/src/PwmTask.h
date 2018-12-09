#ifndef PWMTASK_H
#define PWMTASK_H

#include "custom_gnulight.h"
#include <Arduino.h>

/*
 * In most of Arduino boards the built-in led is attached
 * on PIN 13 and can't be driven in PWM mode (analogWrite)
 * We can use a Task to do accomplish this
 */
class PwmTask: public Task {
public:
	PwmTask(uint8_t pin, uint8_t initialPinLevel = LOW);
	void analogWrite(uint8_t value);
protected:
	void OnUpdate(uint32_t taskTime) override;
private:
	uint8_t pin;
	uint8_t pinLevel;
	uint32_t highTime= -1;
};

#define PWM_PERIOD MsToTaskTime(25)

PwmTask::PwmTask(uint8_t pin, uint8_t initialPinLevel) :
		Task(MsToTaskTime(-1)), pin(pin), pinLevel(initialPinLevel) {
	digitalWrite(pin, pinLevel);
}

inline void PwmTask::analogWrite(uint8_t value) {

	highTime = (PWM_PERIOD * value) / 255;

	uint32_t updateTime = -1;

	if (highTime == 0) {
		digitalWrite(pin, pinLevel = LOW);
	} else {
		digitalWrite(pin, pinLevel = HIGH);

		if (highTime < PWM_PERIOD) {
			updateTime = highTime;
		}
	}

	setTimeInterval(updateTime);
}

inline void PwmTask::OnUpdate(uint32_t taskTime) {

	if (highTime == 0 || highTime == PWM_PERIOD) {

		/*
		 * if value is 0 or 255 we have nothing to do
		 */
		return;
	}

	if (pinLevel == HIGH) {
		digitalWrite(pin, pinLevel = LOW);
		setTimeInterval(PWM_PERIOD - highTime);
	} else {
		digitalWrite(pin, pinLevel = HIGH);
		setTimeInterval(highTime);
	}
}

#endif

