#include <Arduino.h>
#define photoresistorPin A5
#define redPin 9
#define greenPin 10
#define bluePin 11
#define pirPin 2

int redLevel=0;
int greenLevel=0;
int blueLevel=0;

int criticalLightLevel=0;

bool isOn=false;
bool photoresistorDetectionOn=false;
bool pirDetectionOn=false;
bool tvModeOn=false;

void playTvMode();
void photoresistorModeOn();
void lightsOn();
void lightsOff();

void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(pirPin, INPUT);

  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);

  Serial.begin(9600);
}

void loop() {

  if(isOn)
  {
    lightsOn();
  }
  else if(photoresistorDetectionOn)
  {
    photoresistorModeOn();
  }
  else if(pirDetectionOn)
  {
    // TODO
  }
  else if(tvModeOn)
  {
    playTvMode();
  }
  else
  {
    lightsOff();
  }
  

}


void serialEvent()
{
  //TODO handle incoming message
}


void playTvMode()
{

}

void photoresistorModeOn()
{
  int lightLevel=analogRead(photoresistorPin);
  if(lightLevel<criticalLightLevel) lightsOn();
}

void lightsOn()
{
  analogWrite(redPin,redLevel);
  analogWrite(greenPin,greenLevel);
  analogWrite(bluePin,blueLevel);
}

void lightsOff()
{
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
}
