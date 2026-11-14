#include <Arduino.h>

/* -------------------------------------------------------------------
 * B4. Division (SDIV et UDIV interdites)
 * Responsable : ...
 * R0, R1 (entrée) : dividende, diviseur (non nul)
 * R0 (sortie) : quotient tronqué vers zéro (-7 / 2 = -3)
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int division(int a, int b) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
