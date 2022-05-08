#ifndef Screen_H
#define Screen_H

#include <map>
#include <U8g2lib.h>
#include <Arduino.h>
#include <iostream>
#include <string>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

using namespace std;

extern U8G2_SH1107_SEEED_128X128_1_HW_I2C u8g2;

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
  void Afficher_time(int heure, int minut);
  void Day_mode(); //Affichage sur fond blanc (affichage jour)
  void Night_mode(); //Affichage sur fond noir (affichage nuit)
  void Write_to_screen();//Méthode globale d'envoie des données à l'écran  

  //OPERATEUR
  /*copie la map générée par Build dans Screen_data*/
  Screen &operator=(std::map<String, int>& MAP); 
  };

#endif
