# Temp-Bot
Interactive ESP8266 remote temperature sensor, controlled using Telegram Bot.
We use an ESP8266 NodeMCU together with a TMP36 temperature in order to retrieve temperature data.
The user can interact with the remote device using Telegram Bot API.

based on Telegram Library by Brian laugh
https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

## Installing drivers and the Arduino IDE
First of all, you need to install th USB driver for the CP2104 USB-to-Serial chip,
see [link](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx).

Then install the [Arduino IDE](http://www.arduino.cc/en/Main/Software).

Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field in the Arduino v1.6.4+ preferences.
Next, use the Board manager to install the ESP8266 package.
When you've restarted, select NodeMCU 0.9 (ESP-12 Module) from the Tools->Board dropdown, 80 MHz as the CPU frequency, and for Upload Speed, select 115200 baud; finally select the matching COM port for your  USB-Serial cable.

## NodeMCU pin layout
https://pradeepsinghblog.files.wordpress.com/2016/04/nodemcu_pins.png

## LED blinking
Test that everything is working as expected by completing the code to make an LED blink, see exercises/LST-01-ex-led-blink.ino

## Sensing Temperature using TMP36
Using the TMP36 is easy, simply connect the left pin to power (2.7-5.5V) and the right pin to ground. Then the middle pin will have an analog voltage that is directly proportional (linear) to the temperature, i.e.<br/>
Temp in °C = [(Vout in mV) - 500] / 10  
To read temperature using an Arduino-like board powered at 3.3V:  
voltage at pin in milliVolts = (reading from ADC) * (3.3/1024)  
this formula converts the number 0-1023 from the ADC into 0-3.3V.
then, to convert volts into temperature, use this formula:  
Centigrade temperature = [(analog voltage in V) - 0.5] * 100

Scaricare il codice che trovate in exercises/LST-02-ex-reading-temperature-sensor.ino e completarlo affinché si possa misurare anche l'umidità.

## Telegram Bot
_Bots are simply Telegram accounts operated by software – not people – and they'll often have AI features._
To create a new Bot you can ask __\@BotFather__. A new Bot has been created for you, that is __\@bl_esp8266_bot__ which has the corresponding API token.
In order to talk with the Bot you need to know your Telegram chat ID, by contacting __\@myidbot__ and sending the command _/getid_.

### Install Telegram library
Install the ArduinoJson library written by Benoît Blanchon and the Universal Telegram Bot Library.
Sketch > #include libreria > Aggiungi libreria da file .ZIP
Scaricare il codice t-bot.ino e configurare Telegram Bot e i parametri di rete WiFi.
Modificare il codice aggiungendo altre funzioni di interazione con l'utente.

### Interacting with the Bot
Scaricare il codice che trovate in
exercises/LST-03-ex-telegram-bot.ino
e modificarlo creando nuove azioni a cui il bot possa rispondere.

## Interactive remote temperature sensor controlled using Telegram Bot.
