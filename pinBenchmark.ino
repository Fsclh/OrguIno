//Paramètres :
const int digitalCount = 63; //Nombre de digitalPins. Les analogiques y sont inclus.
static const uint8_t analog_pins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15}; //Liste des analogPins
const byte offset = 34; //Note la plus basse
//Numéro de canal à configurer dans les fonctions NoteStart et NoteStop en fin. 0x{fonction}{canal}

//Début du programme :
int previous[digitalCount];
void setup() {
  //Vitesse de la liaison série
  Serial.begin(256000);
  //Configuration des touches
  for (int i = 2; i < digitalCount; i++) {
    pinMode(i, INPUT);//Règle en mode entrée
    digitalWrite(i, HIGH); //Active la résistance interne (sinon trop sensible)
    previous[i] = LOW;
  }

}
unsigned long avg = 0;
unsigned long cur = 0;
void loop() {
  unsigned long end = 0;
  unsigned long start = micros();

  //Vérification de l'état des pins digitaux
  scanDigital();

  // Compute the time it took
  end = micros();
  cur++;
  avg = avg + (end - start);
  if (cur == 10000) {
    Serial.println(avg / cur);
    avg = 0;
    cur = 0;
  }
}

void scanDigital() {
  //Vérification de l'état des pins digitaux
  for (byte pin = 2; pin < digitalCount; pin++) {
    if (digitalRead(pin) == LOW && previous[pin] == HIGH) { //Vérifie l'état activé en fonction du précédent état
      NoteStart(pin);//Envoie le signal d'activation de la note
      previous[pin] = LOW;//Enregistre le nouvel état dans le tableau d'états
    }
    if (digitalRead(pin) == HIGH && previous[pin] == LOW) { //Vérifie l'état désactivé en fonction du précédent état
      NoteStop(pin);//Envoie du signal de désactivation de la note
      previous[pin] = HIGH;//Enregistre le nouvel état dans le tableau d'états
    }
  }
}

//Trame = type de message & numéro de canal, numéro de note, force de frappe
void NoteStart(byte pin) {
  byte message[] = {0x90, pin + offset, 0x40};
  Serial.write(message, sizeof(message));
}
void NoteStop(byte pin) {
  byte message[] = {0x80, pin + offset, 0x40};
  Serial.write(message, sizeof(message));
}
