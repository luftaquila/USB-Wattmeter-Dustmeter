// Made by Luft Aquila, v1.1.0 Alpha at 2017.05.07 22:19

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 sensor219;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

byte check[8] = {
        B00000,
        B00001,
        B00010,
        B00010,
        B10100,
        B10100,
        B01000,
        B00000
};

byte micro[8] = {
        B00000,
        B10001,
        B10001,
        B11001,
        B10110,
        B10000,
        B10000,
        B00000
};

int sw = 5;
bool state = true;

float v = 0.0;

float mAh_total = 0;
float current = 0;

float density, voltage;
int   adcvalue;
const int iled = 13;
const int aout = 0;
unsigned long int time0;
unsigned long int last_time;
unsigned long int timer = 0;


void setup()
{
  sensor219.begin();
  lcd.begin(16, 2);
  
  lcd.createChar(0, check); // Define character '√' 
  lcd.createChar(1, micro); // Define character 'μ'
  
  pinMode(5, INPUT_PULLUP); // Set pin #5 to switch Input
  pinMode(13, OUTPUT); // Set pin #13 to Board LED Output

  lcd.setCursor(1, 0);
  lcd.print("by Luft Aquila");
  lcd.setCursor(2, 1);
  lcd.print("v1.1.0 alpha");
  delay(3000);
  lcd.clear();

  state = ModeSelect(); // Get mode select's return value
  lcd.clear();
  
  BootScreen();

  if(state == true) // Dustmeter Mode Sensor Check
  {
    lcd.setCursor(0, 1);
    lcd.print("Sensor Check");
    delay(700);
    lcd.print(".");
    delay(700);
    lcd.print(".");
    delay(1300);
    
    getDustValue();
    
    if(density <= 0 || density >= 1000) // Print Error Screen
    {
      lcd.setCursor(0, 0);
      lcd.print("Sensor Failure!!");
      lcd.setCursor(0, 1);
      lcd.print("Chk Sensor State");
      delay(1000000);
    }
    
    else
    {
      lcd.print("OK");
      delay(1500);
      lcd.clear();
    }
  }
  
  else if(state == false) // Wattmeter Mode Sensor Check
  {    
    lcd.setCursor(0, 1);
    lcd.print("Sensor Check");
    delay(700);
    lcd.print(".");
    delay(700);
    lcd.print(".");
    delay(1300);
    lcd.print("OK");
    delay(1500);
    lcd.clear();
    
    
    // Setting LCD Layout
    lcd.setCursor(5, 0);
    lcd.print("V");
    
    lcd.setCursor(14, 0);
    lcd.print("mA");
    
    lcd.setCursor(13, 1);
    lcd.print("mAh");
    
    lcd.setCursor(5, 1);
    lcd.print("s");

    
    last_time = millis();
    WattmeterMeasurement();
  }
}

void loop()
{
  if(state == true)
    DustmeterLoop();
  
  if(state == false)
    WattmeterLoop();
}
