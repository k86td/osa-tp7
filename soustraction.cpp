#include <Arduino.h>

/* -------------------------------------------------------------------
 * B2. Soustraction
 * Responsable : Fatoumata Diaraye Bah
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 − R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int soustraction(int a, int b) {
  asm volatile(
    "SUB R0, RO, R1        \n"
    "BX    LR              \n"  
    ".ltorg                \n"
  );
}
