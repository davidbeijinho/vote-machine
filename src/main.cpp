#include <Arduino.h>

const int LED_RED = D6;
const int LED_YELLOW = D7;
const int LED_GREEN = D8;

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  digitalWrite(LED_RED, HIGH);

  analogWrite(LED_YELLOW, 255);

  analogWrite(LED_GREEN, 255 / 4);
}

void loop()
{
}