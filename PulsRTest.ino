#line 2 "PulsRTest.ino"

#define MAX_STARS 2

#include "PulsR.h"
#include <AUnit.h>

using namespace PulsR;

unsigned long test_millis = 10;

test(Neutron) {
  Neutron *lich = new Neutron();
  assertEqual(lich->isEmitting(), false);
  assertEqual(lich->isEmpty(), true);

  lich = new Neutron(7);
  assertEqual(lich->isEmitting(), false);
  assertEqual(lich->isEmpty(), false);

  lich = new Neutron(7, 8);
  assertEqual(lich->isEmitting(), false);
  assertEqual(lich->isEmpty(), false);

  lich = new Neutron(7, 8, 44);
  assertEqual(lich->isEmitting(), false);
  assertEqual(lich->isEmpty(), false);
}

test(Neutron_isDecayed) {
  Neutron *lich = new Neutron(7);
  lich->induct(100);
  assertEqual(lich->isEmitting(), true);
  assertEqual(lich->isDecayed(), false);

  lich = new Neutron(7);
  lich->induct(100);
  Neutron::decay = test_millis;
  unsigned long start_time = lich->start_time_stamp;
  assertEqual(lich->isEmitting(), true);
  assertEqual(lich->isDecayed(start_time + 0), false);
  assertEqual(lich->isDecayed(start_time + 20), true);
}

test(Neutron_isReleaseFinished) {
  Neutron *lich = new Neutron(7);
  Neutron::release = 0;
  assertEqual(lich->isReleaseFinished(), true);

  lich = new Neutron(7);
  lich->induct(100);
  assertEqual(lich->isReleaseFinished(), true);

  lich = new Neutron(7);
  lich->induct(100);
  Neutron::release = test_millis;
  unsigned long start_time = lich->start_time_stamp;
  assertEqual(lich->isReleaseFinished(start_time + 0), false);
  assertEqual(lich->isReleaseFinished(start_time + 20), true);
}

test(PulsR_add) {
  PulsR::reset();
  Neutron *lich = new Neutron(0);
  PulsR::add(lich);
  assertEqual(PulsR::starsReady(), 0);

  PulsR::add(7);
  assertEqual(PulsR::starsReady(), 1);

  PulsR::reset();
  assertEqual(PulsR::starsReady(), 0);
  PulsR::add(7, 8);
  assertEqual(PulsR::starsReady(), 1);

  PulsR::reset();
  assertEqual(PulsR::starsReady(), 0);
  PulsR::add(7, 8, 44);
  assertEqual(PulsR::starsReady(), 1);
}

test(PulsR_starsReady) {
  PulsR::reset();
  assertEqual(PulsR::starsReady(), 0);
  Neutron *lich = new Neutron(7);
  PulsR::add(lich);
  assertEqual(PulsR::starsReady(), 1);
}

test(PulsR_pulses) {
  PulsR::reset();
  assertEqual(PulsR::pulses(100), false);
  assertEqual(PulsR::starsReady(), 0);

  Neutron *lich = new Neutron(7);
  PulsR::add(lich);
  assertEqual(PulsR::starsReady(), 1);
  assertEqual(PulsR::pulses(100), true);
  assertEqual(PulsR::starsReady(), 0);
  assertEqual(PulsR::pulses(100), false);
}

test(PulsR_collapse) {
  PulsR::reset();
  PulsR::Neutron::release = 0;

  assertEqual(PulsR::starsReady(), 0);
  PulsR::collapse(100);
  assertEqual(PulsR::starsReady(), 0);

  Neutron *lich = new Neutron(7);
  PulsR::add(lich);
  assertEqual(PulsR::starsReady(), 1);
  PulsR::collapse(100);
  assertEqual(PulsR::starsReady(), 1);
  assertEqual(PulsR::pulses(100), true);
  assertEqual(PulsR::starsReady(), 0);

  PulsR::collapse(100);
  assertEqual(PulsR::starsReady(), 1);
}

test(PulsR_rotate) {
  PulsR::reset();
  Neutron *lich = new Neutron(7);
  PulsR::add(lich);
  PulsR::pulses(100);

  PulsR::rotate();
}

void setup() {
#if !defined(EPOXY_DUINO)
  delay(1000); // wait for stability on some boards to prevent garbage Serial
#endif
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only
#if defined(EPOXY_DUINO)
  Serial.setLineModeUnix();
#endif
}

void loop() { aunit::TestRunner::run(); }
