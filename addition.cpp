#include <Arduino.h>

/* -------------------------------------------------------------------
 * B1. Addition
 * Responsable : Fatoumata Diaraye Bah
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 + R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int addition(int a, int b) {
  asm volatile(
    "ADD R0, R0, R1        \n" 
    "BX    LR              \n"   
    ".ltorg                \n"
  );
}
