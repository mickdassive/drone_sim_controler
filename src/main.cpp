
#include <Arduino.h>
#include "io.h"
#include "DEBUG.h"
#include "usb.h"
#include "esp_task_wdt.h"




void setup() {

  //init serail
  //HardwareSerial Serial1(1);
  Serial.begin(115200, SERIAL_8N1, 44, 43);



}

void loop() {


}
