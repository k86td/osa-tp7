#include <Arduino.h>

/* -------------------------------------------------------------------
 * F1. LED par MMIO — tout éteindre
 * Responsable : ...
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_eteindre(void) {
  asm volatile(
    "LDR   R0, =0x50000508  \n"
    "LDR   R1, =0x01010040  \n"
    "STR   R1, [R0]         \n"

    "BX    LR               \n"
    ".ltorg                 \n"
  );
}
