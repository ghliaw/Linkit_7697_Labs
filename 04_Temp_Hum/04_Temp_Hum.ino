#include "DHT.h"

#define DHTPIN A0     // what pin we're connected to
#define TEMP_LIMIT  30.0
#define HUM_LIMIT   40.0
#define LED_TEMP  2
#define LED_HUM   3

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
    Serial.begin(9600); 
    pinMode(LED_TEMP, OUTPUT);
    pinMode(LED_HUM, OUTPUT);
    
    Serial.println("DHTxx test!");
    dht.begin();
}

void loop() 
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.println(" *C");
        // if value > limit, LED on; else LED off
        if(t >= TEMP_LIMIT)
          digitalWrite(LED_TEMP, HIGH);
        else
          digitalWrite(LED_TEMP, LOW);
        if(h >= HUM_LIMIT)
          digitalWrite(LED_HUM, HIGH);
        else
          digitalWrite(LED_HUM, LOW);
    }
    delay(2000);
}
