#include "Neutron.hpp"
#include <Arduino.h>
#include <stddef.h>

#define NELEMS(x) (sizeof(x) / sizeof(x[0]))

#ifndef MAX_STARS
#define MAX_STARS 12
#endif

namespace PulsR {

static Neutron stars[MAX_STARS];

[[maybe_unused]] static bool add(Neutron *star) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isEmpty()) {
      stars[i] = *star;
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static bool add(unsigned short step_pin) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isEmpty()) {
      stars[i].setStepPin(step_pin);
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static bool add(unsigned short step_pin,
                                 unsigned short direction_pin) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isEmpty()) {
      stars[i].setStepPin(step_pin);
      stars[i].setDirectionPin(direction_pin);
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static bool add(unsigned short step_pin,
                                 unsigned short direction_pin,
                                 unsigned short revert_direction_count) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isEmpty()) {
      stars[i].setStepPin(step_pin);
      stars[i].setDirectionPin(direction_pin);
      stars[i].revert_direction_count = revert_direction_count;
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static unsigned short starsReady() {
  unsigned short count = 0;
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isReady())
      count++;
  }
  return count;
}

[[maybe_unused]] static void inspectStars() {
#ifndef DEBUG
  return;
#else
  Serial.println("PulsR::stars");
  Serial.print("Neutron::decay: ");
  Serial.println(Neutron::decay);

  Serial.print("Neutron::release: ");
  Serial.println(Neutron::release);
  Serial.println("");

  for (unsigned short i = 0; i < MAX_STARS; i++) {
    Serial.print("stars[");
    Serial.print(i);
    Serial.println("]");

    stars[i].inspect();
    Serial.println("");
  }
#endif
}

[[maybe_unused]] static bool pulses(unsigned long delta_micros) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (stars[i].isReady()) {
      stars[i].induct(delta_micros);
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static bool collapse(unsigned long delta_micros) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    if (!stars[i].isReady() && stars[i].delta_time_stamp == delta_micros) {
      stars[i].impact();
      return true;
    }
  }
  return false;
}

[[maybe_unused]] static void rotate() {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    stars[i].pulse(::micros(), ::millis());
  }
}

[[maybe_unused]] static void reset() {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    stars[i].reset();
  }
}

[[maybe_unused]] static void detune(long tune) {
  for (unsigned short i = 0; i < MAX_STARS; i++) {
    stars[i].delta_time_stamp += tune;
  }
}

}; // namespace PulsR
