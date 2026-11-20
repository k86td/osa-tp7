#include <Arduino.h>

/* Couleurs passées à led_allumer() (critère F1) */
#define ROUGE  0
#define VERT   1
#define BLEU   2

/* -------------------------------------------------------------------
 * F1. LED par MMIO — allumer une couleur
 * Responsable : Jean Kersen Villefranche
 * R0 (entrée) : couleur (ROUGE = 0, VERT = 1, BLEU = 2)
 * Éteint les deux autres couleurs et allume celle qui est demandée.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_allumer(int couleur) {
  asm volatile(
    // Éteindre toutes les couleurs
    "LDR   R1, =0x50000508  \n"
    "LDR   R2, =0x01010040  \n"
    "STR   R2, [R1]         \n"

    //  couleur demandée
    "CMP   R0, #0           \n"
    "BEQ   led_rouge        \n"

    "CMP   R0, #1           \n"
    "BEQ   led_vert         \n"

    "CMP   R0, #2           \n"
    "BNE   led_fin          \n"

    // Bleu
    "MOV   R2, #64          \n"
    "B     led_activer      \n"

    // Rouge
    "led_rouge:             \n"
    "LDR   R2, =0x01000000  \n"
    "B     led_activer      \n"

    // Vert
    "led_vert:              \n"
    "LDR   R2, =0x00010000  \n"

    // Activer la couleur choisie
    "led_activer:           \n"
    "LDR   R1, =0x5000050C  \n"
    "STR   R2, [R1]         \n"

    // Retour
    "led_fin:               \n"
    "BX    LR               \n"
    ".ltorg                 \n"
  );
}
