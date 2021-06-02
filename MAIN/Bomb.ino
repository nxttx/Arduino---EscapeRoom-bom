int bombPin [5] = {3, 4, 5, 6, 7};

void bombSetup() {
  pinMode(2, INPUT);
  for (int i = 0; i < 5; i++ ) {
    pinMode(bombPin[i], INPUT);
  }


}

boolean checkCableCut() {
  for (int i = 0; i < 5; i++ ) {
    if (digitalRead(bombPin[i]) == 0) {
      if (bombPin[i] == 4) {
        Serial.println("-----Kabel doorgeknipt.------ ");
        Serial.println("-----Bonustijd: 10 minuten.-------");
        countTime = countTime + PANALTY_TIME;
        bombPin[i] = 2;
        return false;
      } else {
        Serial.println("-----Kabel doorgeknipt.------ ");
        Serial.println("-----Straftijd: 10 minuten.-------");
        bombPin[i] = 2;
        return true;
      }
    }
  }
  return false;
}


boolean checkCode() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    String code = Serial.readString();
    Serial.print("ingevulde code: ");
    Serial.println(code);
    if (code == "527698") {
      Serial.println("------Code correct.------");
      return true;
    } else {
      Serial.println("------Code incorrect.------");
      countTime = countTime - 180000;
      Serial.println("3 Minuten straftijd.");
    }
  }
  return false;
}
