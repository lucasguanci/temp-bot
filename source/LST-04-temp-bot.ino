/*
    Control a remote HDC1008 temperature and humidity sensor
    using ESP8266 Feather Huzzah and Telegram Bot
    based on Telegram Library by Brian laugh
    https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

    created by Luca Sguanci <luca.sguanci@gmail.com>
    10 Mar 2017
    GPL license.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Wire.h>

//------- WiFi Settings -------
char ssid[] = "******";       // your network SSID (name)
char password[] = "******";  // your network key

// ------- Telegram config --------
#define BOT_TOKEN "376233909:AAGcCra1I50H1bcWON8ckpyE3bNOLIQbqx0"
// Telegram chat IDs, contact @myidbot
#define IDs_SIZE 2
char *chat_ids[IDs_SIZE] = {};

// SSL client needed for both libraries
WiFiClientSecure client;

// Telegram bot
UniversalTelegramBot bot(BOT_TOKEN, client);

// temperature sensor
const int inputPin  = A0;

String ipAddress = "";

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done


void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

}

void loop() {
  // wait for messages
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    String msg = "";
    while (numNewMessages) {
      Serial.println("got message");
      for (int i = 0; i < numNewMessages; i++) {
        // check message content
        if ( bot.messages[i].text=="/TEMP" ) {
          msg = readTemperature();
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}

void sendTelegramMessage(String chat_id, String msg) {
  if (  bot.sendMessage(chat_id, msg, "") ) {
    Serial.println("Message has been sent.");
  }
  delay(100);
}

String readTemperature() {
  String msg = "";
  int value = analogRead(inputPin);
  float v = value * (3.3/1024); // value in V
  float temp = ( v - 0.5 ) * 100;  // converting from volts to degrees
  msg = "Temperature: " + String(temp) + "°C";
  Serial.println(msg);
  return msg;
}
