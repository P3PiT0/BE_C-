#include "Screen.h"
U8X8_SH1107_SEEED_128X128_HW_I2C u8x8(U8X8_PIN_NONE);

  void Screen::beginMap(){ 
    screen_data["HUMIDITY"]=0;
    screen_data["TEMPERATURE"]=0;
    screen_data["LIGHT"]=0;
    screen_data["HEURE"]=0;
    screen_data["MINUTE"]=0;
  }
 
  const std::map<String, int> Screen::BuildMap(std::map <String, int> MapCapt, std::map <String, int> MapTime) {
    std::map <String, int> new_map;
    for (std::map<String,int>::iterator it = MapCapt.begin(); it!=MapCapt.end(); it++){
          new_map[it->first]=it->second;
        }
    for (std::map<String,int>::iterator it = MapTime.begin(); it!=MapTime.end(); it++){
          new_map[it->first]=it->second;
        }
    return new_map;
  }
  
  void Screen::Afficher_MAP(){ 
    for (std::map<String,int>::iterator it = screen_data.begin(); it!=screen_data.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
    }
    
  void Screen::Afficher_temperature(int temp) {
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.draw2x2String(3,1,"T:");
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(8,2);
    u8x8.print(temp);
    }

  void Screen::Afficher_humidite(int hum){
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.draw2x2String(3,3,"Hum:");
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(11,4);
    u8x8.print(hum);
    }

  void Screen::Afficher_time(int heure, int minute){
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
  
