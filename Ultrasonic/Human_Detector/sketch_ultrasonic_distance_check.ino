// defines number of seconds and minutes
#define numberOfSeconds(time)  ((_time_/ 1000) % 60)
#define numberOfMinutes(time)  (((_time_/ 1000) / 60) % 60)

//1000ms in 1sec, 60sec in 1min, 60mins in 1hr. So, 1000x60x60 = 3600000ms = hr
unsigned long timeLimit = 3600000;

// defines pins numbers
const int trigPin = Pinnumbers;
const int echoPin = Pinnumbers;

//defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
  Serial.begin(9600);          // Starts the serial communication

}

/*
 * Function to check distance 
 * return true if it detect people in range
 * otherwise return false
 */
boolean checkDistance(int distance){
    // Return true only when distance detect person in range
    if(distance >= 1 && distance <= 40){
        delay(500);
        Serial.println("People Detected");
        return true;
    }else{
      delay(500);
      Serial.println("I cannot see people!");
      return false;
    }
}

/*
 * Function to check the time 
 * 
 * parameter type : boolean 
 * parameter name : distance
 * 
 * return true if it detect people and countdown 
 * 
 */
boolean countdown(boolean check) {

  // Set condition for countdown if the sensor detect people in range
  if(check == true){
    
    Serial.println("People Detected start countdown!");
    
    //Calculate the time remaining
    unsigned long timeRemaining = timeLimit - millis();

    // Loop until Timeremaining is 0
    while(timeRemaining > 0) {
      // To display the countdown in mm:ss format, separate parts
      int seconds = numberOfSeconds (timeRemaining);
      int minutes = numberOfMinutes (timeRemaining);
  
      // Update the time remaining
      timeRemaining = timeLimit - millis();
    }

    // If time remaining is 0
    if(timeRemaining == 0){
      return true;
    }
  }else{
    // Cannot detect people in range 
    Serial.println("Sensor cannot detect people in range!");
    return false;
  }
  
 }

/**
 * Function which make buzzer alert depends on countdown
 * Parameter Type : Boolean
 * Parameter Name : countdownCheck
 * 
 * Return : Void
 */
void buzzerAlert(boolean countdownCheck){
  // If countdown is true buzz
  if(countdownCheck == true){
     // Make Buzzer Buzz

     // Make Button Snooze Buzzer
  }
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
  

  // Check whether people in sensor range
  boolean checkD = checkDistance(distance); 

  // Call Countdown function
  boolean checkCountDown = countdown(checkD);

  // Buzzer
  buzzerAlert(checkCountDown);
  
}
