#ifndef INC_TASKMAIL_H_
#define INC_TASKMAIL_H_

#include "globals.h"

extern void InitMail();

extern String inputMessage; // Email address input from the user

void emailTask(void *pvParameters);
bool sendEmailNotification(String emailMessage);

extern void queueEmailMessage(String emailMessage);


#endif /* INC_TASKMAIL_H_ */