#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#define URL "https://lapin.cloud/api/wifi.php"

#define WIFI_SSID "brisa-1774780"
#define WIFI_PASS "anjxa2ay"


void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS, 6);
  WiFi.mode(WIFI_STA);

  // Espera enquanto tenta conectar
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }


  // Conectado
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("conectado");
    WiFiClientSecure client;
    HTTPClient http;

    client.setInsecure();
    
    
    http.begin(client, URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Request para o LAPIN
    int httpResponseCode = http.POST("rssi=-1&canal=6&lat=-3.7688616&lon=-38.4785713");
    
    if (httpResponseCode > 0) {
      Serial.println(httpResponseCode);
      String payload_response = http.getString();
      Serial.println(payload_response);
    } else {
      Serial.println("error");
      Serial.println(httpResponseCode);
      Serial.println(http.errorToString(httpResponseCode));
    }
    http.end();
  }


}
void loop() {
}



