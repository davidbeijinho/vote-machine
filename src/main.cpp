#include <Arduino.h>
#include <FS.h>

void setup()
{
    Serial.begin(115200);

    bool formatted = SPIFFS.format();
    if (formatted)
    {
        Serial.println("\n\nSuccess formatting");
    }
    else
    {
        Serial.println("\n\nError formatting");
    }
}

void loop()
{
}