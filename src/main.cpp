#include "globals.h"

void setup()
{
  Serial.begin(115200);
  InitWiFi();
  initMQTT();
  initWebServer();

  initDHT20();
  initLCD();
  initLED();

  initRGB();
  initRelay();
  initFan();

  // initPIR();

  initLUX();
  initHC_SR04();
  initSMS();
}

void loop()
{
  if (!Wifi_reconnect())
  {
    return;
  }
  reconnectMQTT();
  loopWebServer();
  vTaskDelay(100/ portTICK_PERIOD_MS);
}
