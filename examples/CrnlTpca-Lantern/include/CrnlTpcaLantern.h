#ifndef CRNL_TPCA_LANTERN_H
#define CRNL_TPCA_LANTERN_H

#include "LedCurrentDriver.h"

#include <Gnulight.h>
#include <LowPower.h>
#include <avr/power.h>

class CrnlTpcaLantern : public Gnulight {
public:
	CrnlTpcaLantern();
protected:
	void onSetup() override;
	void onPowerOn() override;
	void onPowerOff() override;
	LedCurrentDriver ledCurrentDriver { *this };
};

#endif
