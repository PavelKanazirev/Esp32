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

void update_Lcd(bool _isLampStateOn[], float _t, float _h )
{
    lcd.clear();
    lcd.setCursor(0, 0);
    // print message
    lcd.print("Act:");
    for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
    {
        if ( true == _isLampStateOn[EHOMELAMPS_KITCHEN] )
        {
            Serial.println("lcd:K");
            lcd.setCursor(5, 0);
            lcd.print(" K");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_BEDROOM] )
        {
            Serial.println("lcd:B");
            lcd.setCursor(7, 0);
            lcd.print(" B");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_LIVINGROOM] )
        {
            Serial.println("lcd:L");
            lcd.setCursor(9, 0);
            lcd.print(" L");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_CORRIDOR] )
        {
            Serial.println("lcd:C");
            lcd.setCursor(11, 0);
            lcd.print(" C");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_ALARM_ACTIVE] )
        {
            Serial.println("lcd:C");
            lcd.setCursor(13, 0);
            lcd.print(" A");
        }
        if ( true == _isLampStateOn[EHOMELAMPS_ALARM_TRIGGERED] )
        {
            Serial.println("lcd:C");
            lcd.setCursor(15, 0);
            lcd.print(" T");
        }                
    }    
    // set cursor to first column, second row
    lcd.setCursor(0,1);
    lcd.print("T:");
    Serial.print("lcd:T");
    String strTemp = String(_t);
    Serial.println(strTemp);
    lcd.print(strTemp);
    lcd.print(" ");

    lcd.print("H:");
    Serial.print("lcd:H");
    String strHumid = String(_h);
    Serial.println(strHumid);
    lcd.print(strHumid);
}
