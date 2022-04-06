#include <iostream> 
#include <cmath>
#include <string> 
#include "SHT31.h" //Humidity & Temperature sensor

using namespace std; 

 SHT31 sensorHT = SHT31(); //I2C
 const int pinLight=A0; //Analog 
 

class Data {
    protected:
      String ID;
      int SensorData;
    
    public: 
      Data(){ //Constructeur
      ID="NONE";
      SensorData=0;
      }  
      Data(String a){// Constructeur avec ID
        ID=a;
        SensorData=0;
      }
      virtual void compareData() = 0;
      int getData(){return SensorData;}
};

class Humidity : public Data { 
  public :
    Humidity():Data("HUMIDITY"){}// Constructeur 
    void compareData (){ 
        float humidity = sensorHT.getHumidity();
        if (SensorData == 0 || SensorData != int(round(humidity))){
          //Serial.print ("Humidity: ");
          //Serial.println (humidity);
          SensorData = int(round(humidity)); 
        }
    }  
};

class Temperature : public Data { 
  public :
    Temperature():Data("TEMPERATURE"){} // Constructeur
    void compareData (){ 
        float temperature = sensorHT.getTemperature();
        if (SensorData == 0 || SensorData != int(round(temperature))){
          //Serial.print ("Temperature: ");
          //Serial.println (temperature);
          SensorData = int(round(temperature)); 
        }
    }  
};

class Light : public Data { 
  public : 
    Light():Data("LIGHT"){ SensorData=-1;} //Constructeur 
    void compareData(){ //SensorDATA (-1 = not initialized, 0 = day, 1 = night)
       int light = analogRead(pinLight);// [0;678]
       Serial.print ("Light: ");
       Serial.println(light); 
       if (SensorData == -1 && light <250){ 
            SensorData = 1; 
       }
       else if (SensorData == -1 && light >=250) {
            SensorData = 0; 
       }
       else if (SensorData == 1 && light >=300 ){
          SensorData = 0;         
       }
       else if (SensorData == 0 && light <=200 ){ 
          SensorData = 1;
       }
    }
};




void setup() {
  sensorHT.begin(); 
  Serial.begin(9600);
 

}
 Humidity H1= Humidity();
 Temperature T1= Temperature();
 Light L1= Light(); 
 
void loop() {
  /********TEST HUMIDITY********/
  /*Serial.print("DATA(ANCIEN)");
  Serial.println(T1.getData()); 
  T1.compareData();
  Serial.print("DATA(NOUVEAU)");
  Serial.println(T1.getData());*/

  /******TEST TEMPERATURE******/
  /*Serial.print("DATA(ANCIEN)");
  Serial.println(T1.getData()); 
  T1.compareData();
  Serial.print("DATA(NOUVEAU)");
  Serial.println(T1.getData());*/

  /*********TEST LIGHT*********/
  Serial.print("DATA(ANCIEN)");
  Serial.println(L1.getData()); 
  L1.compareData();
  Serial.print("DATA(NOUVEAU)");
  Serial.println(L1.getData());

  
  delay(3000);

}
