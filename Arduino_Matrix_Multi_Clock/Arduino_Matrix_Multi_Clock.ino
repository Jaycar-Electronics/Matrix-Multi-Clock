//Libraries for Dot Matrix
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
DMD dmd(1, 1);

//Libraries for RTC Module
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

//font data
#include "font0816.c"
#include "images.c"
#include "sevensegfont.c"
#include "font0608.c"

#define SPEAKERPIN 4
#define BUTTON1PIN 2
#define BUTTON2PIN 3

char daysofweek[]="SUNMONTUEWEDTHUFRISAT";

byte handx[]={12,13,14,15,16,17,18,19,20,21,21,22,
  22,23,23,23,23,23,22,22,21,21,20,19,
  18,17,16,15,14,13,12,10,9,8,7,6,
  5,4,3,2,2,1,1,0,0,0,0,0,
  1,1,2,2,3,4,5,6,7,8,9,10};

byte handy[]={0,0,0,0,1,1,1,2,2,3,4,4,
  5,6,7,8,8,9,10,11,11,12,13,13,
  14,14,14,15,15,15,15,15,15,15,14,14,
  14,13,13,12,11,11,10,9,8,8,7,6,
  5,4,4,3,2,2,1,1,1,0,0,0};

int dmode=0;    //display mode
int brightness=2;   //display brightness
int bcount=0;   //variable used to keep track of pwm phase
#define BSTEPS 7

void ScanDMD(){       //also implements a basic pwm brightness control
  dmd.scanDisplayBySPI();
  bcount=bcount+brightness;
  if(bcount<BSTEPS){digitalWrite(9,LOW);}
  bcount=bcount%BSTEPS;
}

void setup(){
  Timer1.initialize( 500 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  dmd.clearScreen( true );     //clear/init the DMD pixels held in RAM
  pinMode(BUTTON1PIN,INPUT_PULLUP);
  pinMode(BUTTON2PIN,INPUT_PULLUP);
  pinMode(SPEAKERPIN,OUTPUT);
  digitalWrite(SPEAKERPIN,LOW);    //speaker off
  rtc.begin();
}

void loop(){
  if(!digitalRead(BUTTON1PIN)){dmode=(dmode+1)%6;dmd.clearScreen(true);delay(500);}    //next mode, clear all pixels in case mode doesn't, wait a bit to debounce
  switch(dmode){
    case 0: timeanddate();break;
    case 1: bigdigital();break;
    case 2: analogclock();break;
    case 3: bigsevenseg();break;
    case 4: wordclock();break;
    case 5: binaryclock();break;
  }  
  delay(200);
}

void font0816char(int cx,int cy,char c){
  for(int y=0;y<16;y++){
    int d=pgm_read_word(&font0816[c][y]);
    for(int x=0;x<8;x++){
      if(d&(1<<x)){
        dmd.writePixel(cx+x,cy+y,GRAPHICS_NORMAL,1);
      }else{
        dmd.writePixel(cx+x,cy+y,GRAPHICS_NORMAL,0);
      }
    }
  }
}

void sevensegfontchar(int cx,int cy,char c){
  for(int y=0;y<16;y++){
    int d=pgm_read_word(&sevensegfont[c][y]);
    for(int x=0;x<8;x++){
      if(d&(1<<x)){
        dmd.writePixel(cx+x,cy+y,GRAPHICS_NORMAL,1);
      }else{
        dmd.writePixel(cx+x,cy+y,GRAPHICS_NORMAL,0);
      }
    }
  }
}

void bigdigital(){
  DateTime now = rtc.now();
  int h,m,s;
  h=now.hour();
  m=now.minute();
  s=now.second();

  if(h>9){     //leading zero blank
    font0816char(0,1,(h/10));
  }else{
    font0816char(0,1,10);
  }
  font0816char(8,1,(h%10));
  font0816char(17,1,(m/10));
  font0816char(25,1,(m%10));
}

void bigsevenseg(){
  DateTime now = rtc.now();
  int h,m,s;
  h=now.hour();
  m=now.minute();
  s=now.second();

  if(h>9){     //leading zero blank
    sevensegfontchar(0,1,(h/10));
  }else{
    sevensegfontchar(0,1,10);
  }
  sevensegfontchar(8,1,(h%10));
  sevensegfontchar(17,1,(m/10));
  sevensegfontchar(25,1,(m%10));
}

void analogclock(){
  static int oldh=0,oldm=0,olds=0;    //keep track of what's been displayed to erase later
  int h,m,s;
  DateTime now = rtc.now();
  s=now.second()%60;
  m=now.minute()%60;
  h=(now.hour()%12)*5+(m/12);     //translated to 60th's of a circle
  //erase any hands that have moved
  if(olds!=s){dmd.writePixel(handx[olds]+4,handy[olds],GRAPHICS_NORMAL,0);}   //dot for second hand
  if(oldm!=m){    //line for minute handle
    int x,y,n;
    x=handx[oldm]-12;
    y=handy[oldm]-8;
    n=max(abs(x),abs(y));
    for(int i=0;i<n;i++){
      dmd.writePixel(12+(x*i)/n+4,8+(y*i)/n,GRAPHICS_NORMAL,0);
    }
  }
  if(oldh!=h){    //small circle for hour hand
    int x,y;
    x=(((handx[oldh]-12)*2)/3)+12;
    y=(((handy[oldh]-8)*2)/3)+8;
    dmd.writePixel(4+x,y-1,GRAPHICS_NORMAL,0);
    dmd.writePixel(4+x+1,y,GRAPHICS_NORMAL,0);  
    dmd.writePixel(4+x-1,y,GRAPHICS_NORMAL,0);  
    dmd.writePixel(4+x,y+1,GRAPHICS_NORMAL,0);      
  }
  //draw all hands
  dmd.writePixel(handx[s]+4,handy[s],GRAPHICS_NORMAL,1);    //dot for seocnd hand
  int x,y,n;
  x=handx[m]-12;      //line for minute hand
  y=handy[m]-8;
  n=max(abs(x),abs(y));
  for(int i=0;i<n;i++){dmd.writePixel(12+(x*i)/n+4,8+(y*i)/n,GRAPHICS_NORMAL,1);}
  x=(((handx[h]-12)*2)/3)+12;     //small circle for hour hand
  y=(((handy[h]-8)*2)/3)+8;
  dmd.writePixel(4+x,y-1,GRAPHICS_NORMAL,1);
  dmd.writePixel(4+x+1,y,GRAPHICS_NORMAL,1);  
  dmd.writePixel(4+x-1,y,GRAPHICS_NORMAL,1);  
  dmd.writePixel(4+x,y+1,GRAPHICS_NORMAL,1);  
  for(int i=0;i<60;i=i+5){dmd.writePixel(4+handx[i],handy[i],GRAPHICS_NORMAL,1);}        //draw hour marks every five minutes
  
  olds=s;     //update currently drawn hands
  oldm=m;
  oldh=h;
}

void wordclock(){
  DateTime now = rtc.now();
  int h,m,s;
  int d=0;    //variable for offset if on the hour (showing hour at top and o'clock at bottom)
  h=now.hour();
  m=now.minute()%60;
  s=now.second()%60;
  m=m/5;    //round to 5 minute multiple
  if(m>6){h=h+1;}   //after half past hour, show next hour
  h=h%12;   //mod to 12 hours
  if(m==0){d=8;}
  for(int x=0;x<32;x++){
    int t=pgm_read_word(&topline[m][x]);
    int b=pgm_read_word(&bottomline[h][x]);
    for(int y=0;y<8;y++){                   //draw top line image
      if((1<<y)&t){
        dmd.writePixel(x,y+d,GRAPHICS_NORMAL,1);
      }else{
        dmd.writePixel(x,y+d,GRAPHICS_NORMAL,0);
      }
      if((1<<y)&b){                   //draw bottom line image
        dmd.writePixel(x,y+8-d,GRAPHICS_NORMAL,1);
      }else{
        dmd.writePixel(x,y+8-d,GRAPHICS_NORMAL,0);
      }
    }
  }  
}

void binaryclock(){
  DateTime now = rtc.now();
  int h,m,s;
  h=now.hour()%24;
  m=now.minute()%60;
  s=now.second()%60;

  for(int b=0;b<6;b++){   //scan bits from right to left
    if((1<<b)&h){
      fillrect(26-b*5,1,29-b*5,4,1);  
    }else{
      fillrect(26-b*5,1,29-b*5,4,0);  
    }
    if((1<<b)&m){
      fillrect(26-b*5,6,29-b*5,9,1);  
    }else{
      fillrect(26-b*5,6,29-b*5,9,0);  
    }
    if((1<<b)&s){
      fillrect(26-b*5,11,29-b*5,14,1);  
    }else{
      fillrect(26-b*5,11,29-b*5,14,0);  
    }
  }
}

void fillrect(int x1,int y1,int x2,int y2, int c){
  for(int x=x1;x<x2+1;x++){
    for(int y=y1;y<y2+1;y++){
      dmd.writePixel(x,y,GRAPHICS_NORMAL,c);
    }
  }
}

void timeanddate(){
  DateTime now = rtc.now();
  int h,m,da,dt;
  h=now.hour()%24;
  m=now.minute()%60;
  da=now.dayOfTheWeek()%7;
  dt=now.day()%100;
  if(h<10){
    showchar(4,0,' ');
  }else{
    showchar(4,0,h/10+'0');
  }
  showchar(10,0,h%10+'0');      //hours
  showchar(17,0,m/10+'0');
  showchar(23,0,m%10+'0');      //minutes
  showchar(0,9,daysofweek[da*3]);    //3 letter day of the week
  showchar(6,9,daysofweek[da*3+1]);
  showchar(12,9,daysofweek[da*3+2]);
  showchar(20,9,dt/10+'0');
  showchar(26,9,dt%10+'0');
}

void showchar(int cx,int cy, char c){
  if(c<32){c=32;}
  if(c>127){c=32;}
  c=c-32;
  for(int x=1;x<7;x++){
    for(int y=0;y<8;y++){
      if(pgm_read_byte(&font0608[c][x])&(1<<y)){
      dmd.writePixel(x+cx-1,y+cy,GRAPHICS_NORMAL,1);
      }else{
      dmd.writePixel(x+cx-1,y+cy,GRAPHICS_NORMAL,0);        
      }      
    }
  }
}

