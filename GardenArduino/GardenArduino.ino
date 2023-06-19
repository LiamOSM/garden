#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE pin, CSN pin

const byte addresses[][6] = { "00001", "00002" };
char result[10];

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
    char receivedCommand;
    radio.read(&receivedCommand, sizeof(receivedCommand));
    Serial.print("Received: ");
    Serial.println(receivedCommand);
    delay(100);
    radio.stopListening();
    delay(100);
    if (receivedCommand == 's') {
      result[0] = 'h';
      result[1] = 'e';
      result[2] = 'l';
      result[3] = 'l';
      result[4] = 'o';
      result[5] = '\0';
    } else {
      result[0] = 'e';
      result[1] = 'r';
      result[2] = 'r';
      result[3] = 'o';
      result[4] = 'r';
      result[5] = '\0';
    }

    radio.write(&result, sizeof(result));
    delay(100);
    radio.startListening();
    Serial.print("Sent: ");
    Serial.println(result);
  }
}
