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

//version trying to use ir_samsung lib 

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Samsung.h>

const uint16_t kIrLed = 21;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
IRSamsungAc ac(kIrLed);

//samsung ac
uint8_t AcOn[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};
// samsung ac on raw
uint16_t AcOnn[349] = {578, 17940,  3002, 8978,  520, 480,  518, 1502,  492, 504,  490, 508,  490, 508,  490, 506,  492, 506,  492, 504,  522, 476,  520, 1474,  520, 478,  520, 478,  520, 1476,  520, 478,  520, 478,  518, 1478,  518, 1504,  490, 1504,  468, 1526,  494, 1502,  494, 504,  520, 478,  520, 478,  518, 478,  520, 478,  520, 478,  518, 480,  518, 478,  518, 478,  518, 480,  518, 480,  516, 480,  516, 506,  492, 506,  492, 504,  492, 530,  468, 506,  492, 506,  494, 504,  518, 478,  520, 478,  520, 476,  520, 478,  518, 478,  522, 476,  520, 478,  518, 482,  516, 482,  516, 484,  512, 480,  516, 506,  494, 504,  492, 1502,  492, 1502,  492, 1504,  520, 1476,  518, 2988,  3002, 8974,  520, 1476,  520, 478,  520, 478,  522, 476,  524, 476,  518, 478,  518, 530,  466, 506,  492, 504,  494, 1504,  492, 504,  492, 506,  492, 1502,  520, 480,  518, 1476,  522, 1472,  520, 1474,  520, 1478,  518, 1478,  516, 1504,  492, 504,  492, 506,  466, 532,  490, 506,  490, 506,  494, 502,  520, 478,  522, 476,  520, 478,  518, 478,  520, 478,  518, 480,  520, 478,  518, 480,  518, 478,  518, 480,  516, 480,  518, 504,  492, 506,  492, 504,  492, 506,  492, 506,  492, 506,  492, 504,  518, 478,  520, 478,  518, 480,  518, 478,  518, 478,  520, 478,  518, 480,  518, 478,  518, 480,  518, 480,  520, 478,  518, 504,  492, 2986,  3002, 9002,  468, 1528,  494, 504,  494, 504,  494, 504,  520, 476,  520, 478,  520, 478,  522, 476,  520, 478,  520, 1476,  520, 480,  516, 480,  518, 478,  520, 478,  518, 1502,  492, 1504,  492, 506,  492, 1502,  494, 1500,  520, 1476,  520, 1476,  520, 1476,  520, 1476,  518, 1480,  518, 1476,  518, 504,  494, 504,  492, 506,  492, 1504,  492, 1504,  494, 1502,  520, 478,  518, 480,  518, 478,  520, 478,  520, 476,  520, 1476,  520, 1476,  518, 480,  518, 480,  516, 1504,  492, 506,  468, 1526,  494, 1502,  494, 504,  520, 476,  520, 478,  520, 476,  518, 478,  520, 478,  520, 478,  518, 480,  518, 1476,  518, 1478,  518, 1502,  494, 1502,  520};

// samsung ac off raw
uint16_t AcOff[349] = {578, 17940,  3026, 8974,  520, 478,  520, 1476,  520, 478,  518, 478,  520, 478,  518, 478,  520, 478,  518, 480,  518, 480,  518, 1502,  494, 504,  492, 504,  492, 1504,  492, 1502,  492, 504,  520, 1476,  520, 1476,  520, 1476,  520, 1474,  520, 1476,  518, 480,  518, 480,  518, 506,  492, 506,  490, 506,  466, 530,  492, 506,  492, 504,  510, 486,  522, 476,  520, 478,  520, 496,  502, 478,  518, 478,  520, 478,  520, 478,  520, 478,  518, 480,  518, 480,  518, 530,  466, 506,  494, 504,  468, 530,  492, 504,  492, 506,  492, 504,  494, 504,  520, 478,  520, 478,  520, 476,  522, 476,  520, 476,  520, 478,  520, 478,  520, 1476,  520, 1476,  518, 2986,  3002, 9002,  492, 1502,  516, 482,  490, 506,  494, 504,  494, 504,  520, 476,  520, 478,  522, 500,  496, 478,  520, 1474,  520, 478,  520, 478,  518, 1476,  520, 480,  518, 1502,  494, 1502,  492, 1504,  492, 1502,  494, 1502,  520, 1476,  518, 478,  520, 478,  520, 476,  520, 476,  520, 478,  520, 476,  518, 480,  518, 478,  518, 478,  518, 504,  492, 504,  492, 506,  492, 506,  494, 504,  492, 504,  518, 478,  520, 476,  522, 476,  518, 478,  520, 476,  520, 478,  520, 478,  522, 476,  520, 478,  518, 480,  518, 480,  516, 506,  492, 504,  494, 504,  466, 530,  492, 506,  490, 506,  492, 504,  494, 504,  520, 478,  518, 480,  520, 2986,  3002, 8974,  520, 1476,  520, 476,  520, 478,  520, 478,  520, 478,  518, 480,  518, 504,  496, 502,  492, 506,  490, 1504,  494, 504,  494, 504,  518, 480,  518, 1476,  522, 1474,  520, 1500,  496, 476,  520, 1476,  520, 1476,  516, 1506,  492, 1502,  466, 1528,  494, 1502,  494, 1500,  520, 1476,  520, 478,  520, 478,  520, 476,  518, 1478,  518, 1478,  518, 1478,  516, 480,  518, 504,  494, 504,  492, 506,  492, 506,  492, 1504,  494, 1502,  520, 478,  520, 478,  518, 1476,  518, 478,  518, 1476,  520, 1476,  520, 478,  520, 478,  518, 482,  516, 504,  494, 504,  516, 482,  490, 508,  492, 504,  492, 504,  492, 504,  518, 1476,  522, 1474,  520};

//#define R1 15
//#define R2 2
//#define R3 4
//#define R4 22

// prototypes
boolean connectWifi();

//callback functions
void tvon(uint8_t on);
void acon(uint8_t on);
void acoff(uint16_t off);

// Change this!!

// WiFi Credentials
const char* ssid = "2G_REDELUZ";
const char* password = "net16luz";

// choose the name alexa will respond to
String Device_1_Name = "tv";
String Device_2_Name = "ar";


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
    espalexa.addDevice(Device_1_Name, tvon); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, acon); //simplest definition, default state off
   // espalexa.addDevice(Device_2_Name, acoff); //simplest definition, default state off

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
// tv on off
void tvon(uint8_t on)
{
  //Control the device
  if (on)
  {
    delay(100);
    irsend.sendNEC(0xE0E040BF);
    Serial.println("ligando tv");
    
  }
  else
  {
    delay(100);
    irsend.sendNEC(0xE0E040BF);
    Serial.println("desligando tv");
  }
}

// ac on
void acon(uint8_t on)
{
  //Control the device
  if (on)
  {
    delay(100);
    ac.on();
    //irsend.sendSamsungAC(AcOn);
    //irsend.sendRaw(AcOnn,349,38);
    //delay(10);
    //irsend.sendRaw(AcOnn,349,38);
    //delay(10);
    //irsend.sendRaw(AcOnn,349,38);    
    //Serial.println("ligando ar");
    
  }
  else
  {
    delay(100);
    ac.off();
    //irsend.sendRaw(AcOff,349,38);
    //delay(10);
    //irsend.sendRaw(AcOff,349,38);
    //delay(10);
    //irsend.sendRaw(AcOff,349,38);  
    Serial.println("desligando ar");
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
