#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(10, 11); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

 // Serial.println("Initializing...");
  //delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"safaricom\"\r\n"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"USER\",\"saf\"\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"PWD\",\"data\"\r\n"); 
  updateSerial();
  mySerial.println("AT+SAPBR=1,1\r\n"); 
  updateSerial();
mySerial.println("AT+SAPBR=2,1\r\n"); 
  updateSerial();
  mySerial.println("AT+HTTPINIT\r\n"); 
  updateSerial();
  delay(1000);
  mySerial.println("AT+HTTPPARA=\"CID\",1\r\n"); 
  updateSerial();
  delay(1000);
  mySerial.println("AT+HTTPPARA=\"URL\",\"www.fedha.ke/http/insert.php?count=19\"\r\n"); 
  updateSerial();
  delay(1000);
  mySerial.println("AT+HTTPACTION=0\r\n"); 
  updateSerial();
  delay(1000);
  mySerial.println("AT+HTTPREAD\r\n"); 
  updateSerial();
  delay(50000);
  mySerial.println("AT+HTTPTERM\r\n"); 
  updateSerial();
  delay(1000);
  mySerial.println("AT+SAPBR=0,1\r\n"); 
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
