PulsR
=====


An Arduino Library to control electronic devices with HIGH pulses to produce tones.
It is usefull to handle multiple digital pins, which should emit different PWM signals.


```cpp

#define MAX_STARS       12  // maximum size an PWM emitting instances

#include <PulsR.h>

PulsR::Neutron::decay   =  0; // Decay value, Zero will be handled as continuous
PulsR::Neutron::release = 10; // Minimum an miliseconds to produce the PWM

PulsR::add(7);        // Add a PWM on pin 7
PulsR::add(8, 9);     // Add a PWM on pin 8, with direction change on pin 9
PulsR::add(8, 9, 44); // Add a PWM with direction change after 44 steps
// PulsR::add will return true on success and false if MAX_STARS reached

PulsR::pulse(100);    // Starts a PWM on any available entry with a period of 100 microseconds
// PulsR::pulse will return true if a entry was available to play

PulsR::collapse(100); // Starts a PWM which is emitting with a period of 100 microseconds

PulsR::rotate();      // Handles the PWM emitting by going through all emitting entries
```


## Development and Testing

[EpoxyDuino](https://github.com/bxparks/EpoxyDuino) for Tests recommended.


Use the **test** target for testing with EpoxyDuino.

```
make test
```

Use the **native_test** target for testing with a Arduino.
