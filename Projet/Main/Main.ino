
#include "Screen.h"
#include "Data.h"
#include <Arduino.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

Screen S1;
MapData M1;
Humidity H1;
Temperature T1;
Light L1;

std::map <String, int> MapData::Data_map;



void Afficher_MAP2(std::map<String,int> mamap){
    Serial.println("AfficherMap");
    for (std::map<String,int>::iterator it = mamap.begin(); it!=mamap.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
}

void setup() {
  Serial.begin(74880);
  InitSensor();
  //sensorHT.begin();
  S1.beginMap();
  //M1.beginData(); 
}

void loop() {
  std::map <String,int> Capteur;
  std::map <String,int> Time;
  H1.compareData(M1);
  T1.compareData(M1);
  L1.compareData(M1);
  Capteur=M1.GetMap();
  M1.afficher_map(); 
  Time["HEURE"]=18;
  Time["MINUTE"]=15;
  Afficher_MAP2(S1.BuildMap(Capteur,Time));
  delay(5000);
}
