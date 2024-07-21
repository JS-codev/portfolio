//This entire code includes Serial monitor display as well as LCD RGB backlight-Display.
//It also includes temp sensor, LED, ultrasonic sensor, buzzer and button.

#include <math.h>
#include "Ultrasonic.h" 
#include <Wire.h>               //Communicate with I2C devices 
#include "rgb_lcd.h"            //Include the RGB_LCD.
rgb_lcd lcd;                    //LCD is connected to 12C. 
const int k = 0;                //k value is set to 0
const int B = 4275;             // B value of the thermistor
const int R0 = 100000;          // R0 = 100k
const int pinTempSensor = A0;   // Temp sensor connected to A0
const int buttonPin = 2;        //Button is connected to Pin 2
const int led = 4;              //LED is connected to Pin 4
const int buzzer = 3;           //Buzzer is connected to Pin 3
Ultrasonic ultrasonic(7);       //Ultrasonic sensor is connected to pin 7
int buttonState = 0;
int previousState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(buttonPin, INPUT);
    pinMode(led, OUTPUT);
    lcd.begin(16,2);             //Uses the entire of the LCD screen. 
    lcd.setCursor(0,0);          //Set cursor to top left conner of the screen. 
    lcd.print("Press button to");
    lcd.setCursor(0,1);          //Set cursor to bottom left conner of the screen. 
    lcd.print("turn on system");
    Serial.print("Press button to turn on the system");
}


void loop()
{
    long h=0;
    buttonState = digitalRead(buttonPin);    //Read the button input. 
    lcd.display();                           //ON Display the LCD.
    if (buttonState==HIGH) {                 //CHECKS IF BUTTON IS PRESSED
      buttonState=0;  
      lcd.clear();                           //Clears all written things on the LCD.
      while (previousState == 0) {
      long RangeInCentimeters;
      RangeInCentimeters = ultrasonic.MeasureInCentimeters();    //Measure the length of the LCD.
      h = RangeInCentimeters - 5;
      long percentage = 100 - (100/25 * h);  //Calculated the percentage for ultrasonic measuring the coolent level. For ultrasonic sensor(Distance decrease = water % lvl increase):  30cm=0%, and 5cm=100%.
      
      int a = analogRead(pinTempSensor);    //Temperature sensor
      float R = 1023.0/a-1.0;
      R = R0*R;
      float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15+(k);
      Serial.print("\nTemperature(°C)=");
      Serial.println(temperature );
      Serial.print("<");
      Serial.print(RangeInCentimeters);
      Serial.print("cm>");
      Serial.print("The coolant level is at ");  //30cm = 10%
      Serial.print(percentage);//0~30cm
      Serial.print("%");

      //LCD coding
      lcd.clear();
      lcd.setCursor(0,0);           //Shows display for 1st horizontal row.
      lcd.print("Coolant lvl:");
      lcd.print(percentage);
      lcd.print("%");
      lcd.setCursor(0,1);           //Shows display for 2nd horizontal row.
      lcd.print("Temp(C):");        //in degree celsius
      lcd.print(temperature);
      
      delay(1000);
      if (temperature > 28) {        //RED LED TURN ON IF TEMP IS OVER 28°C 
        digitalWrite(led, HIGH);
      }
      if (percentage > 30)  //If coolant level is ABOVE 30%, Buzzeer turned ON. 
{
        Serial.print("\nBuzzer turned ON due to coolant lvl above 30%");
        lcd.setCursor(16,0);                    //Sets the cursor 16 blocks from the top left of the screen.
        lcd.print("(Alarm alert Online)");
        digitalWrite(buzzer, HIGH);
        for (int positionCounter = 0; positionCounter <40; positionCounter++) {
          lcd.scrollDisplayLeft();        //LCD scrolling to the left side.
          delay(80);                      //shorter delay for lcd to scroll
        }
        delay(100);                     //delay for the buzzer to buzz a little more. 
        digitalWrite(buzzer, LOW);

        
  }
      buttonState = digitalRead(buttonPin);
      if (buttonState==HIGH) {       //Setting up the "breaking out of while loop" if the button is pressed again...
        previousState=1;
       }
 
      delay(500);
}

      if (buttonState == 1) {        //If the button is pressed after it is turn on, it will access to this code. 
      lcd.clear();                   //Clear all written things on the LCD.
      lcd.print("System Offline");   //LCD prints "System offline" which uses a total of 14 blocks 
      Serial.println("\n");          //Produce an enmpty line. 
      Serial.println("The System is Offline");      //LCD, LED and alarm are offline.
      Serial.println("\n");
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);      
      previousState=0;
 }
    }
delay(500);
}
