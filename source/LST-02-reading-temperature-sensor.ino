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
  float v = value * (3.3/1024); // value in V
  float temp = ( v - 0.5 ) * 100;  // converting from volts to degrees
  msg = "Temperature: " + String(temp) + "°C";
  Serial.println(msg);
  delay(1000);
}
