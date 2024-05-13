#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

void alert();

const int trigPin = 3;
const int echoPin = 2;

const int activeBuzz = 12;

long int duration = 0;
int distance = 0;

const int rs = 5, e = 6, d0 = 8, d1 = 9, d2 = 10, d3 = 11;

LiquidCrystal lcd(rs, e, d0, d1, d2, d3);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Alert System");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(activeBuzz, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Reset Trig Pin
  digitalWrite(trigPin, LOW);
  delay(2);

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration) * (0.034 / 2.0);

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(600);

  alert();
}

void alert()
{
  
  if(distance < 10)
  {
    lcd.setCursor(0,1);
    lcd.print("Motion Detected");
    digitalWrite(activeBuzz, HIGH);
    delay(500);
    digitalWrite(activeBuzz, LOW);
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("No motion");
  }
}