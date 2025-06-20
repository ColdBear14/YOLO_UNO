#include "../include/TaskDHT20.h"

DHT20 dht20;

void TaskDHT20(void *pvParameters)
{
  while (1)
  {
    getValueDHT20();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

int getTemp(){
  dht20.read();
  return dht20.getTemperature();
}

int getHum(){
  dht20.read();
  return dht20.getHumidity();
}

void getValueDHT20()
{
    if (dht20.read() == DHT20_OK)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << "Temperature:" << dht20.getTemperature() << " Humidity:" << dht20.getHumidity();
        // publishData("DHT20", String(ss.str().c_str()));
    }
    else
    {
        Serial.print("Failed to read DHT20 sensor. Status: ");
    }
}

void initDHT20()
{
    Wire.begin(MY_SCL, MY_SDA);
    dht20.begin();
    xTaskCreate(
      TaskDHT20,    // Function to implement the task
      "TaskDHT20",  // Name of the task
      4096,       // Stack size in words
      NULL,        // Task input parameter
      1,           // Priority of the task
      NULL         // Task handle
  );
}


