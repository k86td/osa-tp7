#include <Arduino.h>

/* -------------------------------------------------------------------
 * A1. Conversion ASCII vers entier
 * Responsable : ...
 * R0 (entrée) : adresse d'un texte terminé par 0, par exemple "-45"
 * R0 (sortie) : valeur entière signée
 * Si le texte est vide ou contient un caractère autre qu'un chiffre
 * (après un « - » facultatif), écrire 1 dans saisie_invalide.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int convertir_ascii(volatile char *texte) {
  asm volatile(
    "MOV   R0, #0          \n"   // à remplacer
    "BX    LR              \n"
    ".ltorg                \n"
  );
}