#ifndef INC_TASKWEBSERVER_H_
#define INC_TASKWEBSERVER_H_

#include "globals.h"

extern String output1State;
extern String output2State;
extern String output3State;


extern void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
extern void parseWebSocketMessage(AsyncWebSocketClient *client, const String &message);

extern void initWebServer();
extern void handleRoot();

extern void loopWebServer();
#endif /* INC_TASKWEBSERVER_H_ */