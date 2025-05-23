#include <Arduino.h>
#define photoresistorPin A5
#define redPin 9
#define greenPin 10
#define bluePin 11
#define pirPin 2

enum State {NORMAL, PHOTO, MOTION, TV, NONE};
State state;

int redLevel=0;
int greenLevel=0;
int blueLevel=0;

int criticalLightLevel=0;
int brightnessLevel=0;

uint8_t messageBuffer[10];

void playTvMode();
void photoresistorModeOn();
void lightsOn();
void lightsOff();
void handleRecivedMessage();
void motionOn();

void setup() {
  randomSeed(analogRead(A0));
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

  if(state==NORMAL)
  {
    lightsOn();
  }
  else if(state==PHOTO)
  {
    photoresistorModeOn();
  }
  else if(state==MOTION)
  {
    motionOn();
  }
  else if(state==TV)
  {
    playTvMode();
  }
  else
  {
    lightsOff();
  }
  delay(500);

}


void serialEvent()
{
  uint8_t counter=0;
  while(Serial.available() && counter<10)
  {
    messageBuffer[counter]=Serial.read();
    ++counter;
  }
  
  handleRecivedMessage();
}

void handleRecivedMessage()
{
  if(messageBuffer[0]==1) state=NORMAL;
  else if(messageBuffer[0]==2) state=PHOTO;
  else if(messageBuffer[0]==3) state=MOTION;
  else if(messageBuffer[0]==4) state=TV;

  if((state==NORMAL)||(state==PHOTO)||(state==MOTION))
  {
    redLevel=messageBuffer[1];
    greenLevel=messageBuffer[2];
    blueLevel=messageBuffer[3];
    brightnessLevel=messageBuffer[4];
  }
  if(state==PHOTO) criticalLightLevel=messageBuffer[5];
}


void lightsOn()
{
  analogWrite(redPin,redLevel*brightnessLevel);
  analogWrite(greenPin,greenLevel*brightnessLevel);
  analogWrite(bluePin,blueLevel*brightnessLevel);
}


void photoresistorModeOn()
{
  int lightLevel=analogRead(photoresistorPin);
  lightLevel=map(lightLevel,0,1023,1,100);
  if(lightLevel<criticalLightLevel) lightsOn();
}


void motionOn()
{
  if(digitalRead(pirPin)==LOW) lightsOn;
}


void playTvMode()
{
  brightnessLevel=100;
  redLevel=random(0,256);
  greenLevel=random(0,256);
  blueLevel=random(0,256);
  lightsOn();
}


void lightsOff()
{
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
}