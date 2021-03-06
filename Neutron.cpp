/*
 * File:   Neutron.cpp
 * Author: mafolz
 *
 */

#include "Neutron.h"
#include <Arduino.h>
namespace PulsR {

  Neutron::Neutron() {
    this->step_pin = 0;
    this->emitts = false;
    return;
  }

  Neutron::Neutron(unsigned short step_pin) {
    this->step_pin = step_pin;
    this->emitts = false;
    this->direction_pin = 0;
    ::pinMode(this->step_pin, OUTPUT);
    ::digitalWrite(this->step_pin, LOW);
    return;
  }

  Neutron::Neutron(unsigned short step_pin, unsigned short direction_pin, unsigned short revert_direction_count) {
    this->step_pin = step_pin;
    this->direction_pin = direction_pin;
    this->revert_direction_count = revert_direction_count;
    this->step_counter = 0;
    this->emitts = false;
    ::pinMode(this->step_pin, OUTPUT);
    ::digitalWrite(this->step_pin, LOW);
    ::pinMode(this->direction_pin, OUTPUT);
    ::digitalWrite(this->direction_pin, LOW);
    return;
  }

  void Neutron::induct(unsigned int delta_time_stamp) {
    this->delta_time_stamp = delta_time_stamp;
    this->emitts = true;
    this->last_pulse = ::micros();
    return;
  }

  void Neutron::impact() {
    this->emitts = false;
    return;
  }

  void Neutron::pulse() {
    if (this->isEmitting() && ((::micros() - this->last_pulse) > this->delta_time_stamp)
            ) {
      ::digitalWrite(this->step_pin, !::digitalRead(this->step_pin));
      this->pulseCallback();
      this->last_pulse = ::micros();
    }
    return;
  }

  bool Neutron::isEmitting() {
    return (this->emitts && this->step_pin > 0);
  }

  bool Neutron::isReady() {
    return ((!this->emitts) && this->step_pin > 0);
  }

  bool Neutron::isEmpty() {
    return this->step_pin == 0;
  }

  void Neutron::pulseCallback() {
    if (this->direction_pin != 0) {
      this->step_counter++;
      if (this->step_counter > this->revert_direction_count) {
        ::digitalWrite(this->direction_pin, !::digitalRead(this->direction_pin));
        this->step_counter = 0;
      }
    }
    return;
  }

  Neutron::~Neutron() {
  }
}
