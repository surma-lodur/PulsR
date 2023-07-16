/*
 * File:   Neutron.cpp
 * Author: mafolz
 *
 */

#include "Neutron.hpp"
#include <Arduino.h>
namespace PulsR {

#ifndef OUTPUT
#define OUTPUT true
#endif

unsigned short Neutron::decay = DECAY;
unsigned short Neutron::release = RELEASE;

Neutron::Neutron() {
  this->start_time_stamp = 0;
  this->delta_time_stamp = 0;

  this->step_pin = 0;
  this->direction_pin = 0;

  this->revert_direction_count = 0;
  this->step_counter = 0;

  this->emitts = false;
  this->released = false;
}

Neutron::Neutron(unsigned short step_pin) : Neutron::Neutron() {
  this->step_pin = step_pin;
  ::pinMode(this->step_pin, OUTPUT);
  ::digitalWrite(this->step_pin, LOW);
}

Neutron::Neutron(unsigned short step_pin, unsigned short direction_pin,
                 unsigned short revert_direction_count)
    : Neutron::Neutron(step_pin) {
  this->revert_direction_count = revert_direction_count;
  this->direction_pin = direction_pin;
  ::pinMode(this->direction_pin, OUTPUT);
  ::digitalWrite(this->direction_pin, LOW);
}

Neutron::Neutron(unsigned short step_pin, unsigned short direction_pin)
    : Neutron::Neutron(step_pin, direction_pin, FLOPPY_SECTORS) {}

void Neutron::induct(unsigned int delta_time_stamp) {
  this->start_time_stamp = ::millis();
  this->delta_time_stamp = delta_time_stamp;
  this->emitts = true;
  this->last_pulse = ::micros();
#ifdef DEBUG
  Serial.println("induct");
  this->inspect();
#endif
  return;
}

void Neutron::impact() {
#ifdef DEBUG
  Serial.println("impact");
  this->inspect();
#endif
  if (this->isReleaseFinished()) {
    this->emitts = false;
    this->released = false;
  } else {
    this->released = true;
  }
  return;
}

void Neutron::pulse(unsigned long current_micros,
                    unsigned long current_millis) {
  if (this->isEmitting()) {

    if ((current_micros - this->last_pulse) > this->delta_time_stamp) {
      ::digitalWrite(this->step_pin, !::digitalRead(this->step_pin));
      this->pulseCallback();
      this->last_pulse = current_micros;
    }

    if ((this->released && this->isReleaseFinished(current_millis)) ||
        this->isDecayed(current_millis)) {
      this->impact();
    }
  }

  return;
}

void Neutron::pulse(unsigned long current_micros) {
  this->pulse(current_micros, current_micros / 1000);
}

void Neutron::pulse() { this->pulse(::micros()); }

void Neutron::reset() {
  this->step_pin = 0;
  this->emitts = false;
}

void Neutron::inspect() {
  Serial.print("Neutron::decay: ");
  Serial.println(Neutron::decay);

  Serial.print("Neutron::release: ");
  Serial.println(Neutron::release);
  Serial.println("");

  Serial.print("> delta_time_stamp: ");
  Serial.println(this->delta_time_stamp);

  Serial.print("> start_time_stamp: ");
  Serial.println(this->start_time_stamp);

  Serial.print("> last_pulse: ");
  Serial.println(this->last_pulse);

  Serial.print("> released: ");
  Serial.println(this->released);

  Serial.print("> isReady(): ");
  Serial.println(this->isReady());

  Serial.print("> isEmitting(): ");
  Serial.println(this->isEmitting());

  Serial.print("> isEmpty(): ");
  Serial.println(this->isEmpty());

  Serial.print("> isDecayed(): ");
  Serial.println(this->isDecayed());
}

void Neutron::setStepPin(unsigned short step_pin) {
  this->step_pin = step_pin;
  ::pinMode(this->step_pin, OUTPUT);
  ::digitalWrite(this->step_pin, LOW);
};

void Neutron::setDirectionPin(unsigned short step_pin) {
  this->direction_pin = direction_pin;
  ::pinMode(this->direction_pin, OUTPUT);
  ::digitalWrite(this->direction_pin, LOW);
};

bool Neutron::isReleaseFinished(unsigned long current_millis) {
  return (Neutron::release == 0 ||
          ((Neutron::release > 0) &&
           (current_millis - this->start_time_stamp > Neutron::release)));
}

bool Neutron::isReleaseFinished() {
  return this->isReleaseFinished(::millis());
}

bool Neutron::isDecayed(unsigned long current_millis) {
  if (Neutron::decay == 0)
    return false;
  return (current_millis - this->start_time_stamp > Neutron::decay);
}

bool Neutron::isDecayed() { return this->isDecayed(::millis()); }

bool Neutron::isEmitting() { return (this->emitts && this->step_pin > 0); }

bool Neutron::isReady() { return ((!this->emitts) && this->step_pin > 0); }

bool Neutron::isEmpty() { return this->step_pin == 0; }

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

Neutron::~Neutron() {}
} // namespace PulsR
