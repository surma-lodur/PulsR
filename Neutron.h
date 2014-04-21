/*
 * File:   Neutron.h
 * Author: mafolz
 *
 * A neutron represents a electric device which should be controlled with
 * high pulses.
 */

#ifndef NEUTRON_H
#define	NEUTRON_H
namespace PulsR {

  class Neutron {
  public:
    unsigned long delta_time_stamp;


    Neutron();
    Neutron(unsigned short step_pin);
    Neutron(unsigned short step_pin, unsigned short direction_pin, unsigned short revert_direction_count);
    virtual ~Neutron();

    void induct(unsigned int delta_time_stamp);
    void impact();
    void pulse();
    bool isEmitting();
    bool isReady();
    bool isEmpty();


  private:

    // MEMO: i wrote this explicite to better comment each variable

    // Represents the pulse emitting pin
    unsigned short step_pin;

    // if the neutron will have a direction which must be handled, this are the pin
    unsigned short direction_pin;
    unsigned short step_counter;
    unsigned short revert_direction_count;

    // signals that the neutron fires
    bool emitts;

    // last time which the neutron emitts an pulse
    unsigned long last_pulse;

    void pulseCallback();

  };
}

#endif	/* NEUTRON_H */

