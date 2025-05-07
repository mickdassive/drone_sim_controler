

#ifndef debug_cpp
#define debug_cpp

#include <Arduino.h>
#include "debug.h"

//var defines
enum debug_levels debug_level = no_debug;

//functions

/**
 * @brief Prints a debug message with optional attached value.
 * 
 * This function prints a debug message along with the current millis() value. 
 * The debug message can be customized based on the debug level provided.
 * 
 * @param message_debug_level The debug level for the message.
 * @param debug_message The debug message to be printed.
 * @param include_num Flag indicating whether to include an attached value.
 * @param num_include The attached value to be printed (if include_num is true).
 */
void debug_msg(enum debug_levels message_debug_level, const char* debug_message, bool include_num, int num_include) {
    if (debug_level != no_debug) {
        switch (message_debug_level) {
            case full:
                Serial.print("debug msg at millis: ");
                Serial.print(millis());
                Serial.print("| ");
                if (include_num) {
                    Serial.print(debug_message);
                    Serial.print("  | attached value: ");
                    Serial.println(num_include);
                } else {
                    Serial.println(debug_message);
                }
                break;
            case partal_io:
                Serial.print("debug msg at millis: ");
                Serial.print(millis());
                Serial.print("| ");
                if (include_num) {
                    Serial.print(debug_message);
                    Serial.print("  | attached value: ");
                    Serial.println(num_include);
                } else {
                    Serial.println(debug_message);
                }
                break;
            case partal_usb:
                Serial.print("debug msg at millis: ");
                Serial.print(millis());
                Serial.print("| ");
                if (include_num) {
                    Serial.print(debug_message);
                    Serial.print("  | attached value: ");
                    Serial.println(num_include);
                } else {
                    Serial.println(debug_message);
                }
                break;
            case no_debug:
                break;
        }
    }
}

void debug_level_set(enum debug_levels new_debug_level) {
    debug_level = new_debug_level;
}



#endif // debug_cpp