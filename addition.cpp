#include <Arduino.h>

/* -------------------------------------------------------------------
 * B1. Addition
 * Responsable : ...
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 + R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int addition(int a, int b) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
