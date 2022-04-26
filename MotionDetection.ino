//PIR Sensor Motion Detection

int data = 0;//n
int calibrationTime = 15; //the time we give the sensor to calibrate
int lowIn;                //the time when the sensor outputs a low impulse long unsigned
int pause = 2500;         //the amount of milliseconds the sensor has to be low before we assume all motion has stopped long unsigned 
boolean lockLow = true; 
boolean takeLowTime; 
int pirPin = 3;           //the digital pin connected to the PIR sensor's output 
int ledPin = 13;          //digital pin the led is connected to

//Detection Setup
void setup(){ 
    Serial.begin(9600); 
    pinMode(pirPin, INPUT); 
    pinMode(ledPin, OUTPUT); 
    digitalWrite(pirPin, LOW); 
    //give the sensor some time to calibrate 
    Serial.print("calibrating sensor "); 

    for(int i = 0; i < calibrationTime; i++)
    {
        Serial.print("."); 
        delay(1000); 
    } 
    Serial.println(" done"); 
    Serial.println("Sensor Calibrated"); 
    delay(50); 
    
}

//Detection Loop
void loop(){
     if(digitalRead(pirPin) == HIGH)
     { 
        digitalWrite(ledPin, HIGH); 
        //the led visualizes the sensors output pin state 
        if(lockLow){ 
            //makes sure we wait for a transition to LOW before any further output is made: 
            lockLow = false; 
            Serial.println("---"); 
            Serial.print("motion detected at ");
            Serial.print(millis()/1000); 
            Serial.println(" sec"); 
            
            float dataRead = digitalRead(pirPin);
            if(digitalRead(pirPin) == HIGH){
              data++;
            }
            String dataToSend = String(data);
            Serial.print(dataToSend);
            Serial.println(" person(s) spotted.");
            delay(50); 
        } 
        takeLowTime = true; 
    } 
    if(digitalRead(pirPin) == LOW)
    { 
        digitalWrite(ledPin, LOW); 
        //the led visualizes the sensors output pin state 
        if(takeLowTime)
        { lowIn = millis(); 
            //save the time of the transition from high to LOW 
            takeLowTime = false; 
            //make sure this is only done at the start of a LOW phase 
        } 
        //if the sensor is low for more than the given pause, we assume that no more motion is going to happen 
        if(!lockLow && millis() - lowIn > pause)
        { 
            //makes sure this block of code is only executed again after 
            //a new motion sequence has been detected 
          lockLow = true; 
          Serial.print("motion ended at "); //output 
          Serial.print((millis() - pause)/1000); 
          Serial.println(" sec"); 
          delay(50); 
        } 
    } 
}

    
