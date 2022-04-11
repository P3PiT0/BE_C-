#include <iostream> 
#include <cmath>
#include <map> 
#include <string> 
#include "SHT31.h" //Humidity & Temperature sensor

using namespace std; 

 SHT31 sensorHT = SHT31(); //I2C
 const int pinLight=A0; //Analog 

 class MapData{
  protected :
  static std::map <String, int> Data_map;
  public:
   /* MapData(){ 
      Data_map.insert(pair<String, int>("HUMIDITY", 0));
      Data_map.insert(pair<String, int>("TEMPERATURE", 0));
      Data_map.insert(pair<String, int>("LIGHT", 0));*/
      
      /*Data_map["HUMIDITY"]=0;
      Data_map["TEMPERATURE"]=0;
      Data_map["LIGHT"]=0;*/
    //}
    static std::map <String, int> GetMap(){
      return Data_map;
    }
    void afficher_map(){
      for ( std::map<String,int>::iterator it = Data_map.begin(); it!=Data_map.end(); it++){
              Serial.print("ID : ");
              Serial.print(it->first);
              Serial.print(", Valeur : ");
              Serial.println(it->second);
          }
    }
    friend class Data;

};

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
      virtual void compareData(MapData Dmap) = 0;
      int getData(){return SensorData;}
      void change_map (MapData Dmap){
        Dmap.Data_map[ID]=SensorData;
      }
  friend class MapData;
};

class Humidity : public Data { 
  public :
    Humidity():Data("HUMIDITY"){}// Constructeur 
    void compareData (MapData Dmap){ 
        float humidity = sensorHT.getHumidity();
        if (SensorData == 0 || SensorData != int(round(humidity))){
          //Serial.printf("Humidity: %\d ",humidity);
          //Serial.print ("Humidity: "); 
          //Serial.println (humidity);
          SensorData = int(round(humidity)); 
          change_map(Dmap);
        }
    }  
};

class Temperature : public Data { 
  public :
    Temperature():Data("TEMPERATURE"){} // Constructeur
    void compareData (MapData Dmap){ 
        float temperature = sensorHT.getTemperature();
        if (SensorData == 0 || SensorData != int(round(temperature))){
          //Serial.printf("Temperature: %\d ",temperature);
          //Serial.print ("Temperature: ");
          //Serial.println (temperature);
          SensorData = int(round(temperature)); 
          change_map(Dmap);
        }
    }  
};

class Light : public Data { 
  public : 
    Light():Data("LIGHT"){ SensorData=-1;} //Constructeur 
    void compareData(MapData Dmap){ //SensorDATA (-1 = not initialized, 0 = day, 1 = night)
       int light = analogRead(pinLight);// [0;678]
       //Serial.print ("Light: ");
       //Serial.println(light); 
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
       change_map(Dmap);
    }
};


void setup() {
  Serial.begin(74880);
  sensorHT.begin();
}
 
 Humidity H1;//= Humidity();
 Temperature T1;//= Temperature();
 Light L1;//= Light(); 
 MapData M1;//= MapData();
 std::map <String, int> MapData::Data_map;

void loop() {
  Serial.println("piiiiiinte");
  H1.compareData(M1);
  T1.compareData(M1);
  L1.compareData(M1);
  M1.afficher_map(); 

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
 /* Serial.print("DATA(ANCIEN)");
  Serial.println(L1.getData()); 
  L1.compareData();
  Serial.print("DATA(NOUVEAU)");
  Serial.println(L1.getData());*/

  
  delay(3000);

}
