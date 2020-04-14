char val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //initialze serial
  pinMode(49, INPUT);    //set pin49 as input
  pinMode(3, OUTPUT);   //set pin 3 as output
  digitalWrite(3, LOW);   //start will LED off
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(rcTime(49) != NULL){   //if rctime function call is yeilding value
    Serial.println(rcTime(49));  //print out that value
    digitalWrite(3, HIGH);   //turn LED on
    delay(3000);             //wait 3 seconds
    digitalWrite(3, LOW);    //turn it off
    //delay(2000);            /wait 2 more seconds
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
