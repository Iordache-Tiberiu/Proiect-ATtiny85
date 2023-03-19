const int latchPin = 0;  // ST_CP
const int clockPin = 1;  // SH_CP
const int dataPin = 4;   // DS

volatile int contor_buton;
int potentiometru;

byte etaj;
byte coloane_1;
byte coloane_2;

void setup() {
  // put your setup code here, to run once:

  contor_buton = 0;

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), increment_contor_buton, RISING);

  pinMode(A3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  potentiometru = analogRead(A3);
  potentiometru = map(potentiometru, 0, 1023, 50, 1000);

  // MODELUL 0
  if (contor_buton == 0) {
    etaj = 0b00000000;
    coloane_1 = 0b11111111;
    coloane_2 = 0b11111111;
    aprinde(etaj, coloane_1, coloane_2);
  }


  // MODELUL 1
  if (contor_buton == 1) {
    etaj = 0b00000001;
    coloane_1 = 0b00000000;
    coloane_2 = 0b00000000;

    aprinde(etaj, coloane_1, coloane_2);
    delay(potentiometru);

    for (int i = 1; i < 4; i ++) {
      etaj = etaj << 1;
      etaj = etaj + 1;
      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
    for (int i = 1; i <= 4; i ++) {
      etaj = etaj << 1;
      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
  }


  // MODELUL 2
  if (contor_buton == 2) {
    etaj = 0b00001111;
    coloane_1 = 0b11110000;
    coloane_2 = 0b11110000;

    aprinde(etaj, coloane_1, 255);
    delay(potentiometru);
    aprinde(etaj, 0, 255);
    delay(potentiometru);
    aprinde(etaj, 0, coloane_2);
    delay(potentiometru);
    aprinde(etaj, 0, 0);
    delay(potentiometru);

    aprinde(etaj, ~coloane_1, 0);
    delay(potentiometru);
    aprinde(etaj, 255, 0);
    delay(potentiometru);
    aprinde(etaj, 255, ~coloane_2);
    delay(potentiometru);
    aprinde(etaj, 255, 255);
    delay(potentiometru);
  }


  // MODELUL 3
  if (contor_buton == 3) {
    etaj = 0b00001111;
    coloane_1 = 0b11101110;
    coloane_2 = 0b11101110;

    aprinde(etaj, coloane_1, coloane_2);
    delay(potentiometru);

    for (int i = 1; i < 4; i ++) {
      coloane_1 = coloane_1 << 1;
      coloane_1 = coloane_1 - 16;
      coloane_2 = coloane_2 << 1;
      coloane_2 = coloane_2 - 16;

      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
    coloane_1 = 0b00010001;
    coloane_2 = 0b00010001;
    aprinde(etaj, coloane_1, coloane_2);
    delay(potentiometru);

    for (int i = 1; i < 4; i ++) {
      coloane_1 = coloane_1 << 1;
      coloane_1 = coloane_1 + 17;
      coloane_2 = coloane_2 << 1;
      coloane_2 = coloane_2 + 17;
      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
  }


  // MODELUL 2'
  if (contor_buton == 4) {
    etaj = 0b00001111;
    coloane_1 = 0b00001111;
    coloane_2 = 0b00001111;

    aprinde(etaj, 255, coloane_2);
    delay(potentiometru);
    aprinde(etaj, 255, 0);
    delay(potentiometru);
    aprinde(etaj, coloane_1, 0);
    delay(potentiometru);
    aprinde(etaj, 0, 0);
    delay(potentiometru);

    aprinde(etaj, 0, ~coloane_2);
    delay(potentiometru);
    aprinde(etaj, 0, 255);
    delay(potentiometru);
    aprinde(etaj, ~coloane_1, 255);
    delay(potentiometru);
    aprinde(etaj, 255, 255);
    delay(potentiometru);
  }


  // MODELUL 3'
  if (contor_buton == 5) {
    etaj = 0b00001111;
    coloane_1 = 0b01110111;
    coloane_2 = 0b01110111;

    aprinde(etaj, coloane_1, coloane_2);
    delay(potentiometru);

    for (int i = 1; i < 4; i ++) {
      coloane_1 = coloane_1 >> 1;
      coloane_1 = coloane_1 - 8;
      coloane_2 = coloane_2 >> 1;
      coloane_2 = coloane_2 - 8;

      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
    coloane_1 = 0b10001000;
    coloane_2 = 0b10001000;
    aprinde(etaj, coloane_1, coloane_2);
    delay(potentiometru);

    for (int i = 1; i < 4; i ++) {
      coloane_1 = coloane_1 >> 1;
      coloane_1 = coloane_1 + 136;
      coloane_2 = coloane_2 >> 1;
      coloane_2 = coloane_2 + 136;

      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
  }


  // MODELUL FINAL
  if (contor_buton == 6) {
    etaj = 0b00000000;
    coloane_1 = 0b00000000;
    coloane_2 = 0b00000000;

    for (int i = 0; i < 10; i ++) {
      etaj = ~etaj;
      aprinde(etaj, coloane_1, coloane_2);
      delay(potentiometru);
    }
  }
}

void aprinde(byte et, byte col_1, byte col_2) {

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, col_2);
  shiftOut(dataPin, clockPin, MSBFIRST, col_1);
  shiftOut(dataPin, clockPin, MSBFIRST, et);
  digitalWrite(latchPin, HIGH);
}

void increment_contor_buton() {

  contor_buton ++;
  if (contor_buton == 7)
    contor_buton = 0;
}
