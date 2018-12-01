#ifndef LEDCURRENTDRIVER_H
#define LEDCURRENTDRIVER_H

#include "crnl_tpca_lantern_config.h"

#include <Gnulight.h>

class LedCurrentDriver: public BrightnessDriver {
public:
	LedCurrentDriver(TaskManager &taskManager);
	void onSetLevel(float level) override;
private:
	void digPotWrite(uint16_t value);
};

#endif
