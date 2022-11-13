
#include <SoftwareSerial.h>

//#include <TinyGPS.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L call
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


//char Number;
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor) for call
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
 mySerial.println("ATD+ +254741606811;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
   Serial.println("Initializing...");
  delay(1000);
  
//Second emaergency contact
  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
 mySerial.println("ATD+ +254733695601;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
  
//Begin serial communication with Arduino and Arduino IDE (Serial Monitor) for sms
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+254741606811\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Hello am in danger urgently need help.I am here https://maps.google.com/maps?q=-1.344690,36.727893"); //text content
  updateSerial();
  mySerial.write(26);
    mySerial.begin(9600);
    
//  Second emergency contact mesasge
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+254733695601\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Hello am in danger urgently need help.I am here https://maps.google.com/maps?q =-1.344690,36.727893"); //text content
  updateSerial();

 
  //Begin serial communication with Arduino and GPS(Serial Monitor) for location
  Serial.println("Initializing...");
  delay(1000);
   Serial.begin(9600);
  ss.begin(GPSBaud);
//
//   Serial.begin(9600);
//  delay(2000);
//  Serial.println("Type Number");

}
void loop()
   {
   // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
    }
  }
//     if(Serial.available()){
//      Number = Serial.read();
//      Serial.print(Number);
//    }


}
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  Serial.println();
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
