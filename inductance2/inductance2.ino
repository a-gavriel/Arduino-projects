// Originally by reibot.org, modified by soundation.ch
 
// reworked by Salvatore Carotenuto (ultimoistante)
// of StartupSolutions (www.startupsolutions.it | ultimoistante.wordpress.com)
 
// 16x1 LCD circuit connections:
// LCD pin 4 (RS) to digital pin 12
// LCD pin 6 (Enable) to digital pin 11
// LCD pin 11 (DB4) to digital pin 5
// LCD pin 12 (DB5) to digital pin 4
// LCD pin 13 (DB6) to digital pin 3
// LCD pin 14 (DB7) to digital pin 2
// LCD pin 5 (R/W) to ground
// LCD pin 3 (contrast adjust) to ground
// LCD pin 2 (Vdd) to +5V
// LCD pin 1 (Vss) to ground
 
// library to drive the 16x1 LCD display
//#include <LiquidCrystal.h>
 
// initialize the LCD library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
// variables used for calculations
double pulse, frequency, capacitance, inductance;
 
void setup()
   {
   // pin 13 is the input to the circuit (connects to 150ohm resistor),
   // pin 10 is the comparator/op-amp output.
   // visit reibot.org for guide
   pinMode(13, OUTPUT);
   pinMode(10, INPUT);
 
   // --- Capacitor exact value setting ---
   // Use a multimeter to measure the exact value of capacitor for more accurate readings.
   // My capacitor is 1.021 uF, so the value (in Farads) is 0.000001021
   // Note: an ideal 1uF capacitor will be equal to 1.E-6 (0.000001)
   capacitance = 2.E-9;
   //capacitance = 0.000001021;
 
   // set up the LCD's number of columns and rows
   // NOTE: the 16x1 display is treated as an 8x2
   //lcd.begin(8, 2);
 
   delay(200);
 
   // starts serial communication, just for debugging purpose
   Serial.begin(9600);
   }
 
void loop()
   {
   // does a pulse on pin 13
   digitalWrite(13, HIGH);
   delay(5); //give some time to charge inductor.
   digitalWrite(13, LOW);
   delayMicroseconds(100);
 
   // reads the pulse duration, in microseconds, on pin 10 (comparator/op-amp output)
   pulse = pulseIn(10, HIGH, 5000);
 
   // debug
   Serial.print("pulse: ");
   Serial.println(pulse);
 
   //lcd.clear();
 
   if(pulse > 0.1)
      {
      frequency = 1.E6 / (2 * pulse);
      inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159);
      inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6
 
      // writes read value on the LCD display
      Serial.print("L value:");
      //lcd.setCursor(0, 1);
      if(inductance >= 1000)
         {
         Serial.print ((inductance/1000)-0.5);
         Serial.print ("mH");
         }
      else
         {
         Serial.print (inductance + 10);
         Serial.print ("uH");
         }
      }
   else if(pulse < 0.1)
      {
      //lcd.print("Insert i");
     // lcd.setCursor(0, 1);
     // lcd.print("nductor");
      }
   delay(300);
   }
