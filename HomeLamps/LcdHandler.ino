#include <LiquidCrystal_I2C.h>

const int lcd_id_scanned = 0x27;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(lcd_id_scanned, lcdColumns, lcdRows); 

void init_Lcd()
{
    // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void update_Lcd(bool _isLampStateOn[] )
{
    lcd.clear();
    lcd.setCursor(0, 0);
    // print message
    lcd.print("Active:");
    for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
    {
        if ( true == _isLampStateOn[EHOMELAMPS_KITCHEN] )
        {
            Serial.println("lcd:K");
            lcd.setCursor(8, 0);
            lcd.print(" K");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_BEDROOM] )
        {
            Serial.println("lcd:B");
            lcd.setCursor(10, 0);
            lcd.print(" B");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_LIVINGROOM] )
        {
            Serial.println("lcd:L");
            lcd.setCursor(12, 0);
            lcd.print(" L");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_CORRIDOR] )
        {
            Serial.println("lcd:C");
            lcd.setCursor(14, 0);
            lcd.print(" C");
        }        
    }    
    // set cursor to first column, second row
    lcd.setCursor(0,1);
    lcd.print("Alarm:");
    
    if (true == _isLampStateOn[EHOMELAMPS_ALARM_TRIGGERED] )
    {
      Serial.println("lcd:T");
      lcd.print("Triggered");
    }
    else if ( true == _isLampStateOn[EHOMELAMPS_ALARM_ACTIVE] )
    {
      Serial.println("lcd:A");
      lcd.print("Active");
    }
}
