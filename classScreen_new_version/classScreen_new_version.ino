#include <Arduino.h>
#include <iostream>
#include <U8g2lib.h>
#include <map>
#include <string>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1107_SEEED_128X128_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


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

  //Remplie screen_data avec les données recus 
  const std::map  <String, int> BuildMap(std::map <String, int> MapCapt, std::map <String, int> MapTime) {

    std::map <String, int> new_map;
    new_map.insert(MapCapt.begin(), MapCapt.end());
    new_map.insert(MapTime.begin(), MapCapt.end());
    
    return new_map;
    }

  //Afficher MAP
  void Afficher_MAP(){
    
    for (std::map<String,int>::iterator it = screen_data.begin(); it!=screen_data.end(); it++){
      Serial.print("ID : ");
      Serial.print(it->first);
      Serial.print(", Valeur : ");
      Serial.println(it->second);
      }
    

    };

  //Méthodes d'affichage utilisé par Day_mode et Night_mode
  void Afficher_temperature(int temp) {
  
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(25,16, "T : ");
    u8g2.setCursor(55,16);
    u8g2.printf("%02d", temp);
    u8g2.setFont(u8g2_font_unifont_t_symbols);
    u8g2.drawGlyph(75, 11, 0x00b0);
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(85,15, "C");
  }

  void Afficher_humidite(int hum){
 
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(25,35, "H : ");
    u8g2.setCursor(55,35);
    u8g2.printf("%02d", hum);
  }

  void Afficher_time(int heure, int minute){
    
    u8g2.setFont(u8g2_font_ncenB24_tr); 
    u8g2.setCursor(15,74);//u8g2.setCursor(x,64);
    u8g2.printf("%02d", heure);
    u8g2.drawStr(55,74, "h");//u8g2.drawStr(x+40,64, "h");
    u8g2.setCursor(75,74);//u8g2.setCursor(x+60,64);
    u8g2.printf("%02d", minute);
  }

  //Méthodes mode jour/nuit
  void Day_mode(){
  u8g2.firstPage();
  do {
    u8g2.setFontMode(1); /* Transparent font mode with XOR drawing*/
    u8g2.setDrawColor(1);
    
    Afficher_temperature(screen_data["TEMPERATURE"]);
    Afficher_humidite(screen_data["HUMIDITY"]);
    Afficher_time(screen_data["HEURE"],screen_data["MINUTE"]);
    
  }while ( u8g2.nextPage() );
  }

  void Night_mode(){
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
  void Write_screen(){
    if (screen_data["LIGHT"]==0){
      Day_mode();
    }
    else if (screen_data["LIGHT"]==1){
      Day_mode();
    }
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
  u8g2.begin(); 

  Serial.begin(74880);
  Serial.print("coucou");
  S1.beginMap();
}

void loop() {

  std::map <String,int> Capteur;
  std::map <String,int> Time;
  std::map <String,int> LaMap;

  Capteur["HUMIDITY"]=10;
  Capteur["TEMPERATURE"]=23;
  Capteur["LIGHT"]=210;
  Time["HEURE"]=18;
  Time["MINUTE"]=15;

  Afficher_MAP2(S1.BuildMap(Capteur,Time));
  delay(5000);
  Serial.print("coucou");

  S1.BuildMap(Capteur,Time);
  S1.Day_mode();
  delay(2000);
  S1.Night_mode();
  delay(2000);
  


  
}
