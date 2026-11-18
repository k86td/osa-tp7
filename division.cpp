#include <Arduino.h>

/* -------------------------------------------------------------------
 * B4. Division (SDIV et UDIV interdites)
 * Responsable : ...
 * R0, R1 (entrée) : dividende, diviseur (non nul)
 * R0 (sortie) : quotient tronqué vers zéro (-7 / 2 = -3)
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int division(int a, int b) {
  asm volatile(
    "push {r1, r2, r3, r4} \n"
    "mov r2, #0 \n"

    "mov r3, r0 \n"
    "mov r4, r1 \n"

    "cmp r0, #0 \n"
    "it mi \n"
    "rsbmi r0, r0, #0 \n"

    "cmp r1, #0 \n"
    "it mi \n"
    "rsbmi r1, r1, #0 \n"

    "diviseur_boucle: \n"
    "cmp r0, r1 \n"
    "blt fin_diviseur_boucle \n"
    "sub r0, r0, r1 \n"
    "add r2, r2, #1 \n"
    "b diviseur_boucle \n"
    "fin_diviseur_boucle: \n"

    "eors r3, r4 \n"
    "it mi \n"
    "rsbmi r2, r2, #0 \n"

    "mov r0, r2 \n"
    "pop {r1, r2, r3, r4} \n"

    "bx lr \n"
    ".ltorg \n"
  );
}
