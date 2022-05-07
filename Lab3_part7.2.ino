#include <WiFi.h>
// Configuring for dual core operation. 
static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;

static const int led_pin1 = LED_BUILTIN;
static const int led_pin2 = 6;

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
const char* ssid     = "EN20136956";
const char* password = "12345678";

WiFiServer server(80);

void connect_wifi(void *parameters) {

  Serial.print("Connecting to WiFi ");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  server.begin();

}

void web_server(void *parameters) {
  while (1) {

    WiFiClient client = server.available();

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

              client.print("<Click a href=\"/A\">here</a> to Turn ON the built in LED <br>");
              client.print("<Click a href=\"/B\">here</a> to Turn OFF the built in LED <br>");

              client.print("<Click a href=\"/C\">here</a> to Turn ON the External in LED <br>");
              client.print("<Click a href=\"/D\">here</a> to Turn OFF the External in LED <br>");

              client.println();
              break;

            } else {
              currentLine = "";
            }

          } else if (c != '\r') {
            currentLine += c;
          }

          if (currentLine.endsWith("GET /A")) {
            digitalWrite(led_pin1, HIGH);
          }

          if (currentLine.endsWith("GET /B")) {
            digitalWrite(led_pin1, LOW);
          }

          if (currentLine.endsWith("GET /C")) {
            digitalWrite(led_pin2, HIGH);
          }

          if (currentLine.endsWith("GET /D")) {
            digitalWrite(led_pin2, LOW);
          }
        }
      }

      client.stop();
      Serial.println("Connection Lost ..............");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);

  xTaskCreatePinnedToCore(web_server,
                          "Using the Web Server",
                          2048,
                          NULL,
                          1,
                          &task_2,
                          app_cpu);


  xTaskCreatePinnedToCore(connect_wifi,
                          "Wi-Fi Connection",
                          2048,
                          NULL,
                          2,
                          &task_1,
                          pro_cpu);

  vTaskDelete(NULL);
}

void loop() {
  }
