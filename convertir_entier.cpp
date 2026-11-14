#include <Arduino.h>

/* -------------------------------------------------------------------
 * A2. Conversion entier vers ASCII
 * Responsable : ...
 * R0 (entrée) : valeur entière signée
 * R1 (entrée) : adresse du texte de sortie (texte_resultat)
 * Écrit le texte terminé par 0, par exemple "-84".
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void convertir_entier(int valeur, volatile char *sortie) {
  asm volatile(
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
