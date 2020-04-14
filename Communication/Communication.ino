void setup() {
  // put your setup code here, to run once:
  
pinMode(8, INPUT);      // Inializes Pin 8 as input pin
pinMode(3, OUTPUT);     // Inializes Pin 3 as output pin 
                        // ** DO NOT USE PIN 2 - DOESN'T WORK/FRIED **
pinMode(7, OUTPUT);     // Inializes Pin 7 as output pin 
digitalWrite(2, LOW);   // Sets output to Low, light is off
digitalWrite(7, LOW);   // Sets output to Low, light is off

Serial.begin(9600);     // Initializes Serial connection and sets data rate to 9600 bits/s
Serial2.begin(9600);    // Initializes Serial connection and sets data rate to 9600 bits/s
delay (1000);           // Delays 1s
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(8) == HIGH){ //If there is information available to read
    digitalWrite(3, HIGH);    //Make first LED turn on, indicating something is sent
    Serial2.write('J');       //Send letter "s" out
    
    
    delay(500);                // delay so we don't send character every millisecond
    digitalWrite(3, LOW);
  }
  if (Serial2.available()) {  //If there is information available to read
  char incoming = Serial2.read(); // If something is recieved, then 
    digitalWrite(7, HIGH);        // Turn on 2nd LED, indicating data recieved
    Serial.print(incoming);
    delay(500);                  // Delay 1s
    digitalWrite(7, LOW);         // Turn off 2nd LED

  }
}
