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

  
     if ( data > 230) // 
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
Serial.println("Calling through GSM Modem");
          mySerial.begin(9600);//setting baudrate at 9600;
          delay(1000);
          mySerial.println("ATDPhoneNumberwithCode;"); // ATDxxxxxxxxxx; semicolon should be at the last ;AT command that follows UART protocol , egATD+911111111111;
          Serial.println(" Message of your choice here ");
          delay(1000);
          if (mySerial.available())
          Serial.write(mySerial.read());
      
}


