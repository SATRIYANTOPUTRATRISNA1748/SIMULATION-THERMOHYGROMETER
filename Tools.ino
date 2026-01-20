//You can fill with your API Cloud(i suggest you with blynk)\
// For library you can choose dht 22 and fil "Blynk@wokwi:ff31ef6c8e4f64cd5acd23b415d84f7e5555fc1f"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your network for method LAN
char ssid[] = "Name"; 
char pass[] = "Password"; 

#define DHTPIN 5          // Mention the digital pin where you connected 
#define DHTTYPE DHT22     // DHT 11  
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void setup(){
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(CHANGE YOUR BUTTON CODE, h);
  Blynk.virtualWrite(CHANGE YOUR BUTTON CODE, t);
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print("    Humidity : ");
  Serial.println(h);


  if(t > 30){
   // Blynk.email("isamahfudi08@gmail.com", "Alert", "Temperature over 28C!");
    Blynk.logEvent("temp_alert","Temp above 30 degrees");
  }
}
