#include "Data.h"
SHT31 sensorHT;

    void MapData::beginData(){
      Data_map["HUMIDITY"]=0;
      Data_map["TEMPERATURE"]=0;
      Data_map["LIGHT"]=0;
    }
    
    const std::map <String, int>& MapData::GetMap(){
      return Data_map;
    }
   
    void MapData::afficher_map(){
      for ( std::map<String,int>::iterator it = Data_map.begin(); it!=Data_map.end(); it++){
              Serial.print("ID : ");
              Serial.print(it->first);
              Serial.print(", Valeur : ");
              Serial.println(it->second);
          }
    }
      
    Data::Data(){ 
      ID="NONE";
      SensorData=0;
    }  
    Data::Data(String a){
      ID=a;
      SensorData=0;
    }
    int Data::getData(){return SensorData;}
    void Data::change_map (MapData Dmap){
      Dmap.Data_map[ID]=SensorData;
    }
    
    //Humidity::Humidity():Data("HUMIDITY"){}// Constructeur 
    void Humidity::compareData (MapData Dmap){ 
        float humidity = sensorHT.getHumidity();
        if (SensorData == 0 || SensorData != int(round(humidity))){
          SensorData = int(round(humidity)); 
          change_map(Dmap);
        }
    }  

    //Temperature::Temperature():Data("TEMPERATURE"){} 
    void Temperature::compareData (MapData Dmap){ 
        float temperature = sensorHT.getTemperature();
        if (SensorData == 0 || SensorData != int(round(temperature))){
          SensorData = int(round(temperature)); 
          change_map(Dmap);
        }
    }  
    
    //Light::Light():Data("LIGHT"){ SensorData=-1;} //Constructeur 
    void Light::compareData(MapData Dmap){ //SensorDATA (-1 = not initialized, 0 = day, 1 = night)
       int light = analogRead(pinLight);// [0;678]
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

    void InitSensor (){
        sensorHT.begin();
    }
