#include "../include/RS485.h"

HardwareSerial RS485Serial(1);

const byte SOUND_REQUEST[] = {0x15, 0x03, 0x01, 0xF6, 0x00, 0x01, 0x66, 0xD0};
const byte PRESSURE_REQUEST[] = {0x15, 0x03, 0x01, 0xF9, 0x00, 0x01, 0x56, 0xD3};
const byte PM2P5_REQUEST[] = {0x15, 0x03, 0x01, 0xF7, 0x00, 0x01, 0x37, 0x10};
const byte PM10_REQUEST[] = {0x15, 0x03, 0x01, 0xF8, 0x00, 0x01, 0x07, 0x13};
const byte AMBIENT_LIGHT_REQUEST[] = {0x15, 0x03, 0x01, 0xFB, 0x00, 0x01, 0xF7, 0x13};
const byte TEMPERATURE_REQUEST[] = {0x15, 0x03, 0x01, 0xF5, 0x00, 0x01, 0x96, 0xD0};
const byte HUMIDITY_REQUEST[] = {0x15, 0x03, 0x01, 0xF4, 0x00, 0x01, 0xC7, 0x10};

const byte SOIL_MOISTURE_REQUEST[] = {0x17, 0x03, 0x00, 0x12, 0x00, 0x01, 0x3D, 0x44};

const byte WIND_DIRECTION_REQUEST[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

void sendRS485Command(const byte *command, int commandSize, byte *response, int responseSize) {
    RS485Serial.write(command, commandSize);
    RS485Serial.flush();
    delay(100);
    if (RS485Serial.available() >= responseSize) {
        RS485Serial.readBytes(response, responseSize);
    } 
}

// Helper function to read sensor data
float readSensorData(const byte *request, int requestSize) {
    byte response[7];
    sendRS485Command(request, requestSize, response, sizeof(response));
    Serial.println();
    Serial.print("Request: ");
    for (int i = 0; i < requestSize; i++) {
        Serial.print(request[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("Response: "); 
    for (int i = 0; i < sizeof(response); i++) {
        Serial.print(response[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
    if (response[1] == 0x03) {
        Serial.println("Response: ");
        return ((response[3] << 8) | response[4]) / 10.0;
    }
    return -1.0; // Return -1.0 if the response is invalid
}

// Function to read temperature and humidity
void readTemperatureAndHumidity() {
    float temperature = readSensorData(TEMPERATURE_REQUEST, sizeof(TEMPERATURE_REQUEST));
    delay(1000);
    float humidity = readSensorData(HUMIDITY_REQUEST, sizeof(HUMIDITY_REQUEST));
    Serial.println(temperature);
    Serial.println(humidity);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

float getTemperature() {
    float temperature = readSensorData(TEMPERATURE_REQUEST, sizeof(TEMPERATURE_REQUEST));
    return temperature;
}
float getHumidity() {
    float humidity = readSensorData(HUMIDITY_REQUEST, sizeof(HUMIDITY_REQUEST));
    return humidity;
}

float getSoilMoisture() {
    float soilMoisture = readSensorData(SOIL_MOISTURE_REQUEST, sizeof(SOIL_MOISTURE_REQUEST));
    return soilMoisture;
}

float getWindDirection() {
    float windDirection = readSensorData(WIND_DIRECTION_REQUEST, sizeof(WIND_DIRECTION_REQUEST));
    return windDirection;
}

void readWindDirection() {
    float windDirection = getWindDirection();
    Serial.print("Wind Direction: ");
    Serial.println(windDirection);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

// Initialize RS485 communication
void InitRS485() {
    RS485Serial.begin(BAUD_RATE_2, SERIAL_8N1, RXD_RS485, TXD_RS485);
}
