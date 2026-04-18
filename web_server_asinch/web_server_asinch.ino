#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "Robocode";
const char* password = "hacatrone18";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Error SPIFFS");
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Added a small delay to avoid spamming the console
    Serial.println("Connecting to WiFi..");
  }

  // Print local IP address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Start server
  server.begin();
}

void loop() {
  // ESPAsyncWebServer doesn't require a handleClient() call in the loop!
}
