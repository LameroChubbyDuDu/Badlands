#include <EEPROM.h>

//Only need to modify the slave_num//
//Whenever the slave is called, it'll flash//
#define in_built_led 13
#define ENABLE 2
// #define slave_num 97
#define touch_pin 5
#define FAN_CONTROL_PIN 6

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(60, 9);

int brightness = 255;
int fan_stat = 0;
int b_r = 255;
int mul = -10;
int rever = 1;

int val_1 = 0, val_2 = 0;
// int led_case = 0;
char led_case = 'l';

int r_stat = 1;
int g_stat = 1;
int b_stat = 1;
int color_stat = 1;

char slave_num = 'b';

///
char isActivated = 'n';
unsigned long touch_start_time;
bool startTouching = false;
const long activation_time = 600;
const long lighting_time = 10000;

bool isTesting = false; ////

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(250);

  pinMode(in_built_led, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(FAN_CONTROL_PIN, OUTPUT);

  pinMode(touch_pin, INPUT);

  slave_num = EEPROM.read(0);

  digitalWrite(in_built_led, LOW);
  digitalWrite(ENABLE, LOW);

  pixels.begin();
  pixels.setBrightness(255);
}

void loop() {
  //check touch
  if (digitalRead(touch_pin) && startTouching == false) {
    startTouching = true;
    touch_start_time = millis();
  } else if (digitalRead(touch_pin) && startTouching == true) {
    if (millis() - touch_start_time > activation_time) isActivated = 'y';
  } else if (!digitalRead(touch_pin) && millis() - touch_start_time > lighting_time) {
    isActivated = 'n';
  } else {
    startTouching = false;
  }

  //testing
  if (isTesting){
    isActivated = 'y';
  }

  //send message
  if (Serial.available() >= 2) {
    if (Serial.read() == slave_num) {
      // flash();
      led_case = Serial.read();

      digitalWrite(ENABLE, HIGH);
      Serial.write(isActivated);
      delay(1);  //?
      Serial.flush();
      digitalWrite(ENABLE, LOW);
    }
  }

  //led effect
  if (isActivated == 'y' && led_case == 'i') {
    //full power
    light_up();
    fan_on();
  } else if (isActivated == 'y') {
    //local poewr on
    led_single();
    fan_on();
  } else {
    led_off();
    fan_off();
    //off
  }
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

void light_up() {
  for (int i = 0; i < 60; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  pixels.show();
}

// void led_diagonal(){
//   if(b_r == 5) mul = 5;
//   else if(b_r == 255) mul = -5;
//   b_r = b_r + mul;
//   for(int i = 0; i < 60; i++){
//         pixels.setPixelColor(i, pixels.Color(r_stat, g_stat, b_stat));
//   }
//   pixels.setBrightness(b_r);
//   pixels.show();
// }

void led_single() {
  switch (color_stat) {
    case 1:
      rever = 1;
      r_stat = 198;
      g_stat = 44;
      b_stat = 44;
      break;
    case 2:
      r_stat = 198;
      g_stat = 100;
      b_stat = 44;
      break;
    case 3:
      r_stat = 198;
      g_stat = 175;
      b_stat = 44;
      break;
    case 4:
      r_stat = 175;
      g_stat = 198;
      b_stat = 44;
      break;
    case 5:
      r_stat = 44;
      g_stat = 154;
      b_stat = 198;
      break;
    case 6:
      r_stat = 44;
      g_stat = 93;
      b_stat = 198;
      break;
    case 7:
      rever = -1;
      r_stat = 154;
      g_stat = 44;
      b_stat = 198;
      break;
    default:
      break;
  }
  delay(100);
  color_stat = color_stat + rever;
  for (int i = 0; i < 60; i++) {
    pixels.setPixelColor(i, pixels.Color(r_stat, g_stat, b_stat));
  }
  pixels.show();
}

void led_off() {
  for (int i = 0; i < 60; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void flash() {
  digitalWrite(in_built_led, HIGH);
  delay(100);
  digitalWrite(in_built_led, LOW);
  delay(100);
};