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
int lastDetection=0;
bool motionDetected=false;
bool photoresistorOn=false;

int criticalLightLevel=0;
int brightnessLevel=0;

uint8_t messageBuffer[10];

void playTvMode();
void photoresistorModeOn();
void lightsOn();
void lightsOff();
void handleRecivedMessage();
void motionOn();
void sendAck();

void setup() {
  randomSeed(analogRead(A0));
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(pirPin, INPUT);

  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);

  state=NONE;

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
    if(motionDetected==true) lastDetection++;
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
  delay(100);

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

  if((state==PHOTO)||(state==MOTION)) lightsOff();

  sendAck();
}


void lightsOn()
{
  analogWrite(redPin,255-((redLevel*brightnessLevel)/100));
  analogWrite(greenPin,255-((greenLevel*brightnessLevel)/100));
  analogWrite(bluePin,255-((blueLevel*brightnessLevel)/100));
}


void photoresistorModeOn()
{
  int lightLevel=analogRead(photoresistorPin);
  lightLevel=map(lightLevel,0,1023,1,100);

  if(lightLevel<criticalLightLevel)
  {
    lightsOn();
    photoresistorOn=true;
  } 
  else if(photoresistorOn==true)
  {
    lightsOff();
  }
}


void motionOn()
{
  if(lastDetection>50)
  {
    lightsOff();
    lastDetection=0;
    motionDetected=false;
  } 
  else if(digitalRead(pirPin)==HIGH)
  {
    motionDetected=true;
    lightsOn();
  } 
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
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,HIGH);
}


void sendAck()
{
  Serial.write(1);
  Serial.flush();
}