#include <Arduino.h>

/* Couleurs passées à led_allumer() (critère F1) */
#define ROUGE  0
#define VERT   1
#define BLEU   2

/* -------------------------------------------------------------------
 * F1. LED par MMIO — allumer une couleur
 * Responsable : ...
 * R0 (entrée) : couleur (ROUGE = 0, VERT = 1, BLEU = 2)
 * Éteint les deux autres couleurs et allume celle qui est demandée.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void led_allumer(int couleur) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
