#include <Arduino.h>

/* -------------------------------------------------------------------
 * B3. Multiplication (MUL et MLA interdites)
 * Responsable : ...
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 × R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int multiplication(int a, int b) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
