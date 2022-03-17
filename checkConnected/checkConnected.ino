const int inCnt = NUM_DIGITAL_PINS;
int previous[inCnt]; // Tableau contenant les états enregistrés des touches

void setup() {
  for (int i = 0; i < 12; i++) {
    pinMode(i, INPUT);// Active le mode entrée
    //digitalWrite(i, HIGH); // Active la résistance interne (évite l'activation aléatoire de la touche)
    previous[i] = LOW;// Initialise le tableau de référence d'états
  }
  for (int i = 14; i < inCnt; i++) {
    pinMode(i, INPUT);// Active le mode entrée
    //digitalWrite(i, HIGH); // Active la résistance interne (évite l'activation aléatoire de la touche)
    previous[i] = LOW;// Initialise le tableau de référence d'états
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int pin = 0; pin < inCnt; pin++) { // Boucle de vérification de chaque touche
    if (digitalRead(pin) == LOW && previous[pin] == HIGH) { // Vérifie l'état touche appuyée
      digitalWrite(LED_BUILTIN, LOW);
      previous[pin] = LOW; // Enegistre l'état
    }
    if (digitalRead(pin) == HIGH && previous[pin] == LOW) { // Vérifie l'état touche appuyée
      digitalWrite(LED_BUILTIN, HIGH);
      previous[pin] = HIGH; // Enegistre l'état
    }
  }
}
