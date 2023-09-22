#include <SoftwareSerial.h>

#define sensorPin 7 //DC

unsigned long lastEvent = 0; //DC 

int PulseSensorPurplePin = A1;
int LED13=13;
int Signal;
int Threshold =30;
int S;
int k;

SoftwareSerial mySerial(10, 11);

void setup()
{
	// pinMode(sensorPin, INPUT); //DC
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(LED13,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop ()
{
  //BPM
  Signal = analogRead(PulseSensorPurplePin);
  S=(Signal/12);
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
  // ECG:
  if((digitalRead(5) == 1)||(digitalRead(6) == 1)){
  Serial.println('!');
  }
  else
  {
    Serial.print("ECG values:");
    Serial.println(analogRead(A0));
  }
}
