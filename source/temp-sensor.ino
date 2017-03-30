/*
    Control a remote HDC1008 temperature and humidity sensor
    using ESP8266 Feather Huzzah
*/

#include <Wire.h>
#include <Adafruit_HDC1000.h>

// Adafruit HDC1000 temp/humidity sensor
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

// variables for reading the pushbutton status
int tempButtonState = 0;
int humButtonState = 0;

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  // initialize HDC1000
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  // GPIO
  // temperature button
  pinMode(12, INPUT);
  // humidity button
  pinMode(13, INPUT);
}

void loop() {

  // local variables
  double temp, hum;

  // read the state of the pushbutton value (HIGH or LOW)
  tempButtonState = digitalRead(12);
  humButtonState = digitalRead(13);

  // check if the pushbuttons are pressed
  if ( tempButtonState == HIGH ) {
    // read and display temperature
    temp = hdc.readTemperature();
    msg = "Temperature: " + String(temp) + "°C";
    Serial.println(msg);
  }
  if ( humButtonState == HIGH ) {
    // read and display humerature
    hum = hdc.readHumidity();
    msg = "Humidity: " + String(hum);
    Serial.println(msg);
  }
}
