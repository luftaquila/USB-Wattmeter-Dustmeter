void WattmeterLoop()
{
    unsigned long int ResetTimer;
    
    // Print to LCD every 0.5 sec
    time0 = millis();
    if(time0 - last_time >= 500)
    {
      WattmeterMeasurement();
      last_time = time0;
    }

    if(digitalRead(sw)==LOW)
    {
      ResetTimer = millis();
      mAh_total = 0;
    }
        
}
