/*******************************************************
Timers/Counters initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

#ifndef _TIMERS_INIT_INCLUDED_
#define _TIMERS_INIT_INCLUDED_

// Disable a Timer/Counter type A
void tca_disable(TCA_t *ptca);
// Timer/Counter TCA0 initialization
void tca0_init(void);
// Timer/Counter TCA1 initialization
void tca1_init(void);

#endif
