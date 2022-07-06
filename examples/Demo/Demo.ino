/*
  WebSerial Demo
  ------
  This example code works for both ESP8266 & ESP32 Microcontrollers
  WebSerial is accessible at your ESP's <IPAddress>/webserial URL.

  Author: Ayush Sharma
  Checkout WebSerial Pro: https://webserial.pro
*/
#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

/* STA mode */
const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

/* I2C Pin Assignments */
/* These are raw GPIOs, (D2 == GPIO4 == SDA) (D1 == GPIO5 == SCL)
const char sda_pin = D2;
const char scl_pin = D1;

bool buf[4096];
bool* bufI = &buf[0];
const uint32_t PAUSE = 1 << 20;

/* Message callback of WebSerial */
#void recvMsg(uint8_t *data, size_t len){
#  WebSerial.println("Received Data...");
#  String d = "";
#  for(int i=0; i < len; i++){
#    d += char(data[i]);
#  }
#  WebSerial.println(d);
#}

/* Message callback of I2C Bus to WebSerial */
uint32_t waitCl(bool expected) {
    uint32_t i = 0;
    while (digitalRead(scl_pin) != expected) {
      while ((digitalRead(scl_pin) != expected) && (++i % PAUSE != 0)) ;

      if (i % PAUSE == 0) {
        uint32_t i = 0;
        while (&buf[i] != bufI) {
          WebSerial.print(buf[i++]);
          if (i % 9 == 0)
            WebSerial.print(' ');
        }
        if (bufI != &buf[0])
          WebSerial.print('\n');
        bufI = &buf[0];
        yield();
      }
    }
    return i;
}

void setup() {
    Serial.begin(115200);
    pinMode(sda_pin, INPUT);
    pinMode(scl_pin, INPUT);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
#    server.begin();
    ## Instead of running the WebSerial monitor, do main call for I2C sniffing ##
    while (true) {
      uint32_t incr = waitCl(HIGH);
      *bufI++ = digitalRead(sda_pin);
      waitCl(LOW);
    }
}

void loop() {
}
