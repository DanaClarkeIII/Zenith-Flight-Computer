#include <LoRa.h>

#define ss 7
#define rst 23
#define dio0 6

String lastSent = "";
bool waitingForAck = false;
unsigned long lastSendTime = 0;
int sendAttempts = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Transceiver");

  LoRa.setPins(ss, rst, dio0);
  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // check for incoming packets
  checkForPackets();

  // if we're not waiting for an acknowledgement, send a new message
  if (!waitingForAck) {
    String toSend = "Hello, world!";
    send(toSend);
    lastSent = toSend;
    waitingForAck = true;
    lastSendTime = millis();
    sendAttempts = 1;
  }
  // if we are waiting for an acknowledgement, check if the timeout has expired
  else if (millis() - lastSendTime > 2000) { // 2 second timeout
    if (sendAttempts < 5) { // limit of 5 retransmission attempts
      // if the timeout has expired and we haven't reached the retransmission limit, resend the last message
      send(lastSent);
      lastSendTime = millis();
      sendAttempts++;
    } else {
      // if we've reached the retransmission limit, give up on this message
      waitingForAck = false;
      Serial.println("Failed to send message");
    }
  }
}

void checkForPackets() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    byte checksum = 0;
    while (LoRa.available()) {
      char c = (char)LoRa.read();
      received += c;
      checksum ^= c;
    }
    byte receivedChecksum = received.charAt(received.length() - 1);
    received = received.substring(0, received.length() - 1);
    if (checksum == receivedChecksum) {
      Serial.print("Received packet '");
      Serial.print(received);
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
      if (received == "NACK") {
        // if we received a NACK, resend the last message
        send(lastSent);
        lastSendTime = millis();
      } else if (received == "ACK") {
        // if we received an ACK, we can send the next message
        waitingForAck = false;
      }
    } else {
      Serial.println("Checksum mismatch, sending NACK");
      send("NACK");
    }
  }
}

void send(String message) {
  byte checksum = 0;
  for (int i = 0; i < message.length(); i++) {
    checksum ^= message.charAt(i);
  }
  message += (char)checksum;

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
}
