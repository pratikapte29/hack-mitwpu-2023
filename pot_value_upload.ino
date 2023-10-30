//#include <Adafruit_ESP8266.h>

#define POTENTIOMETER_PIN A0
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "ORTHANC";   // your network SSID (name) 
const char* password = "1223334444";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2049964;
const char * myWriteAPIKey = "60RJ40I9TXR2YSZC";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 150;

//variable to write pot readings to thingspeak
float pot_reading;

void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new potentiometer reading
    pot_reading = analogRead(POTENTIOMETER_PIN);
    Serial.print("Potentiometer value = ");
    Serial.println(pot_reading);
    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, pot_reading, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
