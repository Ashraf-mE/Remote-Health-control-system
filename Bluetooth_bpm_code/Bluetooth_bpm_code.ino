#include <SoftwareSerial.h>

int PulseSensorPurplePin =A1;
int LED13=13;
int Signal;
int Threshold =30;
int S;

SoftwareSerial mySerial(10, 11);

void setup()
{
  pinMode(LED13,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop ()
{
  Signal = analogRead(PulseSensorPurplePin);
  S=(Signal/8);
  Serial.print("Your heart beat is: ");
  Serial.println(S);
  mySerial.println(S);
  if(Signal > Threshold)
  {
    digitalWrite(LED13, HIGH);
  }
  else
  {
    digitalWrite(LED13, LOW);
  }
  delay(1000);
}