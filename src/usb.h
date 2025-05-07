#ifndef usb_h
#define usb_h

#include <Arduino.h>

//function prototypes
void usb_send_gamepad_data(int16_t ls_x, int16_t ls_y, int16_t rs_x, int16_t rs_y,uint32_t buttons);



#endif // usb_h