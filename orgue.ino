// Notes :
// Numéro de canal à configurer dans les fonctions NoteStart et NoteStop en fin. 0x{fonction}{canal}
// Note On canal 5 => 0x95; Note Off canal 5 => 0x85

// v0.3
// Paramètres et variables globales :
const int inCnt = NUM_DIGITAL_PINS; // Nombre de pins input-conpatibles, analog inclus. L'utilisation de NUM_DIGITAL_PINS baisse les performances
const byte offset = 34; // Numéro de la note la plus basse
int previous[inCnt]; // Tableau contenant les états enregistrés des touches

void setup() {
  // Vitesse de la liaison série :
  Serial.begin(31250);
  // Configuration des touches, sans les pins 0 et 1, qui lieront les cartes
  for (int i = 2; i < inCnt; i++) {
    pinMode(i, INPUT);// Active le mode entrée
    digitalWrite(i, HIGH); // Active la résistance interne (évite l'activation aléatoire de la touche)
    previous[i] = LOW;// Initialise le tableau de référence d'états
  }
}

void loop() {
  scan(); // Vérification de l'état des pins digitaux
}

void scan() {
  for (byte pin = 2; pin < inCnt; pin++) { // Boucle de vérification de chaque touche
    if (digitalRead(pin) == LOW && previous[pin] == HIGH) { // Vérifie l'état touche appuyée
      NoteStart(pin); // Reçoit l'état touche appuyée
      previous[pin] = LOW; // Enregistre l'état
    }
    if (digitalRead(pin) == HIGH && previous[pin] == LOW) { // Vérifie l'état touche lâchée
      NoteStop(pin); // Reçoit l'état touche lâchée
      previous[pin] = HIGH;// Enregistre l'état
    }
  }
}

void NoteStart(byte pin) { // Trame = type de message & numéro de canal, numéro de note, force de frappe
  byte message[] = {0x91, pin + offset, 0x40};
  Serial.write(message, sizeof(message));
}
void NoteStop(byte pin) {
  byte message[] = {0x81, pin + offset, 0x40};
  Serial.write(message, sizeof(message));
}
