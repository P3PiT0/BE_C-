#ifndef Screen_H
#define Screen_H

#include <map>
#include <U8x8lib.h>
#include <Arduino.h>
#include <iostream>
#include <string>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

using namespace std;


extern U8X8_SH1107_SEEED_128X128_HW_I2C u8x8;

class Screen { 
  protected:
  std::map  <String, int> screen_data;

  public :
  
  //METHODE DE GESTION DE MAP
  void beginMap(); //Initialisation de la MAP
  std::map<String, int> BuildMap(std::map <String, int> MapCapt, std::map <String, int> MapTime); //Retourne une MAP regroupant les différentes informations issues des capteurs et du RTC 
  void Afficher_MAP(); //Méthode pour l'affichage d'une MAP
  
  //METHODE D'AFFICHAGE SUR L'ECRAN
  void Afficher_temperature(int temp);
  void Afficher_humidite(int hum);
  void Afficher_time(int heure, int minute);

  //OPERATEUR
  Screen &operator=(std::map<String, int>& MAP);
  };

#endif
