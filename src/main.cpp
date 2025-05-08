
#include <Arduino.h>
#include "io.h"
#include "debug.h"
#include <tusb.h>
#include "usb.h"




void setup() {
  //init serail
  HardwareSerial Serial1(1);
  Serial1.begin(115200, SERIAL_8N1, 34, 33);

  //init io
  debug_msg(partal_io, "starting io init", false, 0);
  io_gpio_init();

  //jtag setup
  debug_msg(partal_io, "starting jtag init", false, 0);
  //free up jtag pins
  gpio_reset_pin(GPIO_NUM_39); //tck
  gpio_reset_pin(GPIO_NUM_40); //tdo
  gpio_reset_pin(GPIO_NUM_41); //tdi
  gpio_reset_pin(GPIO_NUM_42); //tms

  //init usb
  debug_msg(partal_io, "starting usb init", false, 0);
  tusb_init();
  

}

void loop() {
  //read gamepad data
  io_read_gamepad_data();

  //send gamepad data
  usb_send_gamepad_data(current_gamepad_data.ls_x, current_gamepad_data.ls_y, current_gamepad_data.rs_x, current_gamepad_data.rs_y, current_gamepad_data.buttons);

  //run usb task
  tud_task();  
}
