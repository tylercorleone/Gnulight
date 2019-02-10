#include "custom_gnulight.h"
#include "PwmTask.h"

extern PwmTask pwmTask;

class BuiltinLedDriver: public GnulightLightDriver {
private:
	void onSetLevel(float level) override {
		pwmTask.analogWrite(level * 255);
	}
};
