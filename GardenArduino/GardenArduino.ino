#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>

RF24 radio(7, 8);  // CE pin, CSN pin

const byte addresses[][6] = { "00001", "00002" };
char receivedCommand;
char result[30];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, addresses[0]);  // 00001
  radio.openWritingPipe(addresses[1]);     // 00002
  radio.setPALevel(RF24_PA_HIGH);          // Set power level to the lowest
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedCommand, sizeof(receivedCommand));
    Serial.print("Received: ");
    Serial.println(receivedCommand);
    delay(100);
    radio.stopListening();
    delay(100);
    prepResult();
    radio.write(&result, sizeof(result));
    delay(100);
    radio.startListening();
    Serial.print("Sent: ");
    Serial.println(result);
  }
}

void prepResult() {
  if (receivedCommand == 'h') {
    strcpy(result, "Hello!");
  } else if (receivedCommand == 't') {
    itoa(millis() / 1000, result, 10);
  } else {
    strcpy(result, "Error");
  }
}