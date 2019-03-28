// Dust Sensor Variables
#define COV_RATIO 0.2            //ug/mmm / mv
#define NO_DUST_VOLTAGE 400            //mv
#define SYS_VOLTAGE 5000           


// Setting Filter
int Filter(int m)
{
  static int flag_first = 0, _buff[10], sum;
  const int _buff_max = 10;
  int i;
  
  if(flag_first == 0)
  {
    flag_first = 1;

    for(i = 0, sum = 0; i < _buff_max; i++)
    {
      _buff[i] = m;
      sum += _buff[i];
    }
    return m;
  }
  else
  {
    sum -= _buff[0];
    for(i = 0; i < (_buff_max - 1); i++)
    {
      _buff[i] = _buff[i + 1];
    }
    _buff[9] = m;
    sum += _buff[9];
    
    i = sum / 10.0;
    return i;
  }
}

void getDustValue()
{
   // Dust Concentration Measurement
  digitalWrite(iled, HIGH);
  delayMicroseconds(280);
  adcvalue = analogRead(aout);
  digitalWrite(iled, LOW);
  
  adcvalue = Filter(adcvalue);
    voltage = (SYS_VOLTAGE / 1024.0) * adcvalue * 11;
    if(voltage >= NO_DUST_VOLTAGE)
  {
    voltage -= NO_DUST_VOLTAGE;
    density = voltage * COV_RATIO;
  }
  else
    density = 0;
}

void DustmeterLoop()
{  
  getDustValue();

  // Setting LCD Layout
  lcd.setCursor(0, 0);
  lcd.print("D. Concentration : ");
  lcd.setCursor(8, 1);
  lcd.write(byte(1));
  lcd.print("g/m^3");


  // Print Value
  lcd.setCursor(1, 1);
  
  if(density <= 0 || density >= 1000) // Print Error Screen
  {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Failure!!");
    lcd.setCursor(0, 1);
    lcd.print("Chk Sensor State");
    delay(1000000);
  }
  
  else if(density > 0  && density < 10)
  {
    lcd.print("  ");
    lcd.print(density);    
  }
  
  else if(density >= 10 && density < 100)
  {
    lcd.print(" ");
    lcd.print(density);
  }
  
  else if(density >= 100 && density <1000)
  {
    lcd.print(density);
  }
  
  delay(1000); // Wait 1 sec until next measurement
}
