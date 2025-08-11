#ifndef INC_485_H_
#define INC_485_H_

#include "globals.h"


extern void sendRS485Command(const byte *command, int commandSize, byte *response, int responseSize);

// Helper function to read sensor data
extern float readSensorData(const byte *request, int requestSize);

// Function to read temperature and humidity
extern void readTemperatureAndHumidity();

extern float getTemperature();
extern float getHumidity();
extern float getSoilMoisture();

extern float getWindDirection();
extern void readWindDirection();

// Initialize RS485 communication
extern void InitRS485();

#endif /* INC_485_H_ */