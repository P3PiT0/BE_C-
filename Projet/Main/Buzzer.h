#ifndef Buzzer_H
#define Buzzer_H

#include "Notes.h"

class Buzzer {

  protected:
  const int buzzerPin=D7;

  public :
  void beginBuzzer();
  void beep(int note, int duration);
  void song();
};

#endif
