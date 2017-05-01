/*
    Control a remote TMP36 temperature and humidity sensor
    using NodeMCU ESP8266
*/

const int inputPin  = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  String msg = "";
  // put your main code here, to run repeatedly:
  int value = analogRead(inputPin);
  float v = ..  // valore letto in Volt
  float temp = ..  // convertire i Volt in gradi Celsius
  msg = "Temperature: " + String(temp) + "°C";
  Serial.println(msg);
  delay(1000);
}
