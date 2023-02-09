
#include "lcd.h"
LiquidCrystal lcd = LiquidCrystal(RS, EN, D4, D5, D6, D7);
char line0[16], linea[16];
void setupLCD(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
}
void updateLCD() {
   lcd.setCursor(0,0);
   lcd.print(line0);
	 lcd.setCursor(0,1);
   lcd.print(line1);
}
// void LCDrutina(float datos[4], int dt, byte hayEmergencia){
  // unsigned long millisPrevio = 0;
  // unsigned long millisActual = millis()
  // if (millisActual - millisPrevio >= dt) {

    // millisPrevio = millisActual;
		// lcd.clear();
    // lcd.setCursor(0,0);
    // if (!codEmergencia){
			// lcd.print("x:");
      // lcd.print(datos[0]);
      // lcd.setCursor(8,0);
      // lcd.print("l:");
      // lcd.print(datos[1]);
		// }
    // else lcd.print("***EMERGENCIA***");
    // lcd.setCursor(0,1);
    // lcd.print("y:");
    // lcd.print(datos[2]);
    // lcd.setCursor(8,1);
    // lcd.print("ps:");
    // lcd.print(datos[3]);
  // }
// }