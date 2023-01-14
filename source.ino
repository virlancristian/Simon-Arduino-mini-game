#define BLUE_INPUT 2
#define BLUE_OUTPUT 13

#define GREEN_INPUT 3
#define GREEN_OUTPUT 12

#define RED_INPUT 4
#define RED_OUTPUT 11

#define YELLOW_INPUT 5
#define YELLOW_OUTPUT 10

#define START_BUTTON 6
#define GAME_STATE_OUTPUT 9

#define DIFFICULTY 4

int inputPins[] = {BLUE_INPUT, GREEN_INPUT, RED_INPUT, YELLOW_INPUT, START_BUTTON};
int outputPins[] = {BLUE_OUTPUT, GREEN_OUTPUT, RED_OUTPUT, YELLOW_OUTPUT, GAME_STATE_OUTPUT};
int maxSeqPerDiff[] = {4, 6, 8, 12};
int minSeqPerDiff[] = {2, 3, 4, 6};
int delayTimePerDiff[] = {1000, 750, 500, 300};

void setup() {
  for(int i = 0; i < 5; i++) {
    pinMode(inputPins[i], INPUT);
  }

  for(int i = 0; i < 5; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void playGame() {
  for(int i = 0; i < DIFFICULTY; i++) {
    for(int j = minSeqPerDiff[i]; j <= maxSeqPerDiff[i]; j++) {
      int* sequence = generateSequence(j);
      displaySequence(sequence, j, delayTimePerDiff[i]);
      verifySequence(sequence, j);

      for(int k = 0; k < 2; k++) {
        digitalWrite(GAME_STATE_OUTPUT, HIGH);
        delay(500);
        digitalWrite(GAME_STATE_OUTPUT, LOW);
        delay(500);
      }
      delay(1000);
      free(sequence);
    }
  }
}

void verifySequence(int* sequence, int length) {
  for(int i = 0; i < length; i++) {
    int userInput = getInputFromUser(); 
     
    if(userInput != sequence[i]) {
      digitalWrite(GAME_STATE_OUTPUT, HIGH);
      delay(10000);
      digitalWrite(GAME_STATE_OUTPUT, LOW);
      delay(1000);
      waitForStart();
    }   
    delay(500);
  }
}

int getInputFromUser() {
  while(1 == 1) {
    if(digitalRead(BLUE_INPUT) == HIGH) {
      return BLUE_OUTPUT;
    }    
    if(digitalRead(GREEN_INPUT) == HIGH) {
      return GREEN_OUTPUT;
    }
    if(digitalRead(RED_INPUT) == HIGH) {
      return RED_OUTPUT;
    }
    if(digitalRead(YELLOW_INPUT) == HIGH) {
      return YELLOW_OUTPUT;
    }
  }
}

void displaySequence(int* sequence, int length, int delayTime) {
    for(int i = 0; i < length; i++) {
      digitalWrite(sequence[i], HIGH);
      delay(delayTime);
      digitalWrite(sequence[i], LOW);
      delay(delayTime);
    }
}

int* generateSequence(int length) {
  int* sequence = (int*) calloc(length, sizeof(int));

  for(int i = 0; i < length; i++) {
    sequence[i] = random(10, 14);
  }

  return sequence;
}

void waitForStart() {
  while(1 == 1) {
    int startButtonInput = digitalRead(START_BUTTON);

    if(startButtonInput == HIGH) {
      for(int i = 0; i < 4; i++) {
        digitalWrite(outputPins[i], HIGH);
      }
      delay(1000);

      for(int i = 0; i < 4; i++) {
        digitalWrite(outputPins[i], LOW);
      }
      delay(1000);
      
      playGame();
    }
  }
}

void loop() {
  waitForStart();
}
