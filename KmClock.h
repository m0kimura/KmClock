//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#ifndef KMCLOCK_H
#define KMCLOCK_H
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#define NUM 12        // number of the LEDs

class KmClock{
  public:
    KmClock(int pin, long mon, long moff);
    void begin(int hr, int hg, int hb, int mr, int mg, int mb);
    void time(int h, int m);
    void show();
    Adafruit_NeoPixel Pixels;
    long Mon;
    long Moff;
    int Pin;
    int Hc[3];
    int Mc[3];
    int Hour;
    int Min;
    long Save;
    int State;

  private:
    void bright(int i, int r, int g, int b);
};

#endif
