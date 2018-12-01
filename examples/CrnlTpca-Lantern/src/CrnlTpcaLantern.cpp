#include "CrnlTpcaLantern.h"

CrnlTpcaLantern::CrnlTpcaLantern() :
		Gnulight(ledCurrentDriver) {
	setName("CrnlTpca");
}

void CrnlTpcaLantern::onSetup() {
	setName("CrnlTpca");
	Gnulight::onSetup();
}

void CrnlTpcaLantern::onPowerOn() {
	digitalWrite(DEVICES_VCC_PIN, HIGH);
}

void CrnlTpcaLantern::onPowerOff() {
	digitalWrite(DEVICES_VCC_PIN, LOW);
#if defined(USE_WDT)
	// disable watchdog so it doesn't wake us up
	wdt_reset();
	wdt_disable();
#endif

	LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

#if defined(USE_WDT)
	// enable watch dog after wake up
	wdt_reset();
	wdt_enable(WDTO_X);
#endif
}
