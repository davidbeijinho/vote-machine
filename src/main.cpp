#include <Arduino.h>
#include <ESP8266WiFi.h>

// const char* ssid = "SSID_NAME";
// const char* password = "PASSWORD";

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ENV_SSID, ENV_PASSWORD);

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
}