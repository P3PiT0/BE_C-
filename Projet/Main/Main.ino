#include "RTC.h"
#include "Screen.h"
#include "Data.h"
#include "Buzzer.h"
#include <Arduino.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

rtc T;  
Screen S;
MapData M1;
Humidity H1;
Temperature T1;
Light L1;
Buzzer Buz;


std::map <String, int> MapData::Data_map;
std::map <String,int> rtc::Time;



/**********AFFICHAGE MAP POUR DEBUG****************/
/*void Afficher_MAP2(std::map<String,int> mamap){
    Serial.println("AfficherMap");
    for (std::map<String,int>::iterator it = mamap.begin(); it!=mamap.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
}*/

void setup() {
  Serial.begin(74880);
  u8g2.begin();
  //InitSensor();
  S.beginMap();
  T.beginMap(); 
  T.setupRTC();
  Buz.beginBuzzer();
}

void loop() {
  std::map <String,int> MAP;
  std::map <String,int> Capteur;
  std::map <String,int> Time;
  H1.compareData(M1);
  T1.compareData(M1);
  L1.compareData(M1);
  Capteur=M1.GetMap();
  T.InitReveil(21,50);

  //INTERRUPTION ACTIVE SI L'HEURE CORRESPOND A L'HEURE D'ACTIVATION DU REVEIL
  try{ 
        T.RefreshTime();
    }
        catch (int e){
        if (e==Reveil){
             Buz.song();
             Serial.println("Il est l'heure de se lever");
        }
    }
    
  Capteur=M1.GetMap();
  Time = T.RetMap();
  Serial.println("Affectation Map");
  MAP=S.BuildMap(Capteur,Time);
  Serial.println("Construction Map");
  S=MAP;
  Serial.println("Affichage nouvelle MAP");
  S.Afficher_MAP();
  Serial.println("Affichage de la MAP à l'écran");
  S.Write_to_screen();
  delay(1000);
}
