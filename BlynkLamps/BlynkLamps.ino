#define BLYNK_PRINT Serial

int pin        = 21;

//#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor

#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 4
DHT dht(dht_dpin, DHTTYPE); 

typedef enum HomeLamps_e 
{
  EHOMELAMPS_MIN = 0,
  EHOMELAMPS_KITCHEN = EHOMELAMPS_MIN,
  EHOMELAMPS_BEDROOM,
  EHOMELAMPS_LIVINGROOM,
  EHOMELAMPS_CORRIDOR,
  EHOMELAMPS_ALARM_ACTIVE,
  EHOMELAMPS_ALARM_TRIGGERED,
  EHOMELAMPS_MAX
} HomeLamps_t;

bool isLampStateOn[EHOMELAMPS_MAX] = { false, false, false, false, false, false};
const int lampPins[EHOMELAMPS_MAX] = { 19, 18, 15, 2, 23, 5};

//const int PIN_ADC_I = 34; // D34

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid     = "";
const char* pass = "";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, millis() / 1000);
  dht.begin();
  float h = dht.readHumidity();
  float t = dht.readTemperature();  
  delay(100);
  Blynk.virtualWrite(V4, t);
  Blynk.virtualWrite(V5, h);
  delay(100);
  update_Lcd(isLampStateOn, t, h);
}

void setup() {  
  for ( unsigned int index = EHOMELAMPS_MIN; index < EHOMELAMPS_MAX ; index++ )
  {
      pinMode(lampPins[index], OUTPUT);
      digitalWrite(lampPins[index], LOW);
  }
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin(auth, ssid, pass);

// Setup a function to be called every second
  timer.setInterval(5000L, myTimerEvent);

  init_Lcd();
}

void loop(){
    Blynk.run();
    timer.run(); // Initiates BlynkTimer    
}
