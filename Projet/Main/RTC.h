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
  void RefreshTime(); //met à jour le temps
  std::map <String,int> RetMap(); //retourne la map pour l'exploiter dans le main
  void GetTime(); // affichage de l'heure (débug) 
   
  // METHODE DE GESTION DU REVEIL
  void InitReveil(int HEURE,int MINUTE);  //initialisation du réveil (InitReveil(19,8)) => le réveil sonnera à 19h08
  void DelReveil(); // suppression du réveil
};







#endif
