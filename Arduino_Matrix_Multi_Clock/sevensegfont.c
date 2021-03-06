
#include <Arduino.h>
#include <avr/pgmspace.h>

const unsigned int sevensegfont[][16] PROGMEM ={
  {62,93,99,99,99,65,0,0,65,99,99,99,93,62,0,0},       //0
  {0,64,96,96,96,64,0,0,64,96,96,96,64,0,0,0},       //1
  {62,92,96,96,96,64,62,62,1,3,3,3,29,62,0,0},       //2
  {62,92,96,96,96,64,62,62,64,96,96,96,92,62,0,0},       //3
  {0,65,99,99,99,65,62,62,64,96,96,96,64,0,0,0},       //4
  {62,29,3,3,3,1,62,62,64,96,96,96,92,62,0,0},       //5
  {62,29,3,3,3,1,62,62,65,99,99,99,93,62,0,0},       //6
  {62,92,96,96,96,64,0,0,64,96,96,96,64,0,0,0},       //7
  {62,93,99,99,99,65,62,62,65,99,99,99,93,62,0,0},       //8
  {62,93,99,99,99,65,62,62,64,96,96,96,92,62,0,0},       //9
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},       //blank

};
