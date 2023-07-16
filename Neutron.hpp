/*
 * File:   Neutron.h
 * Author: mafolz
 *
 * A neutron represents a electric device which should be controlled with
 * high pulses.
 */

#ifndef NEUTRON_H
#define NEUTRON_H

#ifndef DECAY
#define DECAY 0
#endif

#ifndef RELEASE
#define RELEASE 10
#endif

#ifndef FLOPPY_SECTORS
#define FLOPPY_SECTORS 44
#endif

namespace PulsR {

class Neutron {
public:
  static unsigned short decay;
  static unsigned short release;

  unsigned int delta_time_stamp;
  unsigned long start_time_stamp;
  unsigned short revert_direction_count;

  bool released = false;

  Neutron();
  Neutron(unsigned short step_pin);
  Neutron(unsigned short step_pin, unsigned short direction_pin);
  Neutron(unsigned short step_pin, unsigned short direction_pin,
          unsigned short revert_direction_count);
  virtual ~Neutron();

  void induct(unsigned int delta_time_stamp);
  void impact();
  void pulse(unsigned long current_micros, unsigned long current_millis);
  void pulse(unsigned long current_micros);
  void pulse();
  bool isEmitting();
  bool isReady();
  bool isEmpty();
  bool isDecayed(unsigned long current_millis);
  bool isDecayed();
  bool isReleaseFinished(unsigned long current_millis);
  bool isReleaseFinished();
  void reset();
  void inspect();

  void setStepPin(unsigned short step_pin);
  void setDirectionPin(unsigned short step_pin);

private:
  // MEMO: i wrote this explicite to better comment each variable

  // Represents the pulse emitting pin
  unsigned short step_pin;

  // if the neutron will have a direction which must be handled, this are the
  // pin
  unsigned short direction_pin;
  unsigned short step_counter;

  // signals that the neutron fires
  bool emitts;

  // last time which the neutron emitts an pulse
  unsigned long last_pulse;

  void pulseCallback();
};
} // namespace PulsR

#endif /* NEUTRON_H */
