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
    lcd.setCursor(0, 0);
    // print message
    lcd.print("Active : ");
    for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
    {
        if ( true == _isLampStateOn[index] )
        {
            switch (index) {
/*              
 *                 EHOMELAMPS_KITCHEN = EHOMELAMPS_MIN,
  EHOMELAMPS_BEDROOM,
  EHOMELAMPS_LIVINGROOM,
  EHOMELAMPS_CORRIDOR,
  EHOMELAMPS_ALARM_ACTIVE,
  EHOMELAMPS_ALARM_TRIGGERED,
 */
              case EHOMELAMPS_KITCHEN:
                break;
              default:
                lcd.print("Error");
            }
          
        }
    }    
    // set cursor to first column, second row
    lcd.setCursor(0,1);
    lcd.print("Alarm:");
    

    if ( true == _isLampStateOn[EHOMELAMPS_ALARM_ACTIVE] )
    {
      lcd.print("Active");
    }

    if (true == _isLampStateOn[EHOMELAMPS_ALARM_TRIGGERED] )
    {
      lcd.print("Trig");
    }


}
