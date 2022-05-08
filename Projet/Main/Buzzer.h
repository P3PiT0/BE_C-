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
  void beginBuzzer();
  void beep(int note, int duration);
  void song();
};

#endif
