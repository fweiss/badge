#ifndef STD_THROW_HANDLERS
#define STD_THROW_HANDLERS

/*
 * Define throw handlers for std libraries. Need for <vector>, etc.
 *
 * Not sure if there is an existing way to support this. The ESP8266 libraries have abi.h.
 *
 * see https://forum.pjrc.com/threads/23467-Using-std-vector?p=69787&viewfull=1#post69787
 */

#ifndef ARDUINO_ARCH_ESP32
namespace std {
  void __throw_bad_alloc()  {
    Serial.println("Unable to allocate memory");
  }

  void __throw_length_error(char const *e) {
    Serial.print("Length Error :");
    Serial.println(e);
  }
  void __throw_out_of_range(char const *e) {
    Serial.print("Out of range Error :");
    Serial.println(e);
  }
}
#endif ARDUINO_ARCH_ESP32

#endif STD_THROW_HANDLERS
