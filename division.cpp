#include <Arduino.h>

/* -------------------------------------------------------------------
 * B4. Division (SDIV et UDIV interdites)
 * Responsable : ...
 * R0, R1 (entrée) : dividende, diviseur (non nul)
 * R0 (sortie) : quotient tronqué vers zéro (-7 / 2 = -3)
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int division(int a, int b) {
  asm volatile(
    "PUSH {r1, r2, r3, r4} \n"
    "MOV r2, #0 \n"

    "MOV r3, r0 \n"
    "MOV r4, r1 \n"

    "CMP r0, #0 \n"
    "IT MI \n"
    "RSBMI r0, r0, #0 \n"

    "CMP r1, #0 \n"
    "IT mi \n"
    "RSBMI r1, r1, #0 \n"

    "diviseur_boucle: \n"
    "CMP r0, r1 \n"
    "BLT fin_diviseur_boucle \n"
    "SUB r0, r0, r1 \n"
    "ADD r2, r2, #1 \n"
    "B diviseur_boucle \n"
    "fin_diviseur_boucle: \n"

    "EORS r3, r4 \n"
    "IT MI \n"
    "RSBMI r2, r2, #0 \n"

    "MOV r0, r2 \n"
    "POP {r1, r2, r3, r4} \n"

    "bx lr \n"
    ".ltorg \n"
  );
}
