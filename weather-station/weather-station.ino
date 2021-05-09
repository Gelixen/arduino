#include <LiquidCrystal.h>
#include "cactus_io_DHT22.h"

#define DHT22_PIN 8

DHT22 dht(DHT22_PIN);

const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en,d4, d5, d6, d7);

const int sensorPin = A5;
const float baselineTemp = 20.0;

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  lcd.begin(16, 2);
  //lcd.print("Hello, world!");
}

void loop() {  
  dht.readHumidity();
  dht.readTemperature();

  if (isnan(dht.humidity) || isnan(dht.temperature_C)) {
    lcd.print("DHT sensor read failure!");
    return;
  }

//  double summedTemp = 0;
  double maxTemp = 0;
  double minTemp = 99;

  for(int i=0; i<100; i++) {
    int sensorValue = analogRead(sensorPin);
    double voltage = (sensorValue / 1024.0 ) * 5.0;
    double temperature = (voltage - .5) * 100;
//    summedTemp += temperature;

    if (temperature > maxTemp) {
      maxTemp = temperature;
    }

    if (temperature < minTemp) {
      minTemp = temperature;
    }
  }
  
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(dht.temperature_C);
  lcd.print(" H:");
  lcd.print(dht.humidity);

  lcd.setCursor(0,1);
  lcd.print("+:");
  lcd.print(maxTemp);
  lcd.print(" -:");
  lcd.print(minTemp);

  delay(1000);
}
