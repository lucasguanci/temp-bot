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
#include <Adafruit_HDC1000.h>

//------- WiFi Settings -------
char ssid[] = "MLV";       // your network SSID (name)
char password[] = "napoleone";  // your network key

#define TELEGRAM_BUTTON_PIN 13
#define LED_PIN 15
#define LED_OB 0

// ------- Telegram config --------
#define BOT_TOKEN "376233909:AAGcCra1I50H1bcWON8ckpyE3bNOLIQbqx0"
// Telegram chat IDs, contact @myidbot
#define IDs_SIZE 2
char *chat_ids[IDs_SIZE] = {"264555843", "242452060"};

// SSL client needed for both libraries
WiFiClientSecure client;

// Telegram bot
UniversalTelegramBot bot(BOT_TOKEN, client);
// Adafruit HDC1000 temp/humidity sensor
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

String ipAddress = "";

volatile bool telegramButtonPressedFlag = false;
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

void setup() {

  Serial.begin(115200);

  // Initialize the buttons
  pinMode(TELEGRAM_BUTTON_PIN, INPUT);
  pinMode(LED_OB, OUTPUT);
  digitalWrite(LED_OB, HIGH);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // initialize HDC1000
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }

  // NOTE:
  // It is important to use interupts when making network calls in your sketch
  // if you just checked the status of te button in the loop you might
  // miss the button press.
  attachInterrupt(TELEGRAM_BUTTON_PIN, telegramButtonPressed, RISING);

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
  if ( telegramButtonPressedFlag ) {
    String msg = "Button pressed";
    broadcastTelegramMessage(msg);
  }
  // wait for messages
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    String msg = "";
    while (numNewMessages) {
      Serial.println("got message");
      for (int i = 0; i < numNewMessages; i++) {
        // check message content
        if ( bot.messages[i].text=="/LEDON" ) {
          msg = "LED is now ON";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
        if ( bot.messages[i].text=="/LEDOFF" ) {
          msg = "LED is now OFF";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
        if ( bot.messages[i].text=="/TEMP" ) {
          msg = "Temperature: " + String(hdc.readTemperature()) + "°C";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
        if ( bot.messages[i].text=="/HUM" ) {
          msg = "Humidity: " + String(hdc.readHumidity());
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
        if ( bot.messages[i].text=="/TEMP+HUM" ) {
          msg = "Temperature: " + String(hdc.readTemperature()) + "°C";
          sendTelegramMessage(bot.messages[i].chat_id,msg);
          msg = "Humidity: " + String(hdc.readHumidity());
          sendTelegramMessage(bot.messages[i].chat_id,msg);
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}

void telegramButtonPressed() {
  Serial.println("telegramButtonPressed");
  int button = digitalRead(TELEGRAM_BUTTON_PIN);
  if (button == HIGH)
  {
    digitalWrite(LED_PIN, HIGH);
    telegramButtonPressedFlag = true;
  }
  return;
}

void broadcastTelegramMessage(String msg) {
  for ( int k = 0; k < IDs_SIZE; k++ ) {
    bot.sendMessage(chat_ids[k], msg, "");
  }
  Serial.println("Broadcasting message");
  telegramButtonPressedFlag = false;
  digitalWrite(LED_PIN, LOW);
}

void sendTelegramMessage(String chat_id, String msg) {
  digitalWrite(LED_PIN, HIGH);
  if (  bot.sendMessage(chat_id, msg, "") ) {
    Serial.println("Message has been sent.");
  }
  delay(100);
  digitalWrite(LED_PIN, LOW);
}
