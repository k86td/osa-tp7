#include <Arduino.h>

/* -------------------------------------------------------------------
 * F1. LED par MMIO — initialisation
 * Responsable : ...
 * Configure en sortie les trois broches de la LED RGB (registre DIRSET)
 * et éteint la LED.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_init(void) {
  asm volatile(
    "LDR   R0, =0x50000518  \n"
    "LDR   R1, =0x01010040  \n"
    "STR   R1, [R0]         \n"

    "LDR   R0, =0x50000508  \n"
    "STR   R1, [R0]         \n"

    "BX    LR               \n"
    ".ltorg                 \n"
  );
}

