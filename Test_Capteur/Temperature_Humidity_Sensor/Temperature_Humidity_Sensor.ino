#include "SHT31.h"

SHT31 sht31 = SHT31();

void setup() {
  Serial.begin(9600);
  sht31.begin();  
}

void loop() {

  float temperature = sht31.getTemperature();
  float humidity = sht31.getHumidity();
  Serial.print("Temperature :");
  Serial.println(temperature);
  Serial.print("Humidity :");
  Serial.println(humidity);
  
  delay(1000);// wait for a second
}
