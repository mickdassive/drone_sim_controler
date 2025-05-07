#ifndef debug_h
#define debug_h

#include <Arduino.h>

//var defines
enum debug_levels {
    full,
    partal_io,
    no_debug,
    partal_usb
    };
;

//function define
void debug_msg(enum debug_levels debug_level, const char* debug_message, bool include_num, int num_include);
void debug_level_set(enum debug_levels new_debug_level);


#endif // debug_h