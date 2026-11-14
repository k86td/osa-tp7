#include <Arduino.h>

/* -------------------------------------------------------------------
 * B2. Soustraction
 * Responsable : ...
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 − R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int soustraction(int a, int b) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
