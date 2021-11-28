
const uint8_t  pinSensor   = A0;
const int analogin = 10;
const int analogin2 = 11;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int humidity;
int page;
//int mode [3] = {1, 2};
int minuters;
int hour;
int seconds;
int relay;
int relay2;
int set = 600;
int set2;
int light_mode = 0;
int r4 = 0;
int mater_mode = 0;
int anal;
int anal2;
unsigned long relay_timer;
unsigned long watr_timer;
// watering settings
int water_mode = 0;
int period = 30000;
int watering_time =  10000;
// analog sensor settings
int sensor_mode = 1;
int maximal = 1000;
// menu settings
int pages = 15 ;
LiquidCrystal_I2C LCD(0x27, 16, 2);
void setup() {
  dht.begin();
  Serial.begin(9600);
  pinMode(13, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(analogin, OUTPUT);
  pinMode(analogin2, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}
void loop() {
  float h = dht.readHumidity();
    float t = dht.readTemperature();
  analogWrite(analogin, anal);
  analogWrite(analogin2, anal2);
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print(page);
  if (round(millis() / 10) % 2 == 0) {
    seconds++;
  }
  if (minuters == 60) {
    minuters = 0;
    hour ++;
  }
  if (hour == 24) {
    hour = 0;
  }
  if (seconds == 60) {
    seconds = 0;
    minuters++;
  }
 
  if ( page == 0 ) {
    LCD.setCursor(3, 1);
    LCD.print("version 0.5");
    LCD.setCursor(2, 0);
    LCD.print("page");
  }
  if ( page == 1 ) {
    LCD.setCursor(2, 0);
    LCD.print("page");
    LCD.setCursor(0, 1);
    LCD.print("time ");
    LCD.setCursor(7, 1);
    LCD.print(hour);
    LCD.print(".");
    LCD.print(minuters);
    LCD.print(".");
    LCD.print(seconds);
  }
  if ( page == 2 ) {
    LCD.setCursor(0, 1);
    LCD.print("signal");
    LCD.setCursor(2, 0);
    LCD.print("page analog");
    LCD.setCursor(9, 1);
    if (millis() > 1000) {
      if (sensor_mode == 1) {
        LCD.print( maximal - analogRead(pinSensor));
      }
      if (sensor_mode == 0) {
        LCD.print(  analogRead(pinSensor));
      }
      LCD.setCursor(12, 1);
    }
    if (!digitalRead(6) == 1) {
      sensor_mode = 1;

    }
    if (!digitalRead(8) == 1) {
      sensor_mode = 0;

    }
  }
  if ( page == 3 ) {
    LCD.setCursor(0, 1);
    LCD.print("signal");
    LCD.setCursor(2, 0);
    LCD.print("page digital 1 ");
  }
  if ( page == 4 ) {
    LCD.setCursor(0, 1);
    LCD.print("mode");
    if ( light_mode == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("on");
    }
    if ( !light_mode == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("off");
    }
    LCD.setCursor(2, 0);
    LCD.print("page reley 1");
    if (!digitalRead(6) == 1) {
      light_mode = 1;
      digitalWrite(9, HIGH);
    }
    if (!digitalRead(8) == 1) {
      light_mode = 0;
      digitalWrite(9, LOW);
    }
  }
  if ( page == 5 ) {
    LCD.setCursor(0, 1);
    LCD.print("mode");
    if (mater_mode == 1) {
      LCD.print(" on");
    }
    if (!mater_mode == 1) {
      LCD.print(" off");
    }
    LCD.setCursor(2, 0);
    LCD.print("page relay 2");


  }
  if ( page == 6 ) {
    LCD.setCursor(0, 1);
    LCD.print("signal ");
    if (digitalRead(4) == 1) {
      LCD.print("off");
    }
    if (!digitalRead(4) == 1) {
      LCD.print("on");
    }
    LCD.setCursor(2, 0);
    LCD.print("page digital 2");
  }
  if ( page == 7 ) {
    LCD.setCursor(0, 1);
    LCD.print("time ");
    LCD.print((millis() / 60000));
    LCD.setCursor(2, 0);
    LCD.print("page timer");
  }
  if ( page == 8 ) {
    LCD.setCursor(0, 1);
    LCD.print("mode ");
    LCD.print(relay2);
    if ( relay == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("on");
    }
    if ( !relay == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("off");
    }
    
    LCD.setCursor(2, 0);
    LCD.print("page reley 3");
    if (!digitalRead(6) == 1) {
      relay2 ++;
  //    digitalWrite(5, HIGH);
    }
    if (!digitalRead(8) == 1) {
      relay2 --;
 //     digitalWrite(5, LOW);
    }
    if(relay2 > 2){
      relay2 == 0;
    }
     if(relay2 < 0){
      relay2 == 2;
    }
  }
  if ( page == 9 ) {
    LCD.setCursor(0, 1);
    LCD.print("r2 mode ");
    LCD.print(water_mode );

    LCD.setCursor(2, 0);
    LCD.print("settings");
    if (!digitalRead(6) == 1) {
      water_mode ++;

    }
    if (!digitalRead(8) == 1) {
      water_mode --;

    }
    if (water_mode > 2) {
      water_mode = 0;
    }
    if (water_mode < 0) {
      water_mode = 2;
    }
  }
  if ( page == 10 ) {
    LCD.setCursor(0, 1);
    LCD.print("set ");
    LCD.print(set);
    LCD.setCursor(2, 0);
    LCD.print(" analog set ");
    if (!digitalRead(6) == 1) {
      set = set + 100;
    }
    if (!digitalRead(8) == 1) {
      set = set - 100;
    }
    if (set > 1200) {
      set = 1200;
    }

    if (set < 0) {
      set = 0;
    }



  }
  if ( page == 11 ) {
    LCD.setCursor(0, 1);
    LCD.print("mode");
    if ( r4 == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("on");
    }
    if ( !r4 == 1)  {
      LCD.setCursor(9, 1);
      LCD.print("off");
    }
    LCD.setCursor(2, 0);
    LCD.print("page reley 4");
    if (!digitalRead(6) == 1) {
      r4 = 1;
      digitalWrite(13, HIGH);
    }
    if (!digitalRead(8) == 1) {
      r4 = 0;
      digitalWrite(13  , LOW);
    }
  }
  if ( page == 12 ) {
    LCD.setCursor(0, 1);
    LCD.print("signal ");
    LCD.print(anal);
    LCD.setCursor(2, 0);
    LCD.print(" in analog ");
    if (!digitalRead(6) == 1) {
      anal = anal + 5;
    }
    if (!digitalRead(8) == 1) {
      anal = anal - 5;
    }
  }
  if ( page == 13 ) {
    LCD.setCursor(0, 1);
    LCD.print("signal ");
    LCD.print(anal2);
    LCD.setCursor(2, 0);
    LCD.print(" in analog2 ");
    if (!digitalRead(6) == 1) {
      anal2 = anal2 + 5;
    }
    if (!digitalRead(8) == 1) {
      anal2 = anal2 - 5;
    }
  }
    if ( page == 14 ) {
   
    LCD.setCursor(0, 1);
    LCD.print("h");
    LCD.print(h);
    LCD.print("% t");
    LCD.print(t);
    LCD.print("C");
    LCD.setCursor(2, 0);
    LCD.print(" climate ");
    //     if (isnan(h) || isnan(t)) {
    // return;
    // }

  }
    if ( page == 15 ) {
    LCD.setCursor(0, 1);
    LCD.print("set2 ");
    LCD.print(set2);
    LCD.setCursor(2, 0);
    LCD.print(" analog set2 ");
    if (!digitalRead(6) == 1) {
      set2 = set2 + 100;
    }
    if (!digitalRead(8) == 1) {
      set2 = set2 - 100;
    }
    if (set2 > 1200) {
      set2 = 0;
    }

    if (set < 0) {
      set2 = 1200;
    }



  }



  if (!digitalRead(3) == 1) {
    page ++;
    if (page > pages) {
      page = 1;
    }
  }
  if (!digitalRead(12) == 1) {
    page --;
    if (page < 1) {
      page = pages;
    }
  }
 
  if (water_mode == 1 ) {
    if ( analogRead(pinSensor) > set) {
      digitalWrite(7, HIGH);
      mater_mode = 1;
    }
    if (analogRead(pinSensor) < set) {
      digitalWrite(7, LOW);
      mater_mode = 0;

    }
  }
  if (water_mode == 0) {
    if (millis() - relay_timer > period) {
      Serial.println("a");
      relay_timer = millis();
      digitalWrite(7, HIGH);
      mater_mode = 1;
    }
  }
  if (water_mode == 0) {
    if ( mater_mode == 1) {
      if (millis() - relay_timer > watering_time ) {
        watr_timer = millis();
        digitalWrite(7, LOW);
        mater_mode = 0;
      }
    }
  }
  if (water_mode == 2 ) {
    if (! digitalRead(4) == 1) {
      digitalWrite(7, HIGH);
      mater_mode = 1;
    }
    if (! digitalRead(4) == 0) {
      digitalWrite(7, LOW);
      mater_mode = 0;

    }
  }
   if (relay2 == 0 ) {
    if ( analogRead(pinSensor) > set2) {
      digitalWrite(5, HIGH);
      relay = 1;
    }
    if (analogRead(pinSensor) < set2) {
      digitalWrite(5, LOW);
      relay = 0;

    }
  }
    if (relay2 == 1 ) {
    if (! digitalRead(4) == 1) {
      digitalWrite(5, HIGH);
     relay = 1;
    }
    if (! digitalRead(4) == 0) {
      digitalWrite(5, LOW);
      relay  = 0;

    }
  }

}
