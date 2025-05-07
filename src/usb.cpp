#ifndef usb_cpp
#define usb_cpp

#include <Arduino.h>
#include <tusb.h>
#include "usb.h"
#include "debug.h"


//called when the device is mounted
void tud_mount_cb(void) {

}

//called when device is unmounted
void tud_unmount_cb(void) {

}

//called when device enters suspend
void tud_suspend_cb(bool remote_wakeup_en) {

}

//called when device leaves suspend
void tud_resume_cb(void) {

}

//send gmaepad data
void usb_send_gamepad_data(int16_t ls_x, int16_t ls_y, int16_t rs_x, int16_t rs_y,uint32_t buttons) {
    if (tud_hid_ready()) {
        tud_hid_gamepad_report(5, ls_x, ls_y, 0, 0, rs_x, rs_y, 0, buttons);
    } else {
        debug_msg(partal_usb, "hid not ready", false, 0);
    }
}



#endif // usb_cpp