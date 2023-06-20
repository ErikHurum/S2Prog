#include <inarm.h>
#include "reg.h"

extern "C"{
//
// IRQ interrupt handler.
//
__irq void irq_handler()
{
  int vec;

  vec = rIVEC_ADDR; // Get vector offset.
  vec >>= 2; // To get vecor number.

  // Check if timer 0 interrupt.
  if (vec == 2)
  {
    // Timer0 interrupt will be called 1000 Hz rate.
    // Stop at zero.
    if (tick)
      --tick;
    rTCON0 &= ~0x10; // Clear pending interrupt at timer 0.
  }

  // Clear interrupt controller service pending bit.
  rIRQISPC = 1 << vec;
}

//
// FIQ interrupt handler.
//
__fiq void fiq_handler()
{
  int vec = rFVEC_ADDR;
  vec >>= 2; // To get vecor number.

  // Clear interrupt controller service pending bit.
  rFIQISPC = 1 << vec;
}
