#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11 
#define LED_PIN 7

// Assign AP ssid / password here
#define _SSID "DaBear"
#define _KEY  "100godbl"

#define SENSOR_READ_PERIOD  2000

// Device object
// Assign device id / key of your test device
MCSDevice mcs("Dl430N0B", "2VU9Lb8ahNjhIH0k");

// Data channel objects (corresponding to the device)
// should be filled with the data channel name given in the prototype
MCSDisplayFloat temperature("tem_1");  
MCSDisplayFloat humidity("hum_1");
MCSControllerOnOff led("led");

DHT dht(DHTPIN, DHTTYPE);
unsigned long last_sensor_read_time;

void setup() {
  // setup Serial output at 9600
  Serial.begin(9600);

  dht.begin();
  // setup Wifi connection
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(_SSID);
    Serial.print(",");
    Serial.print(_KEY);
    Serial.println(")...");
    WiFi.begin(_SSID, _KEY);
  }
  Serial.println("WiFi connected !!");

  // add data channel objects into device object
  mcs.addChannel(temperature);
  mcs.addChannel(humidity);
  mcs.addChannel(led);
  
  // setup LED pin
  pinMode(LED_BUILTIN, OUTPUT);

  // connect to MCS
  while(!mcs.connected())
  { 
    Serial.println("MCS.connect()...");
    mcs.connect();
  }
  Serial.println("MCS connected !!");

  last_sensor_read_time = millis();
}

void loop() {
  // call process() to allow background processing, add timeout to avoid high cpu usage
  //Serial.print("process(");
  //Serial.print(millis());
  //Serial.println(")");
  mcs.process(100);

  if(millis() - last_sensor_read_time >= SENSOR_READ_PERIOD) {
    last_sensor_read_time = millis();
    // Read humidity and temperature values from DHT sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  
    // the value of each data channel object
    humidity.set(h);
    temperature.set(t);
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
  
  // Check the status of on/off controller. 
  // If the status is different from the previous value, update the LED status
  if(led.updated())
    {
      Serial.print("LED updated, new value = ");
      Serial.println(led.value());
      digitalWrite(LED_PIN, led.value() ? HIGH : LOW);
    }
    
  // check if need to re-connect
  while(!mcs.connected())
  {
    Serial.println("re-connect to MCS...");
    mcs.connect();
    if(mcs.connected())
      Serial.println("MCS connected !!");
  }

}
