#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


// include libraries
#include <HTTPClient.h>
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "FS.h"
#include <LittleFS.h>
#include <DHT20.h>
#include <PubSubClient.h>
#include "NTPClient.h"
#include <Ultrasonic.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <ElegantOTA.h>

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#include <ESP_Mail_Client.h>

///
#include "../src/connect/TaskWifi.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebServer.h"
#include "../src/connect/TaskAP.h"
#include "../src/connect/TaskMail.h"
#include "../src/connect/TaskMongo.h"

#include "../src/include/TaskDHT20.h"
#include "../src/include/TaskPIR.h"
#include "../src/include/TaskHC_SR04.h"
#include "../src/include/TaskLED.h"
#include "../src/include/TaskRGB.h"
#include "../src/include/TaskFan.h"
#include "../src/include/TaskLUX.h"
#include "../src/include/TaskSMS.h"
#include "../src/include/TaskLCD.h"
#include "../src/include/TaskRelay.h"

#include "../src/include/RS485.h"

#define BAUD_RATE_2 9600

#define RXD_RS485 43
#define TXD_RS485 44

#define delay_time 10000

#define PIR_SENSOR_PIN 7 

#define HC_SR04_TRIG_PIN 18
#define HC_SR04_ECHO_PIN 21

#define LUX_PIN 3 
#define SMS_PIN 1 

#define PIN_NEO_PIXEL  6   
#define Relay_PIN 8 
#define FAN_PIN 10 
#define LED_PIN 48

#define MY_SCL 11
#define MY_SDA 12

#endif