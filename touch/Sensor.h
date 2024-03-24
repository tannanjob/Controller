#include "Arduino.h"
#include "HID-Project.h"

class Sensor {
public:
  int key = 0;
  char text = '\0';
  bool isPress = false;
  bool canPress = false;
  bool change = false;

  Sensor() {}
  Sensor(int keyNum, char c) {
    pinMode(keyNum, INPUT);
    key = keyNum;
    text = c;
  }
  void Write() {
    if (isPress && canPress) {
      NKROKeyboard.add(text);
      Serial.print(key);
      Serial.print("---");
      Serial.println(text);
      
      change = true;
      canPress = false;
    }
    if (!isPress && !canPress) {
      NKROKeyboard.release(text);
      Serial.print(key);
      Serial.print("---");
      Serial.println("^^^");
     
      change = true;
      canPress = true;
    }
  }

  void CheckKey() {
    if(digitalRead(key) == HIGH) {
      isPress = false;
    }else{
      isPress = true;
    }
    
    Serial.print(key);
    // Serial.print("###");
    // Serial.print(analogRead(key));
    Serial.print("###");
    Serial.println(digitalRead(key));
  }

private:
};
