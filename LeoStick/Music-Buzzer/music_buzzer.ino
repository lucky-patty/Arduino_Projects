void Tone(int buzzer, int Freq, int duration){ 
  int uSdelay = 1000000 / (Freq * 2);
  unsigned long ending = millis() + duration;
  while(millis() < ending){
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(uSdelay);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(uSdelay);
  }
} 
int buzzer = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Tone(buzzer,500,500);
delay(2000);
}
