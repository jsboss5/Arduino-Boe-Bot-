char val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //initialze serial
  Serial2.begin(9600); 
  pinMode(49, INPUT);    //set pin49 as input
  pinMode(3, OUTPUT);   //set pin 3 as output
  pinMode(7, OUTPUT);     // Inializes Pin 7 as output pin 

  
  digitalWrite(3, LOW);   //start will LED off
  digitalWrite(7, LOW);   // Sets output to Low, light is off


}

void loop() {
  // put your main code here, to run repeatedly:
  if(rcTime(49) != NULL){   //if rctime function call is yeilding value
    Serial.println(rcTime(49));  //print out that value
    digitalWrite(3, HIGH);   //turn LED on
    Serial2.write('J');       //Send letter "s" out
    delay(3000);             //wait 3 seconds
    digitalWrite(3, LOW);    //turn it off
    //delay(2000);            /wait 2 more seconds
  } 
  
if (Serial2.available()) {  //If there is information available to read
  char incoming = Serial2.read(); // If something is recieved, then 
    digitalWrite(7, HIGH);        // Turn on 2nd LED, indicating data recieved
    Serial.print(incoming);
    delay(500);                  // Delay 1s
    digitalWrite(7, LOW);         // Turn off 2nd LED

  }
}

long rcTime(int pin) {     //RCtime function returns value if 
 pinMode(pin, OUTPUT);       //RFID is read
 digitalWrite(pin, HIGH);
 delayMicroseconds(230);
 pinMode(pin, INPUT);
 digitalWrite(pin, LOW); long
 time = micros(); while
 (digitalRead(pin)); 
 time = micros() - time; 
 return time;
} 
