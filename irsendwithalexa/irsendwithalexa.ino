/*
   This is a basic example on how to use Espalexa and its device declaration methods.
   This code is edited for controlling 4 Appliances by
   Sachin Soni 
   for techiesms YouTube channel 
   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves
   YouTube Channel :- https://www.youtube.com/techiesms
          techiesms
   explore | learn | share
*/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 21;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

//#define R1 15
//#define R2 2
//#define R3 4
//#define R4 22

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);


// Change this!!

// WiFi Credentials
const char* ssid = "2G_REDELUZ";
const char* password = "xxx";

// device names
String Device_1_Name = "tv";


boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  irsend.begin();
//#if ESP8266
//Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
//#else  // ESP8266
//Serial.begin(115200, SERIAL_8N1);
//#endif  // ESP8266
  Serial.begin(115200);

 // pinMode(R1, OUTPUT);
  //pinMode(R2, OUTPUT);
  //pinMode(R3, OUTPUT);
  //pinMode(R4, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off

    espalexa.begin();
    

  }

  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}


//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      irsend.sendNEC(0xE0E040BF);
      Serial.println("ligando");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    irsend.sendNEC(0xE0E040BF);
    Serial.println("desligando tv");
  }
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;


}
