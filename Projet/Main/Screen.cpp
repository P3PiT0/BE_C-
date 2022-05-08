#include "Screen.h"
U8G2_SH1107_SEEED_128X128_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

  void Screen::beginMap(){ 
    screen_data["HUMIDITY"]=0;
    screen_data["TEMPERATURE"]=0;
    screen_data["LIGHT"]=0;
    screen_data["HEURE"]=0;
    screen_data["MINUTE"]=0;
  }
 
  std::map<String, int> Screen::BuildMap(std::map <String, int> MapCapt, std::map <String, int> MapTime) {
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
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(25,16, "T : ");
    u8g2.setCursor(55,16);
    u8g2.printf("%02d", temp);
    u8g2.setFont(u8g2_font_unifont_t_symbols);
    u8g2.drawGlyph(75, 11, 0x00b0);
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(85,15, "C");
  }

  void Screen::Afficher_humidite(int hum){
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(25,35, "H : ");
    u8g2.setCursor(55,35);
    u8g2.printf("%02d", hum);
  }

  void Screen::Afficher_time(int heure, int minut){
     u8g2.setFont(u8g2_font_ncenB24_tr); 
    u8g2.setCursor(15,74);//u8g2.setCursor(x,64);
    u8g2.printf("%02d", heure);
    u8g2.drawStr(55,74, "h");//u8g2.drawStr(x+40,64, "h");
    u8g2.setCursor(75,74);//u8g2.setCursor(x+60,64);
    u8g2.printf("%02d", minut);
  }

  void Screen::Day_mode(){
    u8g2.firstPage();
    do {
      u8g2.setFontMode(1); /* Transparent font mode with XOR drawing*/
      u8g2.setDrawColor(1);
      Afficher_temperature(screen_data["TEMPERATURE"]);
      Afficher_humidite(screen_data["HUMIDITY"]);
      Afficher_time(screen_data["HEURE"],screen_data["MINUTE"]);
    }while ( u8g2.nextPage() );
  }

  void Screen::Night_mode(){
    u8g2.firstPage();
    do {
      u8g2.setFontMode(1); /* Transparent font mode with XOR drawing*/
      u8g2.setDrawColor(1);
      u8g2.drawBox(0, 0, 128, 128); /*White screen*/
      u8g2.setDrawColor(2);
      Afficher_temperature(screen_data["TEMPERATURE"]);
      Afficher_humidite(screen_data["HUMIDITY"]);
      Afficher_time(screen_data["HEURE"],screen_data["MINUTE"]); 
    }while ( u8g2.nextPage() );
   }

  //Méthode envoi les donner à l'écran en mode jour ou nuit 
  void Screen::Write_to_screen(){
    if (screen_data["LIGHT"]==0){
      Day_mode();
    }
    else if (screen_data["LIGHT"]==1){
      Night_mode();
    }
  }
     Screen& Screen::operator=(std::map<String, int>& MAP){
        screen_data["HUMIDITY"] = MAP["HUMIDITY"];
        screen_data["TEMPERATURE"] = MAP["TEMPERATURE"];
        screen_data["LIGHT"] = MAP["LIGHT"];
        screen_data["HEURE"] = MAP["HEURE"];
        screen_data["MINUTE"] = MAP["MINUTE"];
        return (*this);
    }
  
