void WattmeterOutput()
{
    // Print Passed Time
    lcd.setCursor(1, 1);
    if(timer >= 0 && timer < 10)
    {
      lcd.print("   ");
      lcd.print(timer);
    }

    else if(timer >= 10 && timer < 100)
    {
      lcd.print("  ");
      lcd.print(timer);
    }

    else if(timer >= 100 && timer < 1000)
    {
      lcd.print(" ");
      lcd.print(timer);
    }

    else if(timer >= 1000 && timer < 10000)
      lcd.print(timer);

    else
      lcd.print("Err.");

    // Print Voltage
    lcd.setCursor(1, 0);
    lcd.print(v, 2);

    // Print Current
    lcd.setCursor(8, 0);
    if(current >= 0 && current < 10)
    {
      lcd.print("   ");
      lcd.print(current, 1);
    }

    else if(current >= 10 && current < 100)
    {
      lcd.print("  ");
      lcd.print(current, 1);
    }

    else if(current >= 100 && current < 1000)
    {
      lcd.print(" ");
      lcd.print(current, 1);
    }
    
    else if(current >= 1000 && current < 10000)
      lcd.print(current, 1);

    else
      lcd.print("  Err.");


    // Print mAh
    lcd.setCursor(7, 1);
    if(mAh_total >= 0.0 && mAh_total < 10.0)
    {
      lcd.print("   ");
      lcd.print(mAh_total, 1);
    }

    else if(mAh_total >= 10.0 && mAh_total < 100.0)
    {
      lcd.print("  ");
      lcd.print(mAh_total, 1);
    }

    else if(mAh_total >= 100.0 && mAh_total < 1000.0)
    {
      lcd.print(" ");
      lcd.print(mAh_total, 1);      
    }

    else if(mAh_total >= 1000.0 && mAh_total < 10000.0)
    {
      lcd.print("  ");
      lcd.print(mAh_total, 0);
    }

    else if(mAh_total >= 10000.0 && mAh_total < 100000.0)
    {
      lcd.print(" ");
      lcd.print(mAh_total, 0);
    }

    else if(mAh_total >= 100000.0 && mAh_total < 1000000.0)
      lcd.print(mAh_total, 0);

    else
      lcd.print("  Err.");
}
