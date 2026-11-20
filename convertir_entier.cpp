#include <Arduino.h>

/* -------------------------------------------------------------------
 * A2. Conversion entier vers ASCII
 * Responsable : Adriana Paternina
 * R0 (entrée) : valeur entière signée
 * R1 (entrée) : adresse du texte de sortie (texte_resultat)
 * Écrit le texte terminé par 0, par exemple "-84".
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) void convertir_entier(int valeur, volatile char *sortie) {
  asm volatile(

    // 1. Sauvegarder les registres utilisés
    "PUSH  {R4-R7, LR}          \n"

    // 2. Initialiser les registres
    "MOV   R4, R1              \n"  // Adresse du tampon de sortie
    "MOVS  R5, #0              \n"  // Nombre de chiffres
    "MOVS  R6, #0              \n"  // Indicateur de signe

    // 3. Vérifier si le nombre est négatif
    "CMP   R0, #0              \n"
    "BGE   1f                  \n"
    "MOVS  R6, #1              \n"
    "RSBS  R0, R0, #0          \n"

    // 4. Écrire le signe négatif
    "1:                         \n"
    "CMP   R6, #0              \n"
    "BEQ   2f                  \n"
    "MOVS  R2, #0x2D           \n"
    "STRB  R2, [R4], #1         \n"

    // 5. Préparer l'extraction des chiffres
    "2:                         \n"
    "MOV   R7, R4              \n"  // Début des chiffres

    // 6. Extraire les chiffres par divisions successives
    "3:                         \n"
    "MOVS  R2, #0              \n"  // Quotient
    "MOV   R3, R0              \n"  // Reste provisoire

    // 7. Division par 10 avec soustractions
    "4:                         \n"
    "CMP   R3, #10             \n"
    "BLT   5f                  \n"
    "SUBS  R3, R3, #10         \n"
    "ADDS  R2, R2, #1          \n"
    "B     4b                  \n"

    // 8. Convertir le reste en caractère ASCII
    "5:                         \n"
    "ADDS  R3, R3, #0x30       \n"
    "STRB  R3, [R4], #1         \n"
    "ADDS  R5, R5, #1          \n"

    // 9. Continuer avec le quotient
    "MOV   R0, R2              \n"
    "CMP   R0, #0              \n"
    "BNE   3b                  \n"

    // 10. Terminer le texte par 0x00
    "MOVS  R2, #0              \n"
    "STRB  R2, [R4]            \n"

    // 11. Inverser l'ordre des chiffres
    "SUBS  R4, R4, #1          \n"

    "6:                         \n"
    "CMP   R7, R4              \n"
    "BHS   7f                  \n"
    "LDRB  R2, [R7]            \n"
    "LDRB  R3, [R4]            \n"
    "STRB  R3, [R7]            \n"
    "STRB  R2, [R4]            \n"
    "ADDS  R7, R7, #1          \n"
    "SUBS  R4, R4, #1          \n"
    "B     6b                  \n"

    // 12. Retourner au programme principal
    "7:                         \n"
    "POP   {R4-R7, LR}          \n"
    "BX    LR                  \n"

    ".ltorg                    \n"
  );
}
