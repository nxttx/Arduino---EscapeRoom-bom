////////////////////////
// Basic state machine//
// By: R. Boudewijn   //
// Date: 10/03/2020   //
// #MN# = Machine name//
////////////////////////


unsigned long countTime= 60000; // ms 1 hour
const unsigned long PANALTY_TIME= 600000;//ms 10min
unsigned long dismanteldCountTime;

void setup() {
  pinMode(buzzer(), OUTPUT);
  Serial.begin(9600);
  stateMachineSetup();

}

void loop() {
  stateMachineLoop();

}

int buzzer(){
  return A0;
}
