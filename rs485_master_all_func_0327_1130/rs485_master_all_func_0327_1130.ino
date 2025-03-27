#define in_built_led 13
#define ENABLE 2
#define FAN_CONTROL_PIN 6

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(60, 9);

int val_1 = 0, val_2 = 0;

int brightness = 255;
int b_r = 255;
int mul = -15;
int fan_stat = 0;

int stat = 0;  // 0-total ; message for asking response = 97+stat
char isTouched[4];
const int total_stat = 4;

const int receive_timeout = 1000;

int rod_num = 1;
char led_case = 'x';
// int led_case = 0;

int breath_bright = 255;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);

  pinMode(in_built_led, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(in_built_led, LOW);
  digitalWrite(ENABLE, HIGH);
  pinMode(FAN_CONTROL_PIN, OUTPUT);

  pixels.begin();
  // pixels.setBrightness(breath_bright);
}

void askValue(int index) {
  
  digitalWrite(ENABLE, HIGH);
  Serial.write(index+97);  // salve num indication
  Serial.write(led_case);
  Serial.flush();
  while (Serial.available() > 0) Serial.read();
  digitalWrite(ENABLE, LOW);  // start to receive message from
  unsigned long start_time = millis();

  while (Serial.available() == 0 && millis() - start_time < receive_timeout) {}
  if (Serial.available() > 0) {
    isTouched[index] = Serial.read();
  }
  while (Serial.available() > 0) Serial.read();
  stat = (stat+1)%total_stat;
  while (millis() < 500) {};
}

void loop() {

  askValue(stat);

  int count=0;
  led_case = 'j';
  for (int i=0; i<total_stat; i++){
    if (isTouched[i] =='y') count++;
  }
  if (count==total_stat){
    led_case = 'i';
  }
  // //-----------Message Analyze and Assign-----------//

  if (led_case == 'i') {
    allTouch();
    fan_on();
  } else {
    breath();
    fan_off();
  }
  while (Serial.available() > 0) Serial.read();
  delay(100);
  // digitalWrite(ENABLE, HIGH);
}

void fan_on() {
  if (fan_stat == 0) {
    analogWrite(FAN_CONTROL_PIN, 155);
    delay(100);
    fan_stat = 1;
  } else {
    analogWrite(FAN_CONTROL_PIN, 255);
  }
}

void fan_off() {
  fan_stat = 0;
  analogWrite(FAN_CONTROL_PIN, 0);
}

void allTouch() {
  for (int i = 0; i < 60; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  pixels.show();
}

void breath() {
  if (b_r <= 5) mul = 15;
  else if (b_r == 255) mul = -15;
  b_r = b_r + mul;
  for (int i = 0; i < 60; i++) {
    pixels.setPixelColor(i, pixels.Color(180, 105, 228));
  }
  pixels.setBrightness(b_r);
  pixels.show();
}

void flash() {
  digitalWrite(in_built_led, HIGH);
  delay(500);
  digitalWrite(in_built_led, LOW);
  delay(500);
};