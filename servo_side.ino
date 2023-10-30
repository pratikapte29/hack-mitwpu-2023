#define servo_pin D2
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myServo;

const char ssid[] = "Melange";  // your network SSID (name)
const char pass[] = "Melange@2";   // your network password         
WiFiClient  client;

//---------Channel Details---------//
unsigned long counterChannelNumber = 2049964;            // Channel ID
const char * myCounterReadAPIKey = "7H6V1T81386XKCKI"; // Read API Key
const int FieldNumber1 = 1;  // The field you wish to read
//-------------------------------//

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  myServo.attach(servo_pin);
}

void loop()
{
  //----------------- Network -----------------//
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
  //--------- End of Network connection--------//

  //---------------- Channel 1 ----------------//
  long pot_reading = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("pot_reading: ");
    Serial.println(pot_reading);
    servo_val = 180 * pot_reading / 1024;
    myServo.write(servo_val);
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
  //-------------- End of Channel 1 -------------//
