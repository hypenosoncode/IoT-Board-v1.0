#define BLYNK_TEMPLATE_ID "TMP****"
#define BLYNK_DEVICE_NAME "IoT Board"
#define BLYNK_AUTH_TOKEN "**********"
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wi-Fi Name";
char pass[] = "Wi-Fi Password";
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
int soilMoistureCrop = 0;

BlynkTimer timer;

#define SensorPin 27
#define relay1_pin 32
#define relay2_pin 33
#define relay3_pin 34
#define relay4_pin 35

int relay1_state = 0;
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;


BLYNK_WRITE(V0) {
  relay1_state = param.asInt();
  if(relay1_state == 1)
  { 
    digitalWrite(relay1_pin, HIGH);
    Serial.println(relay1_state);
  }
  if(relay1_state == 0)
  {
     digitalWrite(relay1_pin, LOW);
     Serial.println(relay1_state);
  }
}
//--------------------------------------------------------------------------

BLYNK_WRITE(V2) {
   relay2_state = param.asInt();
  if(relay2_state == 1)
  { 
    digitalWrite(relay2_pin, HIGH);
    Serial.println(relay2_state);
  }
  if(relay2_state == 0)
  {
     digitalWrite(relay2_pin, LOW);
     Serial.println(relay2_state);
  }
}
//--------------------------------------------------------------------------

BLYNK_WRITE(V3) {
   relay3_state = param.asInt();
  if(relay3_state == 1)
  { 
    digitalWrite(relay3_pin, HIGH);
    Serial.println(relay3_state);
  }
  if(relay3_state == 0)
  {
     digitalWrite(relay3_pin, LOW);
     Serial.println(relay3_state);
  }
}
//--------------------------------------------------------------------------

BLYNK_WRITE(V4) {
   relay4_state = param.asInt();
  if(relay4_state == 1)
  { 
    digitalWrite(relay4_pin, HIGH);
    Serial.println(relay4_state);
  }
  if(relay4_state == 0)
  {
     digitalWrite(relay4_pin, LOW);
     Serial.println(relay4_state);
  }
}
//--------------------------------------------------------------------------


void setup()
{

  Serial.begin(115200);
  delay(100);
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
  timer.run();
  sendSensor();
}

void sendSensor() {
  
soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
soilMoistureCrop = soilMoistureValue/100;
  Serial.print(soilMoistureCrop);
  Serial.println("%");
  Blynk.virtualWrite(V6, soilMoistureCrop);
  delay(250);
}