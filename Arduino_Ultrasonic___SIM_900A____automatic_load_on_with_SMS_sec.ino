//Arduino Ultrasonic & SIM 900A    automatic load on with SMS security
#include <SoftwareSerial.h>
SoftwareSerial gsm(7,8);//tx,rx
String outMessage = "SomeOne Enter in home!";
String destinationNumber = "+88017xxxxxxxx";//Enter your phone number

int trigPinA =A0;
int echoPinA =A1;
long durationA;
int distanceA;
int LED = 3;


int led = 13;
int button = A4;
int buttonState = 0;
int flag = 0;
int flaga = 0;

void setup() {
Serial.begin(9600);
pinMode(trigPinA,OUTPUT);
pinMode(echoPinA,INPUT);
pinMode(LED,OUTPUT);

pinMode(led,OUTPUT);
pinMode(button,INPUT);
}
void loop() {
digitalWrite(trigPinA,LOW);
delayMicroseconds(2);
digitalWrite(trigPinA,HIGH);
delayMicroseconds(10);
digitalWrite(trigPinA,LOW);
durationA=pulseIn(echoPinA,HIGH);
distanceA = durationA*0.034/2;
Serial.print("distanceA:");
Serial.println("distanceA");



if(distanceA <= 7){
  
  digitalWrite(LED,LOW);
  delay(500);
}

if(distanceA >= 20){
digitalWrite(LED,HIGH);
}


buttonState = digitalRead(button);

if(buttonState == HIGH && flag == 0){
  flag = 1;
  digitalWrite(led,HIGH);
}
else if(buttonState == HIGH && flag == 1){
  digitalWrite(led,LOW);
  flag = 0;
}
delay(200);




if(distanceA <= 20 && flag == 1){
  digitalWrite(LED,LOW);

gsm.begin(115200);
gsm.print("AT+CMGF=1\r");
delay(1000);
gsm.println("AT + CMGS = \"" + destinationNumber +"\"");
delay(1000);
gsm.print(outMessage);
delay(1000);
gsm.write((char)26);
//ctrl+z
delay(1000);
gsm.println("AT+CLTS=1");
gsm.println("AT+CCLK?");
  
}



}
