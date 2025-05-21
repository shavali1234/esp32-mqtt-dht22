#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define Width 128
#define Height 64
#define reset -1

#define dht22 15
double temperature, humidity;
char temp[10], hum[10];

const char* ssid = "******";//your wifi name
const char* pssd = "******";//your wifi password

const char* host = "192.168.0.104";//your host machine ip where mqtt broker is installed
const int port = 1883;
const char* topic_temp = "sensor/data/temperature";
const char* topic_hum = "sensor/data/humidity";

Adafruit_SH1106G oled = Adafruit_SH1106G(Width, Height, &Wire, -1);

DHT dht(dht22, DHT22);


WiFiClient client;
PubSubClient espclient(client);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  oled.begin(0x3c, true);
  oled.clearDisplay();
  oled.display();
  delay(100);
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);

  dht.begin();
  delay(500);


  WiFi.begin(ssid, pssd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());

  espclient.setServer(host, port);
  espclient.setCallback(callback);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!espclient.connected()) {
    reconnect();
  }
  espclient.loop();

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.print("   ");
  Serial.print("Humidity:");
  Serial.println(humidity);


  dtostrf(temperature, 3, 2, temp);
  dtostrf(humidity, 3, 2, hum);
  espclient.publish(topic_temp, temp);
  espclient.publish(topic_hum, hum);


  oled.setCursor(0, 0);
  oled.print("Temperature: ");
  oled.println(temperature);
  oled.print("Humidty: ");
  oled.println(humidity);
  oled.display();
  delay(2000);
  oled.clearDisplay();
}

void reconnect() {
  while (!espclient.connected()) {
    Serial.println("Attempt to connect Mqtt Broker");

    if (espclient.connect("espclient")) {
      Serial.println("Mqtt broker connected");
      dtostrf(temperature, 3, 2, temp);
      dtostrf(humidity, 3, 2, hum);
      espclient.publish(topic_temp, temp);
      espclient.publish(topic_hum, hum);
    } else {
      Serial.println("Failed to connect");
      Serial.println(espclient.state());
    }
    delay(1000);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived");
  Serial.println(topic);
  Serial.print(":");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
