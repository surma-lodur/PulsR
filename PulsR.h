/*
 * File:   PulsR.h
 * Author: mafolz
 *
 * Created on 19. April 2014, 20:38
 */

#ifndef PULSR_H
#define	PULSR_H

#include <Neutron.h>
#include <stddef.h>

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

#define MAX_STARS 12
#define FLOPPY_SECTORS 44

namespace PulsR {
  static Neutron stars[MAX_STARS];

  static void add(Neutron *star) {
    for (unsigned short i = 0; i < NELEMS(stars); i++) {
      if (stars[i].isEmpty()) {
        stars[i] = *star;
        break;
      }
    }
  }

  static void pulses(long delta_micros) {
    for (unsigned short i = 0; i < NELEMS(stars); i++) {
      if (stars[i].isReady()) {
        stars[i].induct(delta_micros);
        break;
      }
    }
  }

  static void collapse(long delta_micros) {
    for (unsigned short i = 0; i < NELEMS(stars); i++) {
      if (!stars[i].isReady() && stars[i].delta_time_stamp == delta_micros) {
        stars[i].impact();
        break;
      }
    }
  }

  static void rotate() {
    for (unsigned short i = 0; i < NELEMS(stars); i++) {
      stars[i].pulse();
    }
  }

  static void detune(long tune) {
    for (unsigned short i = 0; i < NELEMS(stars); i++) {
      stars[i].delta_time_stamp += tune;
    }

  }

}
#endif	/* PULSR_H */

