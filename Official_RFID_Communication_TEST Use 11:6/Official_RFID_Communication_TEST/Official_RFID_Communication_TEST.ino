#define BUFSIZE    15  // Size of receive buffer (in bytes) (10-byte unique ID + null character)
#define RFID_START  0x02  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x03


void setup()  // Set up code called once on start-up
{

  pinMode(3, OUTPUT);   //set pin 3 as output
  digitalWrite(3,LOW);
  Serial2.begin(9600); 

  
  // setup Arduino Serial Monitor
  Serial.begin(9600);  // Inintialize the serial monitor port
  while (!Serial);   // wait until ready
  Serial.println("RFID Card Reader");
    
  Serial1.begin(9600); // Inintialize the RFID serial port

  Serial.flush();   // wait for all bytes to be transmitted to the Serial Monitor
}

void loop()  // Main code, to run repeatedly
{
  char rfidData[BUFSIZE];  // Buffer for incoming data
  char offset = 0;         // Offset into buffer
  rfidData[0] = 0;         // Clear the buffer    
  while(1) //Loop that waits for a tag to be read
  {
    if (Serial1.available() > 0) // If there are any bytes available to read, then the RFID Reader has probably seen a valid tag
    {
      rfidData[offset] = Serial1.read();  // Get the byte and store it in our buffer
      if (rfidData[offset] == RFID_START)    // If we receive the start byte from the RFID Reader, then get ready to receive the tag's unique ID
      {
        offset = -1;     // Clear offset (will be incremented back to 0 at the end of the loop)
      }
      else if (rfidData[offset] == RFID_STOP)  // If we receive the stop byte from the RFID Reader, then the tag's entire unique ID has been sent
      {
        rfidData[offset] = 0; // Null terminate the string of bytes we just received
        //COMUNICATION CODE
        Serial2.write('J');
        digitalWrite(3, HIGH);
        delay(2000);
        digitalWrite(3, LOW);
        break;                // Break out of the loop
      }
          
      offset++;  // Increment offset into array
      if (offset >= BUFSIZE) offset = 0; // If the incoming data string is longer than our buffer, wrap around to avoid going out-of-bounds
    }
  }

  Serial.println(rfidData);       // The rfidData string should now contain the tag's unique ID with a null termination, so display it on the Serial Monitor
  Serial.flush();                 // Wait for all bytes to be transmitted to the Serial Monitor
}
