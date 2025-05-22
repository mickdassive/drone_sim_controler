#ifndef usb_cpp
#define usb_cpp

#include <Arduino.h>
#include "usb.h"
#include "DEBUG.h"
#include "io.h"
#include "Adafruit_TinyUSB.h"

//usb defines

Adafruit_USBD_HID usb_hid;

hid_gamepad_report_t gp;

uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_GAMEPAD()
};


/**
 * @brief Initializes the USB subsystem and sets up the HID interface.
 *
 * This function performs the following steps:
 * - Logs the start of the USB initialization process.
 * - Configures the HID (Human Interface Device) with a specified polling interval and report descriptor.
 * - Begins the HID interface.
 * - If the USB device is already mounted, it detaches and reattaches the device to force re-enumeration.
 *
 * Note: The function currently contains a commented-out return statement.
 */
void usb_init() {
    //init usb
    debug_msg(DEBUG_PARTIAL_USB, "starting usb init", false, 0);
    // Setup HID
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();

    //reinumerate device
      if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
    }

    return;
 
}

/**
 * @brief Sends gamepad data over USB HID.
 *
 * This function takes a controler_data structure containing the current state
 * of the gamepad (such as joystick positions and button states), maps its fields
 * to the corresponding fields of the USB HID gamepad report structure, and sends
 * the report via the USB HID interface.
 *
 * @param gamepad_data The structure containing the current gamepad state to send.
 */
void usb_send_gamepad_data(struct controler_data gamepad_data) {
    debug_msg(DEBUG_PARTIAL_USB, "usb_send_gamepad_data called", false, 0);
    //send gamepad data
    gp.x = gamepad_data.ls_x;
    gp.y = gamepad_data.ls_y;
    gp.z = 0;
    gp.rz = gamepad_data.rs_x;
    gp.rx = gamepad_data.rs_y;
    gp.ry = 0;
    gp.hat = 0;
    gp.buttons = gamepad_data.buttons;
    usb_hid.sendReport(0, &gp, sizeof(gp));
}

/**
 * @brief Handles periodic USB tasks for the device.
 *
 * This function performs the following operations:
 * - Logs a debug message indicating the function was called.
 * - If manual polling is required (TINYUSB_NEED_POLLING_TASK is defined), it calls the TinyUSB device task handler.
 * - Checks if the USB device is mounted (enumerated by the host); if not, the function returns early.
 * - Checks if the USB HID interface is ready; if not, the function returns early.
 * - Reads gamepad data and sends it over USB HID if all conditions are met.
 */
void usb_tasks () {

    debug_msg(DEBUG_PARTIAL_USB, "usb_tasks called", false, 0);
    #ifdef TINYUSB_NEED_POLLING_TASK
    // Manual call tud_task since it isn't called by Core's background
    TinyUSBDevice.task();
    #endif

    // not enumerated()/mounted() yet: nothing to do
    if (!TinyUSBDevice.mounted()) {
        digitalWrite(led_r.pin_number, !digitalRead(led_r.pin_number));
        delay(500);
        return;
    } else {
        digitalWrite(led_r.pin_number, LOW);
        digitalWrite(led_g.pin_number, HIGH);
    }

    if (!usb_hid.ready()) return;

    usb_send_gamepad_data(io_read_gamepad_data());

    return;


}



#endif // usb_cpp