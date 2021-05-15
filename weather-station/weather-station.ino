#include <LiquidCrystal.h>
#include "cactus_io_DHT22.h"

#define DHT22_PIN 8

DHT22 dht(DHT22_PIN);

const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int photoresistorPin = A5;

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {  
  dht.readHumidity();
  dht.readTemperature();

  float temperature = dht.temperature_C;
  float humidity = dht.humidity;
  float realFeel = dht.computeHeatIndex_C();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.print("DHT sensor read failure!");
    return;
  }

  // -2 to avoid 3-digit number
  int photoresistorValue = (analogRead(photoresistorPin) / 10) - 2;

  printValuesToLCD(temperature, humidity, realFeel, photoresistorValue);

  String output = String(temperature) + "," + humidity + "," + photoresistorValue;
  Serial.println(output);

  delay(2000);
}

void printValuesToLCD(float temperature, float humidity, float realFeel, int photoresistorValue) {
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("RF: ");
  lcd.print(realFeel);

  lcd.print(" ");
  lcd.print(photoresistorValue);
}
