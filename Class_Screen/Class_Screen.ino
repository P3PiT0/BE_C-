#include <Arduino.h>
#include <iostream>
#include <U8x8lib.h>
#include <map>
#include <string>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SH1107_SEEED_128X128_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

using namespace std;


class screen {
  
  protected:
  std::map  <String, int> screen_data;

  public :
  //Initialise screen_data
  void beginMap(){
    screen_data["HUMIDITY"]=0;
    screen_data["TEMPERATURE"]=0;
    screen_data["LIGHT"]=0;
    screen_data["HEURE"]=0;
    screen_data["MINUTE"]=0;
    }

  //Retourne une MAP regroupant les différentes informations issues des capteurs et du RTC 
  const std::map<String, int> BuildMap(std::map <String, int> MapCapt, std::map <String, int> MapTime) {
    std::map <String, int> new_map;
    for (std::map<String,int>::iterator it = MapCapt.begin(); it!=MapCapt.end(); it++){
          new_map[it->first]=it->second;
        }
    for (std::map<String,int>::iterator it = MapTime.begin(); it!=MapTime.end(); it++){
          new_map[it->first]=it->second;
        }
    return new_map;
  }

  //std::map<String,int> operator +=(const std::map<String,int>& A) { 
  //    for (std::map<String,int>::iterator it = A.begin(); it!=A.end(); it++){
  //        this[it->first]=it->second;
  //      }
  //  return (*this);
  //  }

  //Afficher MAP
  void Afficher_MAP(){
    
    for (std::map<String,int>::iterator it = screen_data.begin(); it!=screen_data.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
    

    };

  //Méthodes d'affichage
  void Afficher_temperature(int temp) {
  
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.draw2x2String(3,1,"T:");
  
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(8,2);
    u8x8.print(temp);
    }

  void Afficher_humidite(int hum){

    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.draw2x2String(3,3,"Hum:");
  
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(11,4);
    u8x8.print(hum);
    
    }

  void Afficher_time(int heure, int minute){

    u8x8.setFont(u8x8_font_inb33_3x6_n);
    u8x8.setCursor(1,6);
    u8x8.printf("%02d", heure);
  
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.draw2x2String(7,9,"h");
    
    u8x8.setFont(u8x8_font_inb33_3x6_n);
    u8x8.setCursor(10,6);
    //u8x8.printf("%02d",0);
    u8x8.printf("%02d", minute);
   
    }

  Screen& operator=(std::map<String, int>& MAP){
        if ((screen_data["HUMIDITY"]) != (MAP["HUMIDITY"])){
          screen_data["HUMIDITY"] = MAP["HUMIDITY"];
          Serial.print("Affichage Humidity");
        }
        else if (screen_data["TEMPERATURE"] != MAP["TEMPERATURE"]){
          screen_data["TEMPERATURE"] = MAP["TEMPERATURE"];
          Serial.print("Affichage Temperature");
        }
        //LIGHT DIRECTEMENT DANS AFFICHAGE
        screen_data["HEURE"] = MAP["HEURE"];
        screen_data["MINUTE"] = MAP["MINUTE"];
        return (*this);
    }
  
  };

screen S1;

void Afficher_MAP2(std::map<String,int> mamap){
    
    for (std::map<String,int>::iterator it = mamap.begin(); it!=mamap.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
}


void setup() {
//  u8x8.begin();
//  u8x8.setPowerSave(0);

  Serial.begin(74880);
  Serial.print("coucou");
  S1.beginMap();
}

void loop() {

  std::map <String,int> Capteur;
  std::map <String,int> Time;

  Capteur["HUMIDITY"]=10;
  Capteur["TEMPERATURE"]=23;
  Capteur["LIGHT"]=210;
  Time["HEURE"]=18;
  Time["MINUTE"]=15;

  Afficher_MAP2(S1.BuildMap(Capteur,Time));
  delay(5000);
  Serial.print("coucou");


  
}
