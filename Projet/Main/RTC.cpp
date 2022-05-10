#include "RTC.h"
RTC_DS1307 temps;

  void rtc::beginMap(){ 
    Time["HEURE"]=0;
    Time["MINUTE"]=0;
  }

   void rtc::RefreshTime(){
    DateTime now = temps.now();
    Time["HEURE"]=now.hour();
    Time["MINUTE"]=now.minute();
    if (On==true && Time["HEURE"]==h && Time["MINUTE"]==m && now.second()>30){
      throw Reveil;
    }
  }

  std::map <String,int> rtc::RetMap(){
    return Time;
  }

  void rtc::GetTime(){

    Serial.println("heure : ");
    Serial.print(Time["HEURE"]);
    Serial.println("minute : ");
    Serial.print(Time["MINUTE"]);
  }

  void rtc::InitReveil (int HEURE, int MINUTE){
    h=HEURE;
    m=MINUTE;
    On=true;
  }

  void rtc::DelReveil(){
    On=false;
  }

  void rtc::setupRTC(){
  // Attente de la connection serie avec l'Arduino
  while (!Serial);
  // Lance le communication I2C avec le module RTC et 
  // attend que la connection soit operationelle
  while (! temps.begin()) {
    Serial.println("Attente du module RTC...");
    delay(1000);
  }
  // Mise à jour de l'horloge du module RTC avec la date et 
  // l'heure courante au moment de la compilation de ce croquis
  temps.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("Horloge du module RTC mise a jour");
  }
  
