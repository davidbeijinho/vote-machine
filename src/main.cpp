#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

AsyncWebServer server(80);

const int LED_GREEN = D6;
const int LED_YELLOW = D7;
const int LED_RED = D8;

const int MAX_POWER = 255;
const int VOTE_OPTIONS = 3;

int VOTES[VOTE_OPTIONS] = {0, 0, 0};

const int INDEX_GREEN = 0;
const int INDEX_YELLOW = 1;
const int INDEX_RED = 2;

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    WiFi.begin(ENV_SSID, ENV_PASSWORD);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    if (SPIFFS.begin())
    {
        Serial.println("SPIFFS Initialize");
    }
    else
    {
        Serial.println("SPIFFS Failed");
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });
    server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.js");
    });
    server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.css");
    });

    server.on("/vote/green", HTTP_GET, [](AsyncWebServerRequest *request) {
        VOTES[INDEX_GREEN] += 1;
        request->send(200, "application/json", "{\"color\":\"GREEN\",\"status\":1}");
    });
    server.on("/vote/yellow", HTTP_GET, [](AsyncWebServerRequest *request) {
        VOTES[INDEX_YELLOW] += 1;
        request->send(200, "application/json", "{\"color\":\"YELLOW\",\"status\":1}");
    });
    server.on("/vote/red", HTTP_GET, [](AsyncWebServerRequest *request) {
        VOTES[INDEX_RED] += 1;
        request->send(200, "application/json", "{\"color\":\"RED\",\"status\":1}");
    });

    server.onNotFound(notFound);

    server.begin();
}

int getMaxVotes()
{
    int max = VOTES[0];
    for (int i = 1; i < VOTE_OPTIONS; i++)
    {
        if (max < VOTES[i])
        {
            max = VOTES[i];
        }
    }
    return max;
}

float calculatePower(int index, int max)
{
    return ((float)VOTES[index] / (float)max) * MAX_POWER;
}

void loop()
{
    const int maxVotes = getMaxVotes();

    if (maxVotes != 0)
    {
        analogWrite(LED_GREEN, calculatePower(INDEX_GREEN, maxVotes));
        analogWrite(LED_YELLOW, calculatePower(INDEX_YELLOW, maxVotes));
        analogWrite(LED_RED, calculatePower(INDEX_RED, maxVotes));
    }

    delay(1000);
}
