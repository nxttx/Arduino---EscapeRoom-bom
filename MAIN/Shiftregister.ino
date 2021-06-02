const int DS1 = 11;     // Hiermee geef je door hoeveel ledjes aan moeten staan
const int SH_CP1 = 13; // clock
const int ST_CP1 = 12;  // latch pin/ einde van send.
const int DS2 = 8;     // Hiermee geef je door hoeveel ledjes aan moeten staan
const int SH_CP2 = 10; // clock
const int ST_CP2 = 9;  // latch pin/ einde van send.


void shiftRegisterSetup(){
  startShiftRegsister(DS1, SH_CP1, ST_CP1);
  startShiftRegsister(DS2, SH_CP2, ST_CP2);
}

void startShiftRegsister(int DS, int SH_CP, int ST_CP){
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);

  digitalWrite(DS, LOW);
  digitalWrite(SH_CP, LOW);
  digitalWrite(ST_CP, LOW);

  // alles uit
  digitalWrite(DS, LOW); 
  for ( int i = 0; i < 8; i++) {
    digitalWrite(SH_CP, HIGH);
    digitalWrite(SH_CP, LOW);
  }
  digitalWrite(ST_CP, HIGH);
  digitalWrite(ST_CP, LOW);

}

byte number(int i) {
  const byte NUMBERS [] = {
    B11111100, //0
    B01100000, //1
    B11011010, //2
    B11110010, //3
    B01100110, //4
    B10110110, //5
    B10111110, //6
    B11100100, //7
    B11111110, //8
    B11110110, //9
    B11101111, //A
    B00111111, //B
    B10011101, //C
    B01111011, //D
    B10011111, //E
    B10001111  //F
  };
  return NUMBERS[i];
}

boolean isBitSet(byte pattern, int index) {
  byte check = B00000001 << index;
  return  ((pattern & check)  == check);
}

void displayBinair(byte patroon, int DS, int SH_CP, int ST_CP) {
  for ( int i = 0; i < 8; i++) {
    if ( isBitSet(patroon, i) == true) {
      digitalWrite(DS, HIGH);
    }
    else {
      digitalWrite(DS, LOW);
    }
    digitalWrite(SH_CP, HIGH);
    digitalWrite(SH_CP, LOW);
  }
  digitalWrite(ST_CP, HIGH);
  digitalWrite(ST_CP, LOW);
}

void displayUitroepteken(){
  displayBinair(B01000001, DS1, SH_CP1, ST_CP1);
  displayBinair(B01000001, DS2, SH_CP2, ST_CP2);
}
