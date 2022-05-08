#ifndef RTC_H
#define RTC_H

#include <iostream>
#include "RTClib.h"
#include <map>
using namespace std;

extern RTC_DS1307 temps;

#define Reveil 1 

class rtc {
  protected: 
  static std::map <String,int> Time;
  int h,m;
  bool On;

  public: 
  //METHODE D'INITIALISATION DE LA CONNEXION ET DE LA MAP
  void beginMap();
  void setupRTC();

  // METHODE DE GESTION DE MAP TIME
  void RefreshTime();
  std::map <String,int> RetMap();
  void GetTime();
   
  // METHODE DE GESTION DU REVEIL
  void InitReveil(int HEURE,int MINUTE); 
  void DelReveil();
}







#endif
