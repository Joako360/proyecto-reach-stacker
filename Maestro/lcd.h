#ifndef LCD_H
#define LCD_H
  #define RS 19
  #define EN 18
  #define D4 11
  #define D5 12
  #define D6 13
  #define D7 17
  #include <Arduino.h>
  #include <LiquidCrystal.h>
  extern LiquidCrystal lcd;
  extern char line0[16], line1[16];
  void setupLCD();
  void updateLCD();
#endif // LCD_H
