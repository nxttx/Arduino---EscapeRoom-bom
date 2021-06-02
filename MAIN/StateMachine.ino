////////////////////////
// Basic state machine//
// By: R. Boudewijn   //
// Date: 10/03/2020   //
// #MN# = Machine name//
////////////////////////

// ----Alle states gedefineerd-------
const int STATEMACHINE_STATE_STARTUP = 0;
const int STATEMACHINE_STATE_COUNTDOWN = 1;
const int STATEMACHINE_STATE_CABLECUT = 2;
const int STATEMACHINE_STATE_EXPLODE = 3;
const int STATEMACHINE_STATE_DISMANTLED = 4;

// ----Houdt bij welke state je zit--
int stateMachineCurrentState;

void stateMachineSetup() {  // statemachinestart (Runt 1 keer)
  stateMachineCurrentState = STATEMACHINE_STATE_STARTUP; // Zet de eerste state aan.
  stateMachineStartUpEntry(); // Start de entry van de eerste state.

}

// ----LOOP--------------------------
unsigned long clockCheckInputPreviousMillis = 0;
int clockCheckInputInterval = 1000; //1sec

void stateMachineLoop() {
  switch (stateMachineCurrentState) {
    case STATEMACHINE_STATE_STARTUP: {
        // --- Do ---------------------
        stateMachineStartUpDo();

        // --- Exit Statement ---------
        if (millis() >= 1000) {
          stateMachineStartUpExit();
          stateMachineCurrentState = STATEMACHINE_STATE_COUNTDOWN;
          stateMachineCountDownEntry();
        }
        break;
      }

    case STATEMACHINE_STATE_COUNTDOWN: {
        // --- Do ---------------------
        stateMachineCountDownDo();

        // --- events -----------------
        if (countTime <= millis()) {
          stateMachineCountDownExit();
          stateMachineCurrentState = STATEMACHINE_STATE_EXPLODE;
          stateMachineExplodeEntry();
        } else if (checkCode() == true) {
          stateMachineCountDownExit();
          stateMachineCurrentState = STATEMACHINE_STATE_DISMANTLED;
          stateMachineDismantledEntry();
        } else if (millis() - clockCheckInputPreviousMillis >= clockCheckInputInterval) {
          if (checkCableCut() == true) {
            stateMachineCountDownExit();
            stateMachineCurrentState = STATEMACHINE_STATE_CABLECUT;
            stateMachineCableCutEntry();
            clockCheckInputPreviousMillis = millis();
          }
        }

        break;
      }

    case STATEMACHINE_STATE_CABLECUT: {
        // --- Do ---------------------
        stateMachineCableCutDo();

        // --- events -----------------
        stateMachineCableCutExit();
        stateMachineCurrentState = STATEMACHINE_STATE_COUNTDOWN;
        stateMachineCountDownEntry();
        break;
      }

    case STATEMACHINE_STATE_EXPLODE: {
        // --- Do ---------------------
        stateMachineExplodeDo();

        // --- events -----------------
        //program is done
        break;
      }

    case STATEMACHINE_STATE_DISMANTLED: {
        // --- Do ---------------------
        stateMachineDismantledDo();

        // --- events -----------------
        //program is done
        break;
      }
  }
}


// --- STATEMACHINE_STATE_STARTUP -----------
void stateMachineStartUpEntry() {
  Serial.println("------Booting up.------");
  shiftRegisterSetup();
  bombSetup();
  Serial.println("------Boot up complete.------");
}

void stateMachineStartUpDo() {
  // <nothing>
}

void stateMachineStartUpExit() {
  countTime += millis();
}


// --- STATEMACHINE_STATE_COUNTDOWN -----------
void stateMachineCountDownEntry() {
  // <nothing>
}
unsigned long clockCountDownPreviousMillis = 0;
int clockCountDownInterval = 60000; //minute

void stateMachineCountDownDo() {
  int remainingMinutes = (countTime - millis()) / 1000 / 60;
  int remainingSeconds = (countTime - millis()) / 1000;
  if (remainingSeconds > 60) {
    displayBinair(number(remainingMinutes / 10), DS1, SH_CP1, ST_CP1);
    displayBinair(number(remainingMinutes % 10), DS2, SH_CP2, ST_CP2);
  } else {
    displayBinair(number(remainingSeconds / 10), DS1, SH_CP1, ST_CP1);
    displayBinair(number(remainingSeconds % 10), DS2, SH_CP2, ST_CP2);
    clockCountDownInterval = 1000; // sec
  }
  noTone(buzzer());

  if (millis() - clockCountDownPreviousMillis >= clockCountDownInterval) {
    clockCountDownPreviousMillis = millis();
    tone(buzzer(), 250);

  }
}

void stateMachineCountDownExit() {
  noTone(buzzer());
}


// --- STATEMACHINE_STATE_CABLECUT -----------
void stateMachineCableCutEntry() {
  countTime = countTime - PANALTY_TIME;
  tone(buzzer(), 250);
}

void stateMachineCableCutDo() {
  tone(buzzer(), 250);
}

void stateMachineCableCutExit() {
  // <nothing>
}


// --- STATEMACHINE_STATE_EXPLODE -----------
void stateMachineExplodeEntry() {
  displayUitroepteken();
  tone(buzzer(), 250);
  //Buzzer
}

void stateMachineExplodeDo() {
  //Buzzer
}

void stateMachineExplodeExit() {
  // <nothing>
}


// --- STATEMACHINE_STATE_DISMANTLED -----------
void stateMachineDismantledEntry() {
  dismanteldCountTime = countTime - millis();
}

unsigned long clockDismantledPreviousMillis = 0;
int clockDismantledInterval = 1000; //minute

void stateMachineDismantledDo() {
  int remainingMinutes = dismanteldCountTime / 1000 / 60;
  int remainingSeconds = dismanteldCountTime / 1000;
  if (millis() - clockDismantledPreviousMillis >= clockDismantledInterval) {
    if (remainingSeconds > 60) {
      displayBinair(number(remainingMinutes / 10), DS1, SH_CP1, ST_CP1);
      displayBinair(number(remainingMinutes % 10), DS2, SH_CP2, ST_CP2);
    } else {
      displayBinair(number(remainingSeconds / 10), DS1, SH_CP1, ST_CP1);
      displayBinair(number(remainingSeconds % 10), DS2, SH_CP2, ST_CP2);
    }
    if (millis() - clockDismantledPreviousMillis >= clockDismantledInterval + clockDismantledInterval) {
      shiftRegisterSetup();
      clockDismantledPreviousMillis = millis();
    }
  }
}

void stateMachineDismantledExit() {
  // <nothing>
}
