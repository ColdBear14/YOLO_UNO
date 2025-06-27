#include "TaskWebServer.h"

String output1State = "off";
String output2State = "off";
String output3State = "off";


// Khởi tạo máy chủ HTTP và WebSocket
AsyncWebServer server(8080); // Máy chủ HTTP chạy trên cổng 80
AsyncWebSocket ws("/ws"); // Tạo WebSocket tại endpoint "/ws"

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
    }
    else if (type == WS_EVT_DATA)
    {
        String message = String((char *)data);
        parseWebSocketMessage(client, message); // Gọi hàm xử lý tin nhắn
        Serial.printf("WebSocket client #%u sent data: %s\n", client->id(), message.c_str());
  }
}

void parseWebSocketMessage(AsyncWebSocketClient *client, const String &message) {
    // Xử lý tin nhắn từ client
    // Tìm vị trí của "device" và "state"
    int devicePos = message.indexOf("\"device\":");
    int statePos = message.indexOf("\"state\":");

    // Lấy giá trị device
    int commaPos = message.indexOf(",", devicePos);
    String deviceStr = message.substring(devicePos + 9, commaPos);
    deviceStr.trim();
    int device = deviceStr.toInt();

    // Lấy giá trị state
    int quote1 = message.indexOf("\"", statePos + 8);
    int quote2 = message.indexOf("\"", quote1 + 1);
    String state = message.substring(quote1 + 1, quote2);

    if(device == 1) {
        // Xử lý thiết bị A
        output1State = state;
    } else if(device == 2) {
        // Xử lý thiết bị B
        output2State = state;
    } else if (device == 3) {
        output3State = state;
    }
}

void initWebServer() {

  if (!LittleFS.begin())
  {
      Serial.println("An Error has occurred while mounting LittleFS");
      return;
  }

    File root = LittleFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.println(file.name());
        file = root.openNextFile();
    }

  ws.onEvent(onEvent);

  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/script.js", "application/javascript"); });
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/styles.css", "text/css"); });

  server.begin();
  Serial.println("HTTP server started");
}

void loopWebServer() {
  ws.cleanupClients();

  if (ws.availableForWriteAll()) {
        
    int temperature = getTemp(); // Lấy giá trị nhiệt độ từ DHT20
    int humidity = getHum();     // Lấy giá trị độ ẩm từ DHT20
    int lux = getLux();
    int soil = getValueSMS();
    int distance = getDistanceHC_SR04();

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    String jsonData = "{ \"temperature\": " + String(temperature) + 
                      ", \"humidity\": " + String(humidity) +
                      ", \"lux\": " + String(lux) + 
                      ", \"soil\": " + String(soil) + 
                      ", \"distance\": " + String(distance) + "}";

    //   String jsonData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";
      ws.textAll(jsonData); // Gửi dữ liệu đến tất cả các client WebSocket
  }
}