  #include<Servo.h>

  
  Servo servoLeft;
  Servo servoRight;
  
  int QTIPinL = 47;
  int QTIPinM = 51;
  int QTIPinR = 52;
  int QTIVal_L = 0;
  int QTIVal_M = 0;
  int QTIVal_R = 0;
  int Threshold = 200;
void setup() {
  Serial.begin(9600);
  pinMode(49, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  //initialize servo
  servoLeft.attach(12);
  servoRight.attach(11);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void loop() {
  // different if statements based on what is seen
  // compare to threshold
  // change servo speed accordingly
 
  QTIVal_M = rcTime(QTIPinM);
  QTIVal_L = rcTime(QTIPinL);
  QTIVal_R = rcTime(QTIPinR);
  
 
  //PRINTS IF ITS BLACK OR WHITE
  //if(QTIVal_L <= Threshold) Serial.println("white");
  //if(QTIVal_L >= Threshold) Serial.println("black");
  //if(QTIVal_M <= Threshold) Serial.println("white");
  //if(QTIVal_M >= Threshold) Serial.println("black");
  //if(QTIVal_R <= Threshold) Serial.println("white");
  //if(QTIVal_R >= Threshold) Serial.println("black");
  //Serial.println(" ");


    //RFID LOGIC
  
    
  if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 0){
    goForward();
    }
  
  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 1){
    
    servoStop();
    if(rcTime(49) != NULL){
       Serial.println(rcTime(49));
       digitalWrite(3, HIGH);
       Serial.print("YO");
       }
       
    Serial.print("BRO");
    delay(2000); 
    digitalWrite(3, LOW);
    goForwardHash();
    delay(100);
    
    }

  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) ==2){
    turnLeft();
    }

  else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 3){
    turnRight();
    }
  
  //else if(qtiLogic( QTIVal_L,  QTIVal_M,  QTIVal_R) == 4){
    //turnLeft();
    //}
  
  }
  
  
 int qtiLogic(int QTIVal_L, int QTIVal_M, int QTIVal_R){
      // 0 - GO STRAIGHT 
      // 1 at long hashmark (stop points) - STOP
      // 2  TURN LEFT
      // 3  TURn RIGHT
      // 4 - ID KNOW SOME SHIT WENT WRONG
    
    if( QTIVal_L >= Threshold && QTIVal_M >= Threshold && QTIVal_R >= Threshold){
      return 1;
      }
  
    if( QTIVal_L >= Threshold && QTIVal_M >= Threshold && QTIVal_R <= Threshold){
      return 2;
      } 
  
    if( QTIVal_L >= Threshold && QTIVal_M <= Threshold && QTIVal_R <= Threshold){
        return 2;
      } 


    if( QTIVal_L <= Threshold && QTIVal_M >= Threshold && QTIVal_R >= Threshold){
          return 3;
        } 

    if( QTIVal_L <= Threshold && QTIVal_M <= Threshold && QTIVal_R >= Threshold){
          return 3;
        }

    if( QTIVal_L <= Threshold && QTIVal_M >= Threshold && QTIVal_R <= Threshold){
          return 0;
        }
  
    if( QTIVal_L <= Threshold && QTIVal_M <= Threshold && QTIVal_R <= Threshold){
            return 4;
          }
  
  }

void goForward(){
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1400);
}

void goForwardHash(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  
}

void servoStop(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void mainTurn(){
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


long rcTime(int pin) {
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
