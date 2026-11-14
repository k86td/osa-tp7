#include <Arduino.h>

/* -------------------------------------------------------------------
 * F1. LED par MMIO — initialisation
 * Responsable : ...
 * Configure en sortie les trois broches de la LED RGB (registre DIRSET)
 * et éteint la LED.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_init(void) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
