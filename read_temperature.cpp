#include <Arduino.h>

/* -------------------------------------------------------------------
* H. Read Temperature (fonction originale)
* Responsable : Tristan Lépine
* Paramètres : aucun
* R0 (sortie) : température du die en °C (entier signé)
* ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int read_temperature() {
  asm volatile(
    "MOV R0, #0 \n"

    "LDR R1, =0x4000C000 \n"
    "STR R0, [R1, #0x100] \n"
    "MOV R0, #1 \n"
    "STR R0, [R1, 0x000] \n"

    "read_temp_boucle: \n"
    "LDR R0, [R1, 0x100] \n"
    "CMP R0, #1 \n"
    
    "BNE read_temp_boucle \n"
    "LDR R0, [R1, #0x508] \n"

    "ASR R0, R0, #2 \n"

    "BX LR \n"
    ".ltorg \n"
  );
}
