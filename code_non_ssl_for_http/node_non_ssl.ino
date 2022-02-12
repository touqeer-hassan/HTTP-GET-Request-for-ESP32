#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPass";
 
void setup() {
 
  Serial.begin(115200);
  delay(1000);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://sif.systems/pump.php?id=1"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(5000);
}
