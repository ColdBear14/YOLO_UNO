#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include <LittleFS.h>
#include <DHT20.h>
#include <PubSubClient.h>
// #include <WebServer.h>
#include <Ultrasonic.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

///
#include "../src/connect/TaskWifi.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebServer.h"

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