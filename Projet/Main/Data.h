#ifndef Data_H
#define Data_H

#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include "SHT31.h"

using namespace std;



extern SHT31 sensorHT;
const int pinLight=A0;

class MapData { 
  protected :
  static std::map <String, int> Data_map;
  
  public:
  //METHODE DE GESTION DE MAP
  void beginData();//initialisation de la MAP
  static const std::map <String, int>& GetMap(); //Récupère Data_Map
  void afficher_map(); //Affiche le contenu de Data_Map
  friend class Data;
}; 

class Data {
  protected:
      String ID;
      int SensorData;
      
  public:
  //CONSTRUCTEURS
  Data();  
  Data(String a); 
  //MODIFICATION DE LA MAP
  virtual void compareData(MapData Dmap) = 0;
  int getData();
  void change_map (MapData Dmap);
  friend class MapData;
}; 

class Humidity : public Data { 
  public: 
  Humidity():Data("HUMIDITY"){}; //Constructeur 
  void compareData (MapData Dmap); //Compare les données et change les valeurs de la MAP 
};

class Temperature : public Data { 
  public :
    Temperature():Data("TEMPERATURE"){};// Constructeur
    void compareData (MapData Dmap);//Compare les données et change les valeurs de la MAP 
};

class Light : public Data { 
  public : 
    Light():Data("LIGHT"){}; //Constructeur 
    void compareData(MapData Dmap); //Compare les données et change les valeurs de la MAP 
    //SensorDATA (-1 = not initialized, 0 = day, 1 = night)
};


void InitSensor (); 
  
#endif
