  #define BUFSIZE    15  // Size of receive buffer (in bytes) (10-byte unique ID + null character)
  #define RFID_START  0x02  // RFID Reader Start and Stop bytes
  #define RFID_STOP   0x03
  int RFIDcounter = 0;
  bool isThere = false;
  bool shouldPrint = true;
  
  
  #include<Servo.h>

  
  Servo servoLeft;
  Servo servoRight;
  
  int QTIPinL = 47;  //initialize qti pinL variable for input pin
  int QTIPinM = 51;   // ^
  int QTIPinR = 52;   // . ^
  int QTIVal_L = 0;  //Sets the reading from QTI to 0
  int QTIVal_M = 0;   //Sets the reading from QTI to 0
  int QTIVal_R = 0;     //Sets the reading from QTI to 0
  int Threshold = 200;  //Set's threshold between black and white to 200
  int HashCounter = 0;

void setup() {
  //From comminication
    Serial2.begin(9600); 
    Serial1.begin(9600);                           // Inintialize the RFID serial port

  
  
  
  
  Serial.begin(9600);  //Initializes serial monitor
   Serial.flush();                         // wait for all bytes to be transmitted to the Serial Monitor
  //initialize servo
  servoLeft.attach(12);    //initilizes left wheels
  servoRight.attach(11);   //initializes right wheels
  servoLeft.writeMicroseconds(1500);    //make sure it is stationary
  servoRight.writeMicroseconds(1500);
}

void loop() {
  //from RFID
  char rfidData[BUFSIZE];                        // Buffer for incoming data
  char offset = 0;                                                      // Offset into buffer
  rfidData[0] = 0;
  
  
  // different if statements based on what is seen
  // compare to threshold
  // change servo speed accordingly
 
  QTIVal_M = rcTime(QTIPinM);   //obtain rcTime for middle sensor and store in variable
  QTIVal_L = rcTime(QTIPinL);   //obtain rcTime for left sensor and store in variable
  QTIVal_R = rcTime(QTIPinR);   //obtain rcTime for right sensor and store in variable
  
 
  //PRINTS IF ITS BLACK OR WHITE
//  if(QTIVal_L <= Threshold) Serial.println("white");   
//  if(QTIVal_L >= Threshold) Serial.println("black");
//  if(QTIVal_M <= Threshold) Serial.println("white");
//  if(QTIVal_M >= Threshold) Serial.println("black");
//  if(QTIVal_R <= Threshold) Serial.println("white");
//  if(QTIVal_R >= Threshold) Serial.println("black");
//  Serial.println(" ");

  if(HashCounter <5){
  
  if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 0){ //if qti logic function says 0, execute corresponding action
    goForward();                                      //calls goForward function below
    }
  
  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 1){   //if qti logic function says 1, stop, then move foward
    
    servoStop();      //calls stop function
    HashCounter++;
//    Serial.print(HashCounter);  
    delay(2000);      //wait for 2 seconds
    
    
    
    
    
    
    while(Serial1.available() > 0)                        //Loop that waits for a tag to be read
  {
    
    
    if (Serial1.available() > 0)             // If there are any bytes available to read, then the RFID Reader has probably seen a valid tag
    {
      isThere = true;
      Serial.print(isThere);
      rfidData[offset] = Serial1.read();        // Get the byte and store it in our buffer
      if (rfidData[offset] == RFID_START)    // If we receive the start byte from the RFID Reader, then get ready to receive the tag's unique ID
      {
        offset = -1;     // Clear offset (will be incremented back to 0 at the end of the loop)
      }
      else if (rfidData[offset] == RFID_STOP)  // If we receive the stop byte from the RFID Reader, then the tag's entire unique ID has been sent
      {
        rfidData[offset] = 0;                     // Null terminate the string of bytes we just received
        //COMUNICATION CODE

        
        break;                                 // Break out of the loop
      }
          
      offset++;                         // Increment offset into array
      if (offset >= BUFSIZE) offset = 0; // If the incoming data string is longer than our buffer, wrap around to avoid going out-of-bounds
    }
  }
  
  Serial.println(rfidData);       // The rfidData string should now contain the tag's unique ID with a null termination, so display it on the Serial Monitor
  Serial.flush();   
  if(isThere){
 
  
  RFIDcounter++;
  Serial.print(RFIDcounter);
  
  
  isThere = false;
  }



  
    if(HashCounter < 5){
    goForwardHash();   //call go foward hash function
    delay(500);     //weight .1 seconds
    }
    }

  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) ==2){   //if qti dictates, go left
    turnLeft();
    }

  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 3){   //if qti dictates, go right
    turnRight();
    }
  
  }

  else{

    //communicate
    if(shouldPrint == true){
    if(RFIDcounter == 0) Serial2.write('a');       //Send letter "s" out
    if(RFIDcounter == 1) Serial2.write('b');       //Send letter "s" out
    if(RFIDcounter == 2) Serial2.write('c');       //Send letter "s" out
    if(RFIDcounter == 3) Serial2.write('d');       //Send letter "s" out
    if(RFIDcounter == 4) Serial2.write('e');       //Send letter "s" out
    if(RFIDcounter == 5) Serial2.write('f');       //Send letter "s" out
    shouldPrint = false;
    servoStop();
    
    }
    }
  
  }
  
  
 int qtiLogic(int QTIVal_L, int QTIVal_M, int QTIVal_R){  
      // 0 - GO STRAIGHT 
      // 1 at long hashmark (stop points) - STOP
      // 2  TURN LEFT
      // 3  TURn RIGHT
      // 4 - ID KNOW SOMETHING WENT WRONG
    
    if( QTIVal_L >= Threshold && QTIVal_M >= Threshold && QTIVal_R >= Threshold){  //if all three sensors black, stop
      return 1;
      }
  
    if( QTIVal_L >= Threshold && QTIVal_M >= Threshold && QTIVal_R <= Threshold){  // if left and middle black, turn left
      return 2; 
      } 
  
    if( QTIVal_L >= Threshold && QTIVal_M <= Threshold && QTIVal_R <= Threshold){   //if just left black, turn left
        return 2;
      } 


    if( QTIVal_L <= Threshold && QTIVal_M >= Threshold && QTIVal_R >= Threshold){  //if right and middle black, turn right
          return 3;
        } 

    if( QTIVal_L <= Threshold && QTIVal_M <= Threshold && QTIVal_R >= Threshold){  //if just right black, turn right
          return 3;
        }

    if( QTIVal_L <= Threshold && QTIVal_M >= Threshold && QTIVal_R <= Threshold){  //if middle is only black, move foward
          return 0;
        }
  
    if( QTIVal_L <= Threshold && QTIVal_M <= Threshold && QTIVal_R <= Threshold){   //No logic needed for this case
            return 4;
          }
  
  }

void goForward(){         //Function tells servo to move foward
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1400);
}

void goForwardHash(){   //function tells to move foward after being stopped
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  
}

void servoStop(){   //function tells servo to stop
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void mainTurn(){    //function tells servo to turn - not used 
  servoLeft.writeMicroseconds(1750);
  servoRight.writeMicroseconds(1350);
}

void turnLeft(){                      // Left turn function
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise                              
}

void turnRight(){                       // Right turn function
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
                                        // Maneuver for time ms
}


long rcTime(int pin) {   //RCtime - converts reading from qti into value
 pinMode(pin, OUTPUT);
 digitalWrite(pin, HIGH);
 delayMicroseconds(230);
 pinMode(pin, INPUT);
 digitalWrite(pin, LOW); 
 long time = micros(); 
 while (digitalRead(pin)); 
 time = micros() - time; 
 return time;
} 
