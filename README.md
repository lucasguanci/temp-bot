# Temp-Bot
Interactive ESP8266 remote temperature/humidity sensor, controlled using Telegram Bot.
We use an ESP8266 Feather Huzzah by Adafruit together with an Adafruit HDC1008 temperature and humidity sensor breakout board to retrieve temperature and humidity data.
The user can interact with the remote device using Telegram Bot API.

based on Telegram Library by Brian laugh
https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

## Installing drivers and the Arduino IDE
First of all, you need to install th USB driver for the CP2104 USB-to-Serial chip,
see [link](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx).

Then install the [Arduino IDE](http://www.arduino.cc/en/Main/Software).

Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field in the Arduino v1.6.4+ preferences.
Next, use the Board manager to install the ESP8266 package.
When you've restarted, select Adafruit HUZZAH ESP8266  from the Tools->Board dropdown, 80 MHz as the CPU frequency, and for Upload Speed, select 115200 baud; finally select the matching COM port for your  USB-Serial cable.

## LED blinking
Test that everything is working as expected by writing the code to make  an LED blink.

## Sensing Temperature and Humidity using HDC1008
Install the Adafruit_HDC1000 library
Sketch > #include libreria > Aggiungi libreria da file .ZIP
Lo sketch temp-sensor-exercise.ino permette di visualizzare sul monitor seriale la misura della temperatura al premere di un tasto sulla breadboard.
Scaricare il codice temp-sensor-exercise.ino e completarlo affinché si possa misurare anche l'umidità.

## Telegram Bot
Install the ArduinoJson library written by Benoît Blanchon and the Universal Telegram Bot Library.
Sketch > #include libreria > Aggiungi libreria da file .ZIP
Scaricare il codice t-bot.ino e configurare Telegram Bot e i parametri di rete WiFi.
Modificare il codice aggiungendo altre funzioni di interazione con l'utente.

## Interactive remote temperature/humidity sensor controlled using Telegram Bot.
