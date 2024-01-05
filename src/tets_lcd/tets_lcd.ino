#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 
void setup()
{
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("VT: 1 2 3 4 5 6");
  lcd.setCursor(4,1);
  lcd.print("x x 0 x x x");
}
void loop()
{
}
