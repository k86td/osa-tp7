#include <Arduino.h>

/* -------------------------------------------------------------------
 * A1. Conversion ASCII vers entier
 * Responsable : Adriana Paternina
 * R0 (entrée) : adresse d'un texte terminé par 0, par exemple "-45"
 * R0 (sortie) : valeur entière signée
 * Si le texte est vide ou contient un caractère autre qu'un chiffre
 * (après un « - » facultatif), écrire 1 dans saisie_invalide.
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int convertir_ascii(volatile char *texte) {
  asm volatile(

    // 1. Initialisation
    "PUSH  {R4, LR}             \n"
    "MOVS  R1, #0              \n"
    "MOVS  R3, #0              \n"
    "MOVS  R4, #0              \n"

    // 2. Lecture du premier caractère
    "LDRB  R2, [R0], #1         \n"

    // 3. Vérification du signe négatif
    "CMP   R2, #0x2D           \n"
    "BNE   1f                  \n"
    "MOVS  R3, #1              \n"
    "B     2f                  \n"

    // 4. Vérification du caractère
    "1:                         \n"
    "CMP   R2, #0              \n"
    "BEQ   4f                  \n"
    "CMP   R2, #0x30           \n"
    "BLT   5f                  \n"
    "CMP   R2, #0x39           \n"
    "BGT   5f                  \n"

    // 5. Conversion ASCII vers chiffre
    "SUBS  R2, R2, #0x30       \n"

    // 6. Multiplication par 10 avec LSL
    "ADD   R12, R2, R1, LSL #3 \n"
    "ADD   R1, R12, R1, LSL #1 \n"

    // 7. Compter les chiffres
    "ADDS  R4, R4, #1          \n"

    // 8. Lire le caractère suivant
    "2:                         \n"
    "LDRB  R2, [R0], #1         \n"
    "B     1b                  \n"

    // 9. Vérification de la fin du texte
    "4:                         \n"
    "CMP   R4, #0              \n"
    "BEQ   5f                  \n"
    "CMP   R3, #0              \n"
    "BEQ   6f                  \n"

    // 10. Appliquer le signe négatif
    "RSBS  R1, R1, #0          \n"

    // 11. Retourner le résultat
    "6:                         \n"
    "MOV   R0, R1              \n"
    "POP   {R4, LR}            \n"
    "BX    LR                  \n"

    // 12. Gestion des erreurs
    "5:                         \n"
    "LDR   R2, =saisie_invalide \n"
    "MOVS  R3, #1              \n"
    "STR   R3, [R2]            \n"
    "MOVS  R0, #0              \n"
    "POP   {R4, LR}            \n"
    "BX    LR                  \n"

    ".ltorg                    \n"
  );
}
