// defines number of seconds and minutes
#define numberOfSeconds(_time_)  ((_time_/ 1000) % 60)
#define numberOfMinutes(_time_)  (((_time_/ 1000) / 60) % 60)

//1000ms in 1sec, 60sec in 1min, 60mins in 1hr. So, 1000x60x60 = 3600000ms = 1hr
unsigned long timeLimit = 3600000;
unsigned long timeLimit30Min = 1800000;
unsigned long timeLimit5Min = 300000;

// defines pins numbers
const int trigPin = 12;             // Connect trig pin to
const int echoPin = 13;             // Connect echo pin to
const int buzzer = 9;              // Connect buzzer pin to
const int resetButton = 7;         // Connect ResetButton pin to
const int snoozeButton = 6;        // Connect SnoozeButton pin to

//defines variables

long duration;
int distance;

//change variable state
int snoozeButtonCount = 0;        // variable for counting snooze button
int resetButtonCount = 0;         // variable for counting reset  button 

// Check Snooze State 
boolean snoozeState = false;

void setup() {
  pinMode(trigPin, OUTPUT);       // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);        // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);        // Sets the Buzzer as Output
  pinMode(resetButton, INPUT);    // Sets the Reset Button as Input
  pinMode(snoozeButton, INPUT);   // Sets the Snooze Button as INPUT);
  Serial.begin(9600);             // Starts the serial communication

}

void loop() {

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  
  // Calculating the distance
  distance = duration*0.034/2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

 
   
  // Object is detected
  while(distance <= 40){
    
     
     Serial.println("People Detected");

     if(snoozeState == true){
        unsigned long timeRemainingSnooze = timeLimit5Min - millis();
        if(timeRemainingSnooze > 0){
            // To display the countdown in mm:ss format, separate parts
            int seconds = numberOfSeconds (timeRemainingSnooze);
            int minutes = numberOfMinutes (timeRemainingSnooze);    
        }

        if(timeRemainingSnooze == 0){
          // Buzzer
          digitalWrite(buzzer,HIGH);
          break;
        }
        
     }else{
       unsigned long timeRemaining = timeLimit - millis();

       if(timeRemaining > 0){
        
        // To display the countdown in mm:ss format, separate parts
        int seconds = numberOfSeconds (timeRemaining);
        int minutes = numberOfMinutes (timeRemaining);
        
       }
        // If time remaining is 0 
        if(timeRemaining == 0){
          // Buzzer
          digitalWrite(buzzer,HIGH);
          break;
        }
      
     }
  }

  // Object is not detected
  while(distance > 40){
    Serial.println("People not detected!");

    unsigned long timeRemaining = timeLimit30Min - millis();

    if(timeRemaining > 0){
      
      // To display the countdown in mm:ss format, separate parts
      int seconds = numberOfSeconds (timeRemaining);
      int minutes = numberOfMinutes (timeRemaining);
  
      // Update the time remaining
      timeRemaining = timeLimit30Min - millis();
      
     }

     // If time remaining is 0 
     if(timeRemaining == 0){
        // Buzzer
        digitalWrite(buzzer,HIGH);
        break;
     }
     
  }

  // Check Buzzer State
  int checkBuzzer = digitalRead(buzzer);
  
  if(checkBuzzer == HIGH){

  
      // Snooze incoming
      int checkCurrentSnooze = digitalRead(snoozeButton);
    
      // Initial Case (Happen Once)
      if(checkCurrentSnooze == HIGH && snoozeButtonCount == 0){

          // Increase count for snooze button 
          snoozeButtonCount++;
    
          snoozeState = true;
          digitalWrite(buzzer,LOW);
      
    }else{
      
       snoozeButtonCount++;
       snoozeState = true;
       digitalWrite(buzzer,LOW);
   
    }
   
  }
  
  // Reset Button
  int checkCurrentReset = digitalRead(resetButton);

  /**
   * First time reset button get call 
   * Action : Silence buzzer (if HIGH) and the program will loop itself again
   */
  if(checkCurrentReset == HIGH && resetButtonCount == 0){
      
     snoozeButtonCount++;
     
     if(checkBuzzer == HIGH){
       digitalWrite(buzzer, LOW);
     }
  }else{
    snoozeButtonCount++;
    
    if(checkBuzzer == HIGH){
      digitalWrite(buzzer,LOW);
    }
  }
  
} 
