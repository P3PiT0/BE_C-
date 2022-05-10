#ifndef Buzzer_H
#define Buzzer_H

#include <string>
#include <cmath>
#include <Arduino.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

const int buzzerPin=D7;

class Buzzer {

  public :
    //METHODE D'INITIALISATION 
  void beginBuzzer(); //initialisation 
    //METHODE D'UTILISATION DU BUZZER
  void beep(int note, int duration); //joue une note
  void song(); //joue une musique (appelée dans le main lors de l'interruption)
};

#endif
