#define Relay 12
#define buzzer A0
static const int sensorPin = 10;                    
int SensorStatePrevious = LOW;                  

unsigned long minSensorDuration = 3000;            
unsigned long minSensorDuration2 = 6000;
unsigned long SensorLongMillis;                
bool SensorStateLongTime = false;                  

const int intervalSensor = 50;                    
unsigned long previousSensorMillis;                 

unsigned long SensorOutDuration;                 
unsigned long currentMillis;        

void setup() {
  Serial.begin(9600);                

  pinMode(sensorPin, INPUT);         
  Serial.println("Press button");
  pinMode(Relay,OUTPUT);
  pinMode(buzzer,OUTPUT);
}


void readSensorState() {

  if(currentMillis - previousSensorMillis > intervalSensor) {
    int SensorState = digitalRead(sensorPin);    
    Serial.println(SensorState);
    
    if (SensorState == HIGH && SensorStatePrevious == HIGH && !SensorStateLongTime) {
     SensorLongMillis = currentMillis;
       SensorStatePrevious = LOW;
      
      Serial.println("Button pressed");
    }

  
   SensorOutDuration = currentMillis - SensorLongMillis;

    if (SensorState == HIGH && !SensorStateLongTime && SensorOutDuration >= minSensorDuration) {
      SensorStateLongTime = true;
      digitalWrite(buzzer,HIGH);
      Serial.println("Button long pressed");
    }
    if (SensorState == HIGH && SensorStateLongTime && SensorOutDuration >= minSensorDuration2) {
     SensorStateLongTime = true;
      digitalWrite(Relay,HIGH);
      delay(1000);
      Serial.println("Button long pressed");
    }
      
    if (SensorState == LOW && SensorStatePrevious == LOW) {
      SensorStatePrevious = HIGH;
      SensorStateLongTime = false;
      digitalWrite(Relay,LOW);
      digitalWrite(buzzer,LOW);
      Serial.println("Button released");

  
    }
    
   previousSensorMillis = currentMillis;

  }

}

void loop() {

  currentMillis = millis();    
  readSensorState();           
  
}

