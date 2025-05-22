#ifndef io_h
#define io_h

#include <Arduino.h>

//io_init struct setup
enum in_out {
    in,       //input
    out,      //output
    analog,   //analog pin
    led,      //led pin
    usb       //usb pin
  };
  
  struct pin {
    uint8_t pin_number;        //gpio number
    in_out pin_mode;       //defines pinmode see enum above for deatails
      
  };
  //BE SURE TO ADD PINS TO BOTH THE "pin" STRUCT AND THE "pin_names" ARRAY THEY MUST MATCH
  //io_init struct defines  {pin_number, pin_mode}
  static struct pin gpio0 {0, in};
  static struct pin ls_x {1, analog};
  static struct pin ls_y {2, analog};
  static struct pin rs_x {3, analog};
  static struct pin rs_y {4, analog};
  static struct pin ls_sw {5, in};
  static struct pin rs_sw {6, in};
  static struct pin gpio7 {7, in};
  static struct pin gpio8 {8, in};
  static struct pin led_b {9, led};
  static struct pin led_g {10, led};
  static struct pin led_r {11, led};
  static struct pin btn_1 {12, in};
  static struct pin btn_2 {13, in};
  static struct pin gpio14 {14, in};
  static struct pin dac_1 {17, out};
  static struct pin dac_2 {18, out};
  static struct pin usb_dn {19, usb};
  static struct pin usb_dp {20, usb};
  static struct pin gpio21 {21, in};
  static struct pin gpi033 {33, in};
  static struct pin gpio34 {34, in};
  static struct pin gpio35 {35, in};
  static struct pin gpio36 {36, in};
  static struct pin gpio37 {37, in};
  static struct pin gpio38 {38, in};


   
  
  //Array of pin structs for automatic pin initialization
static struct pin* pin_names[] = {
    &gpio0,
    &ls_x,
    &ls_y,
    &rs_x,
    &rs_y,
    &ls_sw,
    &rs_sw,
    &gpio7,
    &gpio8,
    &led_b,
    &led_g,
    &led_r,
    &btn_1,
    &btn_2,
    &gpio14,
    &dac_1,
    &dac_2,
    &usb_dn,
    &usb_dp,
    &gpio21,
    &gpi033,
    &gpio34,
    &gpio35,
    &gpio36,
    &gpio37,
    &gpio38
};

struct controler_data {
    int16_t ls_x;
    int16_t ls_y;
    int16_t rs_x;
    int16_t rs_y;
    uint32_t buttons;
};
//struct to hold controler data
extern struct controler_data current_gamepad_data;

//function prototypes
void io_gpio_init();
struct controler_data io_read_gamepad_data();

#endif // io_h