//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#include "Arduino.h"
#include "KmClock.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif
KmClock::KmClock(int pin, long mon, long moff){
  Pin=pin; Mon=mon; Moff=moff;
  Pixels=Adafruit_NeoPixel(NUM, pin, NEO_GRB + NEO_KHZ800);
}

void KmClock::begin(int hr, int hg, int hb, int mr, int mg, int mb){
  Hc[0]=hr, Hc[1]=hg; Hc[2]=hb; Mc[0]=mr, Mc[1]=mg; Mc[2]=mb; State=-1;
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  Pixels.begin();
  KmClock::bright(0, 200, 0, 0); delay(300);
  KmClock::bright(1, 0, 200, 0); delay(300);
  KmClock::bright(2, 0, 0, 200); delay(300);
  KmClock::bright(0, 0, 0, 0); delay(300);
  KmClock::bright(1, 0, 0, 0); delay(300);
  KmClock::bright(2, 0, 0, 0); delay(300);
}

void KmClock::time(int h, int m){
  if(h>12){h=h-12;} Hour=h; Min=m/5; State=0; Save=micros();
}
void KmClock::show(){
  if(State<0){return;}
  long t=micros();
  long d=t-Save;
  bool f=false;
  long m;
  if(State==0){
    m=Mon*1000; if(d>m){f=true;}
}
  else if(State==1){
    m=Moff*1000; if(d>m){f=true;}
}
  if(f){
    for(int i=0; i<NUM; i++){bright(i, 0, 0, 0);}
    if(Hour==Min){
      if(State==1){bright(Min, Mc[0], Mc[1], Mc[2]); State=0;}
      else{KmClock::bright(Hour, Hc[0], Hc[1], Hc[2]); State=1;}
    }else{
      bright(Hour, Hc[0], Hc[1], Hc[2]);
      if(State==1){
        KmClock::bright(Min, Mc[0], Mc[1], Mc[2]); State=0;
      }else{
        State=1;
      }
    }
    Save=t;
  }
}

void KmClock::bright(int i, int r, int g, int b){
  Pixels.setPixelColor(i, Pixels.Color(r,g,b));
  Pixels.show();
}
