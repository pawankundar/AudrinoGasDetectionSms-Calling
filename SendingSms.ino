#include <SoftwareSerial.h>
#include <Servo.h> 

SoftwareSerial mySerial(9, 10); // gsm module connected here
String textForSMS;
int smokeS = A1; // smoke / gas  sensor connected with analog pin A1 of the arduino / mega. 
int data = 0; 
int redLed = 2;
int greenLed = 3;
int servoPin = 13;
int buzzer =8;
Servo servo; 

void setup() {


  randomSeed(analogRead(0));
  
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(smokeS, INPUT); 
  servo.attach(13); 
   
}

void loop() {

  data = analogRead(smokeS); 
  
  Serial.print("Smoke: "); 
  Serial.println(data); 

  
     if ( data > 320) // 
  {
digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 20000);
 servo.write(1);               
    delay(355);   

       textForSMS =  "\nGas Or Smoke Detected";  
  sendSMS(textForSMS);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  
delay(500);

  }

     else
     {
       delay(350);
  digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
   servo.write(200); 
  
  }}


void sendSMS(String message)
{
 mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+PhoneNumberHereWithCountryCode\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("ALERT!!! CNG gas leakage");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      
}
