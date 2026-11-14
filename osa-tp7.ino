/*
 * GIF-1001 — TP7 : Calculatrice en assembleur sur l'Arduino Nano 33 BLE
 *
 * Fonctionnement
 *   1. Le programme lit une ligne au moniteur série (115 200 bauds),
 *      par exemple « 25 + 17 » ou « -12 * 7 ». Faites attention à l'espace entre l'opérateur et les opérandes. Si vous saisissez 25+17 il doit vous afficher une erreur et la led doit s'allumer en rouge
 *   2. Il découpe la ligne en trois éléments : opérande 1, opérateur, opérande 2.
 *   3. Il appelle vos fonctions en assembleur pour convertir, valider et calculer.
 *   4. La LED clignote en bleu pendant 15 s (période de 1 s), puis reste
 *      verte si le calcul a réussi, ou rouge en cas d'erreur.
 *
* Vous devez :
 *   Compléter chaque fonction 
 *   Ne pas modifier la section « PROGRAMME PRINCIPAL ».
 *
 * Règles
 *   - Chaque fonction est écrite entièrement en assembleur dans le bloc asm,
 *     dans son propre fichier <fonction>.cpp à côté de ce croquis.
 *   - Paramètres dans R0 à R3, valeur de retour dans R0, retour par BX LR.
 *   - Instructions et fonctions interdites dans vos fonctions :
 *     MUL, MLA, SDIV, UDIV, digitalWrite, pinMode, delay, millis.
 *   - Ne pas retirer la ligne « .ltorg » à la fin de chaque bloc asm :
 *     elle place les adresses chargées par LDR Rd, =variable près du code.
 *   - Compléter l'en-tête de chaque fonction : membre responsable,
 *     paramètres et valeur de retour.
 */

#include <Arduino.h>

/* ===================================================================
 * VARIABLES EN MÉMOIRE
 * Accessibles en assembleur par :  LDR Rx, =nom_de_la_variable
 * =================================================================== */

volatile char tampon[32];            // ligne saisie au moniteur série
volatile char texte_operande1[12];   // premier opérande, en texte
volatile char texte_operande2[12];   // second opérande, en texte
volatile char texte_resultat[12];    // résultat converti en texte (A2)
volatile int  saisie_invalide;       // 1 si un opérande est mal formé (A1)

/* Codes d'erreur retournés par valider() (critère C1) */
#define OK                   0
#define ERR_DIVISION_ZERO    1
#define ERR_HORS_BORNES      2
#define ERR_OPERATEUR        3
#define ERR_SAISIE           4

/* Couleurs passées à led_allumer() (critère F1) */
#define ROUGE  0
#define VERT   1
#define BLEU   2

/* ===================================================================
 * FONCTIONS EN ASSEMBLEUR — À COMPLÉTER
 * Chaque fonction est écrite dans son propre fichier <fonction>.cpp,
 * placé dans le même dossier que ce croquis. L'IDE Arduino les compile
 * automatiquement et les affiche dans des onglets séparés.
 * On ne garde ici que les déclarations extern "C".
 * =================================================================== */

/* A1. Conversion ASCII vers entier           -> convertir_ascii.cpp  */
extern "C" int  convertir_ascii(volatile char *texte);

/* A2. Conversion entier vers ASCII           -> convertir_entier.cpp */
extern "C" void convertir_entier(int valeur, volatile char *sortie);

/* B1. Addition                               -> addition.cpp         */
extern "C" int  addition(int a, int b);

/* B2. Soustraction                           -> soustraction.cpp     */
extern "C" int  soustraction(int a, int b);

/* B3. Multiplication (MUL et MLA interdites) -> multiplication.cpp   */
extern "C" int  multiplication(int a, int b);

/* B4. Division (SDIV et UDIV interdites)     -> division.cpp         */
extern "C" int  division(int a, int b);

/* C1. Validation et exceptions               -> valider.cpp          */
extern "C" int  valider(int a, int operateur, int b);

/* F1. LED par MMIO                           -> led_init.cpp,
 *                                               led_allumer.cpp,
 *                                               led_eteindre.cpp     */
extern "C" void led_init(void);
extern "C" void led_allumer(int couleur);
extern "C" void led_eteindre(void);

/* -------------------------------------------------------------------
 * H. Fonctions originales de l'équipe
 * Ajouter vos propres fonctions dans leur propre fichier .cpp, les
 * déclarer en extern "C" ci-dessus, puis les appeler depuis
 * executer_fonction_originale(), plus bas.
 * ------------------------------------------------------------------- */


/* ===================================================================
 * PROGRAMME PRINCIPAL — NE PAS MODIFIER
 * (sauf executer_fonction_originale pour le critère H)
 * =================================================================== */

static void lire_ligne(void) {
  int n = 0;
  while (true) {
    while (!Serial.available()) { }
    char c = Serial.read();
    if (c == '\r') continue;
    if (c == '\n') break;
    if (n < (int)sizeof(tampon) - 1) tampon[n++] = c;
  }
  tampon[n] = 0;
}

/* Copie le prochain mot de tampon (à partir de *pos) dans dest. */
static void extraire_mot(int *pos, volatile char *dest, int taille) {
  int n = 0;
  while (tampon[*pos] == ' ') (*pos)++;
  while (tampon[*pos] != 0 && tampon[*pos] != ' ') {
    if (n < taille - 1) dest[n++] = tampon[*pos];
    (*pos)++;
  }
  dest[n] = 0;
}

static void phase_bleue(void) {
  for (int i = 0; i < 15; i++) {     // 15 clignotements de période 1 s
    led_allumer(BLEU);
    delay(500);
    led_eteindre();
    delay(500);
  }
}

/* Critère H : appeler ici vos fonctions originales, au besoin. */
static void executer_fonction_originale(void) {
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { }
  led_init();
  Serial.println("Calculatrice GIF-1001 : entrer par exemple  25 + 17");
}

void loop() {
  volatile char texte_operateur[4];
  int pos = 0;

  lire_ligne();
  Serial.print("> ");
  Serial.println((const char *)tampon);

  extraire_mot(&pos, texte_operande1, sizeof(texte_operande1));
  extraire_mot(&pos, texte_operateur, sizeof(texte_operateur));
  extraire_mot(&pos, texte_operande2, sizeof(texte_operande2));

  saisie_invalide = 0;
  int a = convertir_ascii(texte_operande1);
  int b = convertir_ascii(texte_operande2);
  int op = (texte_operateur[1] == 0) ? texte_operateur[0] : 0;

  int code = valider(a, op, b);
  int r = 0;
  if (code == OK) {
    switch (op) {
      case '+': r = addition(a, b);       break;
      case '-': r = soustraction(a, b);   break;
      case '*': r = multiplication(a, b); break;
      case '/': r = division(a, b);       break;
    }
  }

  phase_bleue();

  if (code == OK) {
    convertir_entier(r, texte_resultat);
    Serial.print("= ");
    Serial.println((const char *)texte_resultat);
    led_allumer(VERT);
  } else {
    Serial.print("Erreur ");
    Serial.println(code);
    led_allumer(ROUGE);
  }

  executer_fonction_originale();
}
