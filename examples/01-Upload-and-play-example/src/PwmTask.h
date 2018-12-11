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
	PwmTask(uint8_t pin, TaskManager &taskManager);
	void analogWrite(uint8_t value);
protected:
	void OnUpdate(uint32_t taskTime) override;
private:
	uint8_t pin;
	uint8_t pinLevel;
	uint32_t highTime= -1;
};

#define PWM_PERIOD MsToTaskTime(25)

PwmTask::PwmTask(uint8_t pin, TaskManager &taskManager) :
		Task(MsToTaskTime(-1)), pin(pin) {
	taskManager.SuspendTask(this);
}

inline void PwmTask::analogWrite(uint8_t value) {
	highTime = (PWM_PERIOD * value) / 255;

	digitalWrite(pin, pinLevel = (highTime == 0 ? LOW : HIGH));

	if (highTime == 0 || highTime == 255) {
		Suspend();
	} else {
		setTimeInterval(highTime);
		Resume();
	}
}

inline void PwmTask::OnUpdate(uint32_t taskTime) {
	if (pinLevel == HIGH) {
		digitalWrite(pin, pinLevel = LOW);
		setTimeInterval(PWM_PERIOD - highTime);
	} else {
		digitalWrite(pin, pinLevel = HIGH);
		setTimeInterval(highTime);
	}
}

#endif

