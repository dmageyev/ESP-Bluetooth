#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11

#include <WiFi.h>

const char* ssid = "ssid";
const char* password = "pass";

WiFiServer server(80);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

char index_html_head[] = R"(
<html>
<head>
  <title></title>
</head>
<body>
  <h1 style="color:red;"><b>Temperature</b></h1>
)";

char index_hum[] = R"(
  <h1 style="color:blue;"><b>Humidity</b></h1>
)";

char index_html_bot[] = R"(
</body>
</html>
)";

void loop() {
  WiFiClient client = server.available();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Not Connected");
    return;
  }

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print(index_html_head);
            client.print("<h1>" + String(t) + "</h1>");
            client.print(index_hum);
            client.print("<h1>" + String(h) + "</h1>");
            client.print(index_html_bot);

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } 
        else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
