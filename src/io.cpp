#ifndef io_cpp
#define io_cpp

#include <Arduino.h>
#include "io.h"
#include "DEBUG.h"

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

    debug_msg(DEBUG_PARTIAL_IO, "io_gpio_init called, setting up pins", false, 0);
  
    //begin iterating through pins
    for (size_t i = 1; i < sizeof(pin_names[0]); i++) {
  
      switch (pin_names[i]->pin_mode) {
      default:
        // Error handling for unexpected pin_mode value
        debug_msg(DEBUG_PARTIAL_IO, "Unexpected pin_mode value", false, 0);
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
  
    debug_msg(DEBUG_PARTIAL_IO, "pins have been initialized", false, 0);
  
    return;
  };



/**
 * @brief Reads the current state of the gamepad inputs and returns the data.
 *
 * This function reads analog values from the left and right stick axes, as well as digital values from multiple buttons and switches.
 * The analog stick values are mapped from their raw range (0-4095) to a normalized range (-2000 to 2000).
 * Button and switch states are combined into a single integer using bitwise operations.
 *
 * @return controler_data A struct containing the current state of all gamepad controls.
 */
struct controler_data io_read_gamepad_data() {

  debug_msg(DEBUG_PARTIAL_IO, "io_read_gamepad_data called", false, 0);

    //init loca vars
    struct controler_data current_gamepad_data;
    

    //start reading pins
    current_gamepad_data.ls_x = analogRead(ls_x.pin_number);
    current_gamepad_data.ls_y = analogRead(ls_y.pin_number);
    current_gamepad_data.rs_x = analogRead(rs_x.pin_number);
    current_gamepad_data.rs_y = analogRead(rs_y.pin_number);
    current_gamepad_data.buttons = digitalRead(btn_1.pin_number);
    current_gamepad_data.buttons = ((digitalRead(btn_2.pin_number) << 1) | current_gamepad_data.buttons);
    current_gamepad_data.buttons = ((digitalRead(ls_sw.pin_number) << 2) | current_gamepad_data.buttons);
    current_gamepad_data.buttons = ((digitalRead(rs_sw.pin_number) << 3) | current_gamepad_data.buttons);


    //re bound analogue to +- 2000
    current_gamepad_data.ls_x = map(current_gamepad_data.ls_x, 0, 4095, -2000, 2000);
    current_gamepad_data.ls_y = map(current_gamepad_data.ls_y, 0, 4095, -2000, 2000);
    current_gamepad_data.rs_x = map(current_gamepad_data.rs_x, 0, 4095, -2000, 2000);
    current_gamepad_data.rs_y = map(current_gamepad_data.rs_y, 0, 4095, -2000, 2000);

    return current_gamepad_data;
    
}


#endif // io_cpp