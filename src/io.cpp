#ifndef io_cpp
#define io_cpp

#include <Arduino.h>
#include "io.h"
#include "debug.h"

//vars
bool io_interrupt_flag = false;
//struct to hold controler data
struct controler_data current_gamepad_data;


/**
 * @brief Initializes GPIO pins based on their predefined modes.
 * 
 * This function iterates through the `pin_names` array and sets up each pin
 * according to its specified mode. Supported modes include input, output,
 * interrupt, analog, LED, and USB. Debug messages are logged during the
 * initialization process.
 * 
 * Pin Modes:
 * - `in`: Configures the pin as an input.
 * - `out`: Configures the pin as an output.
 * - `intr`: Configures the pin as an input and attaches an interrupt handler for detecting rising edge signals.
 * - `analog`: Configures the pin as an analog input.
 * - `led`: Configures the pin as an output and initializes it with a PWM value of 0.
 * - `usb`: USB pins are initialized outside of this function.
 * 
 * Error Handling:
 * - If an unexpected `pin_mode` value is encountered, a debug message is logged.
 * 
 * Debug Messages:
 * - Logs the start and completion of the pin initialization process.
 * - Logs an error message if an unexpected `pin_mode` value is encountered.
 * 
 * @note USB pins are not initialized within this function.
 */
void io_gpio_init() {

    debug_msg(partal_io, "io_gpio_init called, setting up pins", false, 0);
  
    //begin iterating through pins
    for (size_t i = 1; i < sizeof(pin_names[0]); i++) {
  
      switch (pin_names[i]->pin_mode) {
      default:
        // Error handling for unexpected pin_mode value
        debug_msg(partal_io, "Unexpected pin_mode value", false, 0);
        break;
      case in:
        pinMode(pin_names[i]->pin_number, INPUT);
        break;
      
      case out:
          pinMode(pin_names[i]->pin_number, OUTPUT);
        break;
      case analog:
        pinMode(pin_names[i]->pin_number, INPUT);
        break;
      case led:
        pinMode(pin_names[i]->pin_number, OUTPUT);
        analogWrite(pin_names[i]->pin_number, 0);
        break;
      case usb:
        //usb pins are initialized outside of this function
        break;
      }  
    }
  
    debug_msg(partal_io, "pins have been initialized", false, 0);
  
    return;
  };


/**
 * @brief Reads gamepad input data from analog and digital pins, processes it, 
 *        and updates the current gamepad data structure.
 * 
 * This function performs the following steps:
 * 1. Initializes local variables to store the current state of gamepad inputs.
 * 2. Reads analog values for the left and right sticks (X and Y axes) and 
 *    digital values for buttons and stick switches from their respective pins.
 * 3. Maps the analog stick values from the range [0, 4095] to [-2000, 2000].
 * 4. Packs the digital button states into a single 32-bit variable.
 * 5. Updates the global gamepad data structure with the processed input values.
 * 
 * @note This function assumes the existence of global variables for pin 
 *       configurations and the gamepad data structure.
 */
void io_read_gamepad_data() {

  debug_msg(partal_io, "io_read_gamepad_data called", false, 0);

    //init loca vars
    int16_t curent_ls_x = 0;
    int16_t curent_ls_y = 0;
    int16_t curent_rs_x = 0;
    int16_t curent_rs_y = 0;
    bool curent_btn_1 = false;
    bool curent_btn_2 = false;
    bool curent_ls_sw = false;
    bool curent_rs_sw = false;
    uint32_t curent_buttons = 0;

    //start reading pins
    curent_ls_x = analogRead(ls_x.pin_number);
    curent_ls_y = analogRead(ls_y.pin_number);
    curent_rs_x = analogRead(rs_x.pin_number);
    curent_rs_y = analogRead(rs_y.pin_number);
    curent_btn_1 = digitalRead(btn_1.pin_number);
    curent_btn_2 = digitalRead(btn_2.pin_number);
    curent_ls_sw = digitalRead(ls_sw.pin_number);
    curent_rs_sw = digitalRead(rs_sw.pin_number);

    //re bound analogue to +- 2000
    curent_ls_x = map(curent_ls_x, 0, 4095, -2000, 2000);
    curent_ls_y = map(curent_ls_y, 0, 4095, -2000, 2000);
    curent_rs_x = map(curent_rs_x, 0, 4095, -2000, 2000);
    curent_rs_y = map(curent_rs_y, 0, 4095, -2000, 2000);

    //move buttions into buttion var
    curent_buttons |= (curent_btn_1 << 0);
    curent_buttons |= (curent_btn_2 << 1);
    curent_buttons |= (curent_ls_sw << 2);
    curent_buttons |= (curent_rs_sw << 3);

    //write data to struct
    current_gamepad_data.ls_x = curent_ls_x;
    current_gamepad_data.ls_y = curent_ls_y;
    current_gamepad_data.rs_x = curent_rs_x;
    current_gamepad_data.rs_y = curent_rs_y;
    current_gamepad_data.buttons = curent_buttons;

    return;
    
}


#endif // io_cpp