#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE pin, CSN pin

const byte addresses[][6] = { "00001", "00002" };
char result[30];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, addresses[1]);  // 00002
  radio.openWritingPipe(addresses[0]);     // 00001
  radio.setPALevel(RF24_PA_HIGH);          // Set power level to the lowest
  radio.startListening();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    radio.stopListening();
    radio.write(&command, sizeof(command));
    radio.startListening();
    Serial.print("Sent: ");
    Serial.println(command);
  }

  if (radio.available()) {
    radio.read(&result, sizeof(result));
    Serial.print("Received: ");
    Serial.println(result);
  }
}
