/*This is the code for the slave rods*/
#include "Wire.h"
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(60, 5);

#define SLAVE_ADDRESS 1 // need to modify the address for each slave rods here
#define CURRENT_ROD 1

#define ROD_1_ADDRESS 1
#define ROD_2_ADDRESS 2
#define ROD_3_ADDRESS 3
#define ROD_4_ADDRESS 4

#define CASE_0 0 
#define CASE_1 1 // 1
#define CASE_2 2 // 2
#define CASE_3 3 // 1, 2
#define CASE_4 4 // 3
#define CASE_5 5 // 1, 3
#define CASE_6 6 // 2, 3
#define CASE_7 7 // 1, 2, 3
#define CASE_8 8 // 4
#define CASE_9 9 // 1, 4
#define CASE_10 10 // 2, 4
#define CASE_11 11 // 1, 2, 4
#define CASE_12 12 // 3, 4
#define CASE_13 13 // 1, 3, 4
#define CASE_14 14 // 2, 3, 4
#define CASE_15 15 // 1, 2, 3, 4

#define red 1
#define orange 2
#define yellow 3
#define light_green 4
#define dark_green 5
#define light_blue 6
#define dark_blue 7
#define purple 8

#define TOUCH_PIN 8

int signal = 0;
int color_state = 1;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(15);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  Wire.onRequest(Sending_touch_signal_request);
  delay(500);
  Getting_rod_5_message();
}

void ReceiveEvent(){
  if(Wire.available()){
    while(Wire.available()) signal = Wire.read();
  }
}

void Sending_touch_signal_request(){
  int touch = digitalRead(TOUCH_PIN);
  Wire.write(touch);
}

void Getting_rod_5_message(){
  Wire.onReceive(ReceiveEvent);
    Serial.print("The attreive signal is: ");
    Serial.println(signal);
    switch(CURRENT_ROD){
      case ROD_1_ADDRESS:
        Serial.println("In rod 1.");
        read_signal_1();
      break;
      case ROD_2_ADDRESS:
        Serial.println("In rod 2.");
        read_signal_2();
      break;
      case ROD_3_ADDRESS:
        Serial.println("In rod 3.");
        read_signal_3();
      break;
      case ROD_4_ADDRESS:
        Serial.println("In rod 4.");
        read_signal_4();
      break;
      default:
        Serial.println("In rod default.");
        read_signal_1();
      break;
    }
}

void read_signal_1(){
  Serial.println("In read signal 1.");
  if((signal == CASE_1) 
      || (signal == CASE_3)
      || (signal == CASE_5)
      || (signal == CASE_7)
      || (signal == CASE_9)
      || (signal == CASE_11)
      || (signal == CASE_13)
      || (signal == CASE_15)
      ) neon_on();
  else{
    Serial.println("Here");
    neon_off();
  }
}

void read_signal_2(){
  if((signal == CASE_2) 
      || (signal == CASE_3)
      || (signal == CASE_6)
      || (signal == CASE_7)
      || (signal == CASE_10)
      || (signal == CASE_11)
      || (signal == CASE_14)
      || (signal == CASE_15)
      ) neon_on();
  else neon_off();
}

void read_signal_3(){
  if((signal == CASE_4) 
      || (signal == CASE_5)
      || (signal == CASE_6)
      || (signal == CASE_7)
      || (signal == CASE_12)
      || (signal == CASE_13)
      || (signal == CASE_14)
      || (signal == CASE_15)
      ) neon_on();
  else neon_off();
}

void read_signal_4(){
  if((signal == CASE_8) 
      || (signal == CASE_9)
      || (signal == CASE_10)
      || (signal == CASE_11)
      || (signal == CASE_12)
      || (signal == CASE_13)
      || (signal == CASE_14)
      || (signal == CASE_15)
      ) neon_on();
  else neon_off();
}

void neon_on(){
  Serial.println("Neon on!!!");
  // circular(color_state);
  // if(color_state == 8)color_state = 1;
  // else color_state++;
  neon_try();
}

void neon_off(){
  for(int i = 1; i < 60; i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void circular(int color_state){
    switch(color_state){
      case red:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case orange:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(255, 96, 0));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case yellow:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(255, 207, 0));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case light_green:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(138, 207, 0));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case dark_green:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(16, 83, 0));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case light_blue:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(16, 181, 205));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case dark_blue:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(3, 55, 182));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      case purple:
      for(int i = 0; i < 60; i ++){
        pixels.setPixelColor(i, pixels.Color(157, 74, 230));
        pixels.show();
        delay(100);
      }
      for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      default:{
        for(int i = 1; i < 60; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(100);
      }
      break;
      }
    }  
}

void neon_try(){
  for(int i = 0; i < 15; i++){
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }
  for(int i = 15; i < 30; i++){
    pixels.setPixelColor(i, pixels.Color(255, 96, 0));
  }
  for(int i = 30; i < 45; i++){
    pixels.setPixelColor(i, pixels.Color(16, 83, 0));
  }
  for(int i = 45; i < 60; i++){
    pixels.setPixelColor(i, pixels.Color(3, 55, 182));
  }

  pixels.show();
}