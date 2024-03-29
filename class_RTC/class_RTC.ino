//#include "mario.h"
#include <iostream>
#include "RTClib.h"
#include <map>
using namespace std;

RTC_DS1307 temps= RTC_DS1307();//define a object of DS1307 class


class RTC {
  protected :
  static std::map <String,int> Time;
  int h,m;
  bool one;
  public :

  void RefreshTime(){
    DateTime now = temps.now();
    Time["HEURE"]=now.hour();
    Time["MINUTE"]=now.minute();
    Time["JOUR"]=now.day();
    Time["MOIS"]=now.month();
    
  }

  void InitReveil (int h, int m){
    h=h;
    m=m;
    one=true;
  }

  void DelReveil(){
    one=false;
  }

  bool CheckReveil(){
    bool value =false;
    if (one==true && Time["HEURE"]==h && Time["MINUTE"]==m){
      value = true;
    }
    return value;
  }
  void  GetTime(){
    
    Serial.println("heure : ");
    Serial.print(Time["HEURE"]);
    Serial.println("minute : ");
    Serial.print(Time["MINUTE"]);
    Serial.println("jour : ");
    Serial.print(Time["JOUR"]);
    Serial.println("mois : ");
    Serial.print(Time["MOIS"]);
  }
};
 
    RTC tt;
    std::map <String,int> RTC::Time;
void setup()
{
    Serial.begin(74880);
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

void loop()
{
  delay(1000);
  
        tt.RefreshTime();
        tt.InitReveil(12,12);
        if (tt.CheckReveil()){
              //sing(1);
              delay(15000);
        }
  tt.GetTime();
  
}
