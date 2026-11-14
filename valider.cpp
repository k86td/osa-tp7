#include <Arduino.h>

/* Variable globale définie dans osa-tp7.ino, lue ici par
 * LDR Rx, =saisie_invalide */
extern volatile int saisie_invalide;

/* Codes d'erreur retournés par valider() (critère C1) */
#define OK                   0
#define ERR_DIVISION_ZERO    1
#define ERR_HORS_BORNES      2
#define ERR_OPERATEUR        3
#define ERR_SAISIE           4

/* -------------------------------------------------------------------
 * C1. Validation et exceptions
 * Responsable : ...
 * R0 (entrée) : opérande 1
 * R1 (entrée) : code ASCII de l'opérateur ('+', '-', '*', '/'),
 *               ou 0 si l'opérateur n'a pas exactement un caractère
 * R2 (entrée) : opérande 2
 * R0 (sortie) : OK (0) ou un code d'erreur, dans cet ordre de priorité :
 *               ERR_SAISIE (4)        si saisie_invalide vaut 1
 *               ERR_OPERATEUR (3)     si l'opérateur est inconnu
 *               ERR_HORS_BORNES (2)   si un opérande est hors de [-100, 100]
 *               ERR_DIVISION_ZERO (1) si l'opérateur est '/' et R2 = 0
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int valider(int a, int operateur, int b) {
  asm volatile(
    "MOV   R0, #0          \n"   // à remplacer
    "BX    LR              \n"
    ".ltorg                \n"
  );
}
