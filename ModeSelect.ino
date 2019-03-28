int ModeCount = 5;
long time1 = 0;
int ModeButton = 0;

void countdown() // Time Countdown
{ 
  lcd.setCursor(0, 0);
  lcd.print("Mode Select");
  lcd.setCursor(13, 0);
  lcd.print("T:");
  lcd.setCursor(15, 0);
  lcd.print(ModeCount);
  ModeCount--;
}

void ChangeModeState() // Change check mark location
{
  if(state == true)
  {
      lcd.setCursor(2, 1);
      lcd.print(" ");
      lcd.setCursor(8, 1);
      lcd.write(byte(0));
      state = false;
  }

  else if(state == false)
  {
      lcd.setCursor(2, 1);
      lcd.write(byte(0));
      lcd.setCursor(8, 1);
      lcd.print(" ");
      state = true;
  }
}

bool ModeSelect()
{
  countdown();

  lcd.setCursor(3, 1);
  lcd.print("Dust");

  lcd.setCursor(9, 1);
  lcd.print("Power");

  lcd.setCursor(2, 1);
  lcd.write(byte(0));
  
  time1 = millis();
  
  while(ModeCount >= 0)
  {
    ModeButton = digitalRead(sw);
    
    if(ModeButton == LOW) // Change check mark location if switch pressed
      ChangeModeState();
    
    if(time1 + 1000 < millis()) // Wait 1 sec until next countdown
    {
      countdown();
      time1 = millis();
    }
    
    delay(150); // Wait 0.15 sec for prevent wrong press
  }
  
  return state;
}
