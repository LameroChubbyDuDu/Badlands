/*This is the code for rod 5*/
#include "Wire.h"
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(60, 5);

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

int touched_1 = 0;
int touched_2 = 0;
int touched_3 = 0;
int touched_4 = 0;

int signal = 0;
int color_state = 0;

void setup() {
  Wire.begin(); // Since we only got 1 master, there's no need for registering an address for the master device
  Serial.begin(9600);
}

void loop() {
  Getting_rod_message();
  delay(500);
  Rod_operation();
}

// Sending the operating command to each slave rod
void Rod_operation(){
  for(int i = 1; i <= 1; i++){
    Wire.beginTransmission(i);

    if(touched_1 && touched_2 && touched_3 && touched_4){
      neon_on();
      Wire.write(CASE_15);
    }else if(~touched_1 && touched_2 && touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_14);
    }else if(touched_1 && ~touched_2 && touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_13);
    }else if(~touched_1 && ~touched_2 && touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_12);
    }else if(touched_1 && touched_2 && ~touched_3 && touched_4){
      neon_off(); 
      Wire.write(CASE_11);
    }else if(~touched_1 && touched_2 && ~touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_10);
    }else if(touched_1 && ~touched_2 && ~touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_9);
    }else if(~touched_1 && ~touched_2 && ~touched_3 && touched_4){
      neon_off();
      Wire.write(CASE_8);
    }else if(touched_1 && touched_2 && touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_7);
    }else if(~touched_1 && touched_2 && touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_6);
    }else if(touched_1 && ~touched_2 && touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_5);
    }else if(~touched_1 && ~touched_2 && touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_4);
    }else if(touched_1 && touched_2 && ~touched_3 && ~touched_4){
      neon_off(); 
      Wire.write(CASE_3);
    }else if(~touched_1 && touched_2 && ~touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_2);
    }else if(touched_1 && ~touched_2 && ~touched_3 && ~touched_4){
      neon_off();
      Wire.write(CASE_1);
    }else{
      neon_off();
      Wire.write(CASE_0);
    }
    
    Serial.print("Transmission for rod ");
    Serial.print(i);
    Serial.print(" = ");
    int error = Wire.endTransmission();
    Serial.println(error);
  }
}

void Getting_rod_message(){
  for(int i = 1; i <= 1; i++){
    Wire.requestFrom(i, 1); // Touch signal is either 0 or 1
    Wire.beginTransmission(i);

    if(i == 1) touched_1 = Wire.read();
    else if(i == 2) touched_2 = Wire.read();
    else if(i == 3) touched_3 = Wire.read();
    else touched_4 = Wire.read();
    
    Serial.print("Requesting message from rod ");
    Serial.print(i);
    Serial.print(" = ");
    int error = Wire.endTransmission();
    Serial.println(error);

    // To check the signal that we got from the rod
    Serial.print("Neon signal[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(touched_1);
    delay(10);
  }
}


void neon_on(){
  circular(color_state);
  if(color_state == 8)color_state = 0;
  else color_state++;
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