#include "TaskMail.h"

#define emailSenderAccount    "james.001lake@gmail.com"
#define emailSenderPassword   "mvor uskh csyq wqaw"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "[ALERT] ESP32 Temperature"

String inputMessage = ""; // Email address input from the user
String enableEmailChecked = "";
String inputMessage2 = ""; // Email enable input from the user
String inputMessage3 = ""; // Threshold temperature input from the user
String lastTemperature;

bool emailSent = false;

unsigned long previousMillis = 0;     
const long interval = 5000;    

SMTPSession smtp;

// Queue handle for email messages
QueueHandle_t emailQueue;

void InitMail() {
  MailClient.networkReconnect(true);
  // Create a queue capable of holding 10 strings
  emailQueue = xQueueCreate(10, sizeof(String));
  // Create the email task
  xTaskCreate(emailTask, "EmailTask", 10240, NULL, 1, NULL);
}

void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());
  if (status.success()) {
    Serial.println("Email sent successfully");
    Serial.println("----------------");
  }
}

void emailTask(void *pvParameters) {
  String emailMessage;
  while (true) {
    // Wait for an email message to be sent to the queue
    if (xQueueReceive(emailQueue, &emailMessage, portMAX_DELAY)) {
      sendEmailNotification(emailMessage);
    }
  }
}

bool sendEmailNotification(String emailMessage) {
  ESP_Mail_Session session;
  session.server.host_name = smtpServer;
  session.server.port = smtpServerPort;
  session.login.email = emailSenderAccount;
  session.login.password = emailSenderPassword;
  session.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "ESP32";
  message.sender.email = emailSenderAccount;
  message.subject = emailSubject;
  message.addRecipient("Recipient", inputMessage);
  message.text.content = emailMessage.c_str();
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;
  smtp.callback(smtpCallback);

  if (!smtp.connect(&session)) {
    Serial.print("Failed to connect to SMTP server: ");
    Serial.println(smtp.errorReason());
    return false;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Error sending Email: "); 
    Serial.println(smtp.errorReason());
    smtp.closeSession();
    return false;
  }

  smtp.closeSession();
  return true;
}

// Function to send an email message to the queue
void queueEmailMessage(String emailMessage) {
  if (xQueueSend(emailQueue, &emailMessage, portMAX_DELAY) != pdPASS) {
    Serial.println("Failed to queue email message");
  }
}