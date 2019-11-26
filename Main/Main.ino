//count is the current number of people in the room

int count = 0;

// defining all pins

#ifndef RELAY_LIGHT_PIN 
  #define RELAY_LIGHT_PIN 10
#endif

#ifndef RELAY_FAN_PIN
  #define RELAY_FAN_PIN 11
#endif

#ifndef TRIGGER_OUTSIDE
  #define TRIGGER_OUTSIDE 3
#endif

#ifndef ECHO_OUTSIDE 
  #define ECHO_OUTSIDE 4
#endif 

#ifndef  TRIGGER_INSIDE 
  #define TRIGGER_INSIDE 5
#endif 

#ifndef ECHO_INSIDE
  #define ECHO_INSIDE 6
#endif


void setup() {

  Serial.begin(9600);

  //defining all pin outputs
  pinMode(RELAY_LIGHT_PIN , OUTPUT);
  pinMode(RELAY_FAN_PIN , OUTPUT);
  pinMode(TRIGGER_OUTSIDE , OUTPUT);
  pinMode(TRIGGER_INSIDE , OUTPUT);
  pinMode(ECHO_OUTSIDE , INPUT);
  pinMode(ECHO_INSIDE , INPUT);

}

//Function to measure distance in a Ultrasonic sensor
float MeasureDistance(int ECHO_PIN , int TRIGGER_PIN)
{

  float distance , duration;
  
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance= duration*0.034/2;

  return distance;
}

void loop() {
  
  //If outside sensor detects a person coming in add 1 to count in room
  
  if(MeasureDistance(ECHO_OUTSIDE , TRIGGER_OUTSIDE) <=5)
  {
    count = count + 1;
  }

  //If inside sensor detects a person going out decrease the count in room
  
  if(MeasureDistance(ECHO_INSIDE , TRIGGER_INSIDE) <=5)
  {
    count = count - 1;
  }

  //If count is 0 turn off all lights and fans

  if(count == 0)
  {
    digitalWrite(RELAY_LIGHT_PIN , LOW);
    digitalWrite(RELAY_FAN_PIN , LOW);
    Serial.println("0 people in room");
  }
  Serial.println(count);

}
