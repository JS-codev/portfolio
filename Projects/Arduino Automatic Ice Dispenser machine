//Autmatic Ice Dispenser machine code:
//Includes servo motor,RGB backlight sensor,temp sensor,LED,ultrasonic sensor,buzzer and button.
//Servo to turn gear to allow ice to dispense
//Temperature to sense over heated (40 degree or above)
//Initial continuous rotation servo position is at 90 (not 0).
//Ultrasonic sensor to sense cup placed
//If user place empty cup that is 25cm-30cm from above ultraonsic sensor, the servo will turn to dispense ice.
//Blue LED lights up whenever the dispenser dispense ICE cubes. Blue LED lights down whenever the Machine stops dispensing ICE Cubes.
//Additonal buttion to off buzzer in case buzzer did not stop automatically (See line 100 - 103)
//Skiped serial monitor codes for aurdino to process main code faster (see lines 33, 44, 68 - 75, 109, 124, 148 - 150)

#include <Servo.h>
#include <math.h>
#include "Ultrasonic.h"        
#include <Wire.h>                
#include "rgb_lcd.h" //Include the RGB_LCD.
rgb_lcd lcd; //LCD is connected to 12C.
const int B = 4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Temp sensor connected to A0
const int buttonPin = 2; //Button is connected to Pin 2 (For power switch)
const int led = 4; //LED is connected to Pin 4
const int buzzer = 3; //Buzzer is connected to Pin 3
Ultrasonic ultrasonic(7); //Ultrasonic sensor is connected to pin 7
const int k = 0;
int buttonState = 0;
int previousState = 0;
Servo myservo1; //Created 1st servo object
int pos = 0; //servo position is set to inital state
const int TouchPin = 8; //TouchPin connected to pin 8 (For buzzer additonal button)
int buzzercheck = 0;

void setup()
{
    Serial.begin(9600); //Serial monitor is starting...
    myservo1.attach(5); //Servo motor is connected to pin 5 (Parallax)
    pinMode(TouchPin, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(buttonPin, INPUT);
    pinMode(led, OUTPUT);
    lcd.begin(16,2); //LCD is starting...
    lcd.setCursor(0,0);          
    lcd.print("Press button to"); //Display message on LCD.
    lcd.setCursor(0,1);
    lcd.print("turn on system");
    Serial.print("Press button to turn on the system"); //Display message on serial monitor
    myservo1.writeMicroseconds(1500);  //Set the inital postition of the continuous rotation servo
}

void loop()
{
    long h=0;
    myservo1.detach(); //stops the continuous rotation servo or else it will run continuously non-stop
    buttonState = digitalRead(buttonPin); //Reads the button input
    lcd.display();
    if (buttonState==HIGH) { //check if button is pressed    
      digitalWrite(led, HIGH); //Green LED on if button is pressed
      buttonState=0;  
      lcd.clear();
      while (previousState == 0) {    
      long RangeInCentimeters;
      RangeInCentimeters = ultrasonic.MeasureInCentimeters();
      h = RangeInCentimeters - 5;
      long percentage = 100 - (100/25 * h); //Ultrasonic sensor: 30cm=0%, and 5cm=100%.

      int a = analogRead(pinTempSensor); //Temperature sensor
      float R = 1023.0/a-1.0;
      R = R0*R;
      float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15+(k);

      Serial.print("\nTemperature(°C)=");  //Display temp, distance and percentage on serial monitor
      Serial.println(temperature );
      Serial.print("<");
      Serial.print(RangeInCentimeters);
      Serial.print("cm>");
      Serial.print("The IceCube level is at ");  
      Serial.print(percentage);//0~30cm
      Serial.print("%");

      //LCD coding
      lcd.clear();
      lcd.setCursor(0,0); //Shows display for 1st horizontal row.
      lcd.print("IceCube lvl:");
      lcd.print(percentage);
      lcd.print("%");
      lcd.setCursor(0,1);      //Shows display for 2nd horizontal row.
      lcd.print("Temp(C):");   //in degree celsius
      lcd.print(temperature);
     
      delay(1000);
     
      if (temperature > 40) { //Alarm activated if temp is above 40 degrees.
        lcd.setCursor(16,0);
        lcd.print("(Temp is above 40 degree)"); //LCD display warning message
        digitalWrite(buzzer, HIGH); //Alarm is triggered
        for (int positionCounter = 0; positionCounter <40; positionCounter++) {
          lcd.scrollDisplayLeft(); //LCD scrolling to the left side.
          delay(90); //shorter delay for lcd to scroll
        }
        digitalWrite(buzzer, LOW);
      }
     
    buzzercheck = digitalRead(TouchPin);  //If the buzzer is still ongoing after first buzz without stoping, pressing and holding the touchpin will automatically stop the buzzer.
    if (buzzercheck == HIGH){
        digitalWrite(buzzer, LOW);
    }

      //If the ultrasonic sense cup is placed and the cup empty, the servo opens the dispenser.
      //30cm(0%)= Cup is empty. 5cm(100%)= Cup is full.
      if (percentage < 55 and percentage >0) { //60% = 12.5cm (Ice cube level in cup is near empty) 
        Serial.print("\nCup detected. Opening dispenser..."); //This will keep on dispensering until it reaches 90-100% of cup filled (7.5cm water/ice cubes from sensor)
        myservo1.attach(5);    
        digitalWrite(led, HIGH);
        myservo1.writeMicroseconds(2000);  //Rotate the continuous rotation servo anti-clockwise
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dispensing...");      //360 + 90 = 450
        for (pos=90; pos <=450; pos +=1) { //Inital position for continuous rotation servo is 90 (Not 0 or else the servo will turn backwards first before turning the proper position way).
          myservo1.write(pos);
          delay(10); //Total time for continuous rotation servo to turn anti-clockwise in 360 degree is 3 seconds.    
  }
        myservo1.detach(); //stops the continuous servo or else it will run continuously non-stop

 }
      if (percentage > 105 and percentage < 110) { //90% = 7.5cm (Ice cube level in cup is near filled)
        Serial.print("\nCup is filled up. Closing dispenser...");
        myservo1.attach(5);
        myservo1.writeMicroseconds(1000);  //Rotate the continuous rotation servo clockwise
        lcd.clear();
        digitalWrite(led, LOW);
        lcd.setCursor(0,0);
        lcd.print("Closing ");
        lcd.setCursor(0,1);
        lcd.print("dispenser...");
        delay(3500); //wait 3.5 seconds to turn clockwise back 360 degree to inital position
        myservo1.detach();
      }
 
      buttonState = digitalRead(buttonPin); //Checks if button is pressed again to turn off the system
      if (buttonState==HIGH) {      
        previousState=1;
       }

     delay(500);
}

      if (previousState == 1) {      
      lcd.clear();             //Clear all written things on the LCD.
      lcd.print("System Offline"); //LCD prints "System offline"
      Serial.println("\n");          
      Serial.println("The System is Offline");  //Serial monitor prints LCD, LED and alarm are offline.
      Serial.println("\n");
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);      
      previousState=0;
 }
    }
delay(500);
}
