#include "custom_gnulight.h"
#include "PwmTask.h"

class BuiltinLedDriver: public GnulightLightDriver {
private:
	void onSetLevel(float level) override;
};

extern PwmTask pwmTask;

void BuiltinLedDriver::onSetLevel(float level) {
	pwmTask.analogWrite(level * 255);
}
