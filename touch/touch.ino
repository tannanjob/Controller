#include "Sensor.h"


const int InitDelay = 5000;
const int frameTime = 30;
int start = 0;
int frame = 0;

const int SENSOR_1_IN = 13;
const int SENSOR_2_IN = 12;
const int SENSOR_3_IN = 11;
const int SENSOR_4_IN = 10;
const int SENSOR_5_IN = 9;
const int SENSOR_6_IN = 8;
const int SENSOR_7_IN = 7;
const int SENSOR_8_IN = 6;
const int SENSOR_9_IN = 5;
const int SENSOR_10_IN = 4;
const int SENSOR_11_IN = 3;
const int SENSOR_12_IN = 2;
const int SENSOR_13_IN = A5;
const int SENSOR_14_IN = A4;
const int SENSOR_15_IN = A3;
const int SENSOR_16_IN = A2;

Sensor S1;
Sensor S2;
Sensor S3;
Sensor S4;
Sensor S5;
Sensor S6;
Sensor S7;
Sensor S8;
Sensor S9;
Sensor S10;
Sensor S11;
Sensor S12;
Sensor S13;
Sensor S14;
Sensor S15;
Sensor S16;

Sensor Ss[16];

const int Stop = A0;
bool isStop = false;
bool change = false;

void send()
{
  for (int i = 0; i < 16; i++) {
    if (Ss[i].change) {
      Ss[i].change = false;
      change = true;
      break;
    }
  }
  if (change) {
    NKROKeyboard.send();
  }
  change = false;
}

void setup() {
  // put your setup code here, to run once:
  NKROKeyboard.begin();

  Serial.begin(115200);
  delay(InitDelay);  // wait for initialization
  NKROKeyboard.releaseAll();

  S1 = Sensor(SENSOR_1_IN, 'a');
  S2 = Sensor(SENSOR_2_IN, 'z');
  S3 = Sensor(SENSOR_3_IN, 's');
  S4 = Sensor(SENSOR_4_IN, 'x');
  S5 = Sensor(SENSOR_5_IN, 'd');
  S6 = Sensor(SENSOR_6_IN, 'c');
  S7 = Sensor(SENSOR_7_IN, 'f');
  S8 = Sensor(SENSOR_8_IN, 'v');
  S9 = Sensor(SENSOR_9_IN, 'g');
  S10 = Sensor(SENSOR_10_IN, 'b');
  S11 = Sensor(SENSOR_11_IN, 'h');
  S12 = Sensor(SENSOR_12_IN, 'n');
  S13 = Sensor(SENSOR_13_IN, 'j');
  S14 = Sensor(SENSOR_14_IN, 'm');
  S15 = Sensor(SENSOR_15_IN, 'k');
  S16 = Sensor(SENSOR_16_IN, ',');

  Ss[0] = S1;
  Ss[1] = S2;
  Ss[2] = S3;
  Ss[3] = S4;
  Ss[4] = S5;
  Ss[5] = S6;
  Ss[6] = S7;
  Ss[7] = S8;
  Ss[8] = S9;
  Ss[9] = S10;
  Ss[10] = S11;
  Ss[11] = S12;
  Ss[12] = S13;
  Ss[13] = S14;
  Ss[14] = S15;
  Ss[15] = S16;

  pinMode(Stop, INPUT_PULLUP);
}

void loop() {
  start = millis();

  if (digitalRead(Stop) == LOW) {
    isStop = true;
    NKROKeyboard.releaseAll();
  } else {
    isStop = false;
  }
  if (!isStop) {
    for (int i = 0; i < 16; i++) {
      Ss[i].CheckKey();
    }
    for (int i = 0; i < 16; i++) {
      Ss[i].Write();
    }

    send();

    frame = millis() - start;
    if (frame < frameTime) {
      delay(frameTime - frame);
      Serial.println("~~~~~~~~~~~~~~~~");
    }
  }
}
