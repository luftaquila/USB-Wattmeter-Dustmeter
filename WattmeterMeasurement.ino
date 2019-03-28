void WattmeterMeasurement()
{
  int led = 0;
    
    // INA219 Variables
    float busVoltage = 0;
    float power = 0;
    
    // Voltmeter Variables
    int analogInput = A7;
    float vout = 0.0;
    float vin = 0.0;
    float R1 = 30000.0;
    float R2 = 7500.0;
    int value = 0;
         
    // INA219 Measurements
    busVoltage = sensor219.getBusVoltage_V();
    current = sensor219.getCurrent_mA();

    if(current <= 0.2)
         current = 0;
    
    power = busVoltage * (current/1000);
    
    // Voltmeter Measurements
    value = analogRead(analogInput);
    vout = (value * 5.0) / 1024.0;
    vin = vout / (R2 / (R1 + R2));
    v = vin-0.2;
    if(v<0)
        v=0;
    
    // mAh Calculation
    float mAh;
    mAh = current * 1/7200;
    mAh_total = mAh + mAh_total;
    
    // Passed Time Calculation
    timer = millis() / 1000 - 15;

    WattmeterOutput();
}
