/*
    Interacting with an ESP8266 Feather Huzzah
    using Telegram Bot
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
char ssid[] = "*******";       // your network SSID (name)
char password[] = "*******";  // your network key

// ------- Telegram config --------
#define BOT_TOKEN "*******"
// Telegram chat IDs, contact @myidbot
#define IDs_SIZE 2
char *chat_ids[IDs_SIZE] = {"264555843", "242452060"};

// SSL client needed for both libraries
WiFiClientSecure client;

// Telegram bot
UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  // initialize HDC1000
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }

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
      for (int i = 0; i < numNewMessages; i++) {
        // check message content
        if ( bot.messages[i].text=="/hello" ) {
          msg = "Hello";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
        if ( bot.messages[i].text=="/who_are_you" ) {
          msg = "I'm an ESP8266 System On Chip";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  }

}

void broadcastTelegramMessage(String msg) {
  for ( int k = 0; k < IDs_SIZE; k++ ) {
    bot.sendMessage(chat_ids[k], msg, "");
  }
  Serial.println("Broadcasting message");
  digitalWrite(LED_PIN, LOW);
}

void sendTelegramMessage(String chat_id, String msg) {
  if (  bot.sendMessage(chat_id, msg, "") ) {
    Serial.println("Message has been sent.");
  }
}
