
#include <Arduino.h>
#include "io.h"
#include "DEBUG.h"
#include "usb.h"




void setup() {
  //init serail
  HardwareSerial Serial1(1);
  Serial1.begin(115200, SERIAL_8N1, 34, 33);

  //init io
  debug_msg(DEBUG_PARTIAL_IO, "starting io init", false, 0);
  io_gpio_init();

  //jtag setup
  debug_msg(DEBUG_PARTIAL_IO, "starting jtag init", false, 0);
  //free up jtag pins
  gpio_reset_pin(GPIO_NUM_39); //tck
  gpio_reset_pin(GPIO_NUM_40); //tdo
  gpio_reset_pin(GPIO_NUM_41); //tdi
  gpio_reset_pin(GPIO_NUM_42); //tms

  //init usb
  usb_init();

  //led animation
  debug_msg(DEBUG_PARTIAL_IO, "starting led animation", false, 0);
  for (int i = 0; i < 6; i++) {
    if (i == 1){
      for (int x = 0; x < 255; x++) {
        analogWrite(led_b.pin_number, x);
        delay(10);
      }
    } else if (i == 2){
      for (int x = 0; x < 255; x++) {
        analogWrite(led_g.pin_number, x);
        delay(10);
      }
    } else if (i == 3){
      for (int x = 0; x < 255; x++) {
        analogWrite(led_r.pin_number, x);
        delay(10);
      }
    } else if (i == 4){
      for (int x = 255; x > 0; x--) {
        analogWrite(led_b.pin_number, x);
        delay(10);
      }
    } else if (i == 5){
      for (int x = 255; x > 0; x--) {
        analogWrite(led_g.pin_number, x);
        delay(10);
      }
    } else if (i == 6){
      for (int x = 255; x > 0; x--) {
        analogWrite(led_r.pin_number, x);
        delay(10);
      }
    }
    
  }

  debug_msg(DEBUG_FULL, "boot complte", false, 0);
    

}

void loop() {
  //do usb tasks 
  usb_tasks();


}
