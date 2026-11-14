#include <Arduino.h>

/* -------------------------------------------------------------------
 * F1. LED par MMIO — tout éteindre
 * Responsable : ...
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_eteindre(void) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
