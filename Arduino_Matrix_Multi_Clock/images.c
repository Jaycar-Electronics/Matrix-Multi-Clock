
#include <Arduino.h>
#include <avr/pgmspace.h>

//top line aka minutes display
const byte topline[][32] PROGMEM ={  
  {124,254,130,254,124,0,6,0,124,254,130,130,0,254,254,128,128,124,254,130,254,124,0,124,254,130,130,0,254,254,108,198},   //o'clock
  //{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},   //blank
  {127,9,9,0,127,0,31,96,31,0,127,73,65,0,0,0,0,127,9,6,0,126,17,126,0,70,73,49,0,1,127,1},   //five past
  {1,127,1,0,127,73,73,0,127,2,4,127,0,0,0,0,127,9,6,0,126,17,126,0,70,73,49,0,1,127,1,0},   //ten past
  {0,0,2,95,32,16,40,52,42,125,32,0,0,0,0,127,9,6,0,126,17,126,0,70,73,49,0,1,127,1,0,0},   //1/4 past
  {1,1,15,1,1,0,7,8,6,248,87,80,47,11,233,80,95,226,4,175,176,81,1,31,241,17,0,1,2,12,2,1},   // twenty past
  {119,8,8,119,0,119,8,8,119,0,31,96,96,31,0,0,0,127,9,6,0,126,17,126,0,70,73,49,0,1,127,1},   //XXV past
  {127,8,127,0,126,17,126,0,127,64,0,127,9,1,0,0,0,127,9,6,0,126,17,126,0,70,73,49,0,1,127,1},   //half past
  {0,0,0,0,66,99,113,89,79,70,0,0,79,73,73,73,121,49,0,0,0,0,66,99,113,89,79,70,0,0,0,0},   // 25 2
  {1,127,1,63,64,56,64,63,0,127,73,65,0,127,1,126,1,127,1,0,15,112,15,0,0,0,1,127,1,62,65,62},   //twenty to
  {62,65,126,0,127,64,127,0,126,17,126,0,127,17,110,1,127,1,127,73,65,0,127,17,110,0,1,127,1,62,65,62},   //quarter to
  {1,1,127,1,1,0,127,73,73,73,65,0,127,2,4,8,127,0,0,0,0,1,1,127,1,1,0,62,65,65,65,62},   // ten to
  {0,0,0,0,127,9,9,0,127,0,31,96,31,0,127,73,65,0,0,0,1,127,1,0,62,65,62,0,0,0,0,0}   //five to
};

//bottom line aka hours
const byte bottomline[][32] PROGMEM ={  
  //12 is first because 12%12=0
  {1,1,255,1,1,0,127,128,112,128,127,0,255,137,137,129,0,255,128,128,128,15,48,192,48,15,0,255,137,137,129,0},   //twelve
  {0,0,0,0,0,126,255,129,129,255,126,0,0,255,255,12,24,255,255,0,0,255,255,137,137,137,129,0,0,0,0,0},   //one
  {0,0,0,0,0,1,1,255,255,1,1,0,0,255,255,64,62,64,255,255,0,0,126,255,129,129,255,126,0,0,0,0},   //two
  {1,1,255,255,1,1,0,255,255,8,8,255,255,0,255,255,17,49,255,206,0,255,255,137,137,129,0,255,255,137,137,129},   //three
  {0,0,255,255,17,17,17,1,0,126,255,129,129,255,126,0,127,255,128,128,255,127,0,255,255,17,49,255,206,0,0,0},   //four
  {0,0,0,255,255,17,17,17,1,0,129,255,255,129,0,63,127,192,192,127,63,0,255,255,137,137,137,129,0,0,0,0},   //five
  {0,0,0,0,0,0,0,70,207,137,145,243,98,0,129,255,255,129,0,0,231,255,24,24,255,231,0,0,0,0,0,0},   //six
  {70,207,137,145,243,98,0,255,255,137,137,129,0,63,127,192,192,127,63,0,255,255,137,137,129,0,255,255,12,24,255,255},   //seven
  {255,255,137,137,137,129,0,129,255,255,129,0,126,255,129,145,241,241,0,255,255,8,8,255,255,0,1,1,255,255,1,1},   //eight
  {0,0,0,255,255,12,24,255,255,0,129,255,255,129,0,255,255,12,24,255,255,0,255,255,137,137,137,129,0,0,0,0},   //nine
  {0,0,0,0,0,1,1,255,255,1,1,0,0,255,255,137,137,137,129,0,0,255,255,12,24,255,255,0,0,0,0,0},   //ten
  {255,137,137,129,0,255,128,128,128,0,255,137,137,129,0,15,48,192,48,15,0,255,137,137,129,0,255,2,4,8,255,0},   //eleven
  {1,1,255,1,1,0,127,128,112,128,127,0,255,137,137,129,0,255,128,128,128,15,48,192,48,15,0,255,137,137,129,0}   //twelve
};

