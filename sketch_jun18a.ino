// #include <CustomSoftwareSerial.h>

// CustomSoftwareSerial* customSerial;               // Declare serial

// // Init value
// void setup() {
//   Serial.begin(9600);
//   while (!Serial) {
//     ; // wait for serial port to connect. Needed for Leonardo only
//   }

//   customSerial = new CustomSoftwareSerial(10, 11); // rx, tx
//   customSerial->begin(4800, CSERIAL_8N1);         // Baud rate: 9600, configuration: CSERIAL_8N1
// }

// int availableData = -1;

// void loop() {
 
//   if (customSerial->available()) {
//     Serial.write(customSerial->read());
//     availableData = 1;
//   } else {
//     Serial.println();
//     availableData = 0;
//   }

//   if (availableData = 0) {
//     Serial.println();
//     availableData = -1;
//   }
//   // delay(1000);
// }

#include <SoftwareSerial.h>

// software serial #1: RX = digital pin 10, TX = digital pin 11

// Typical Baud rate:	4800
// Data bits:	8
// Parity:	None
// Stop bits:	1
// Handshake:	None

SoftwareSerial portOne(10, 11);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only

  }
  portOne.begin(4800);
}

bool monitor = false;

void loop() {
  portOne.listen();

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    if (command.compareTo("stop") == 0) {
      monitor = false;
    }

    if (command.compareTo("start") == 0) {
      monitor = true;
    }
  }

  if (monitor) {
    // Serial.println("\nData from port one:");
    while (portOne.available() > 0) {
      char inByte = portOne.read();
      if (inByte == 0xDB) {
        Serial.println();
      }

      // Serial.print(inByte, BIN);
      // Serial.write("(");
      Serial.write(inByte);
      // Serial.write(")");
      // Serial.write(" ");
    }
    // Serial.println();
  }
}