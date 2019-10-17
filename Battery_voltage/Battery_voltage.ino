float Battery_Voltage;
float Battery_Percent;

#define Batt_Full_Voltage 4.20
#define Batt_Flat_Voltage 3.10



double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   Battery_Voltage=0;
   for (int i = 0; i < 20; i++) {Battery_Voltage+=(analogRead(35)/4096.0*7.335);delay(1);}

   if (Battery_Voltage != 0) {Battery_Voltage=Battery_Voltage/20; }
 
   Serial.print("Batterry Voltage:   ");
 Serial.print(Battery_Voltage);
 Battery_Percent= mapf(Battery_Voltage,Batt_Flat_Voltage,Batt_Full_Voltage,0.000,100.000);
   if (Battery_Percent>100) Battery_Percent=100.0;
   if (Battery_Percent<5)Battery_Percent=5;
 Serial.print("v    ");
 Serial.print(Battery_Percent);
  Serial.println("%  ");
 //delay(1000);
}
