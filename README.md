# CbxButton
### Arduino family - Class for reading a pull-down button on a single pin with debouncing

it provides following functionality

```
CbxButton(int pin);                 // Constructor (requires pin number)
unsigned long debounceTime = 20;    // Debounce time in ms (R/W, Optional)
unsigned long holdAfter = 1000;     // Time in ms after which the Buton.hold returns true (R/W, Optional)
void scan();                        // Scan the button. Call as often as possible.
bool down();                        // Returns true if button was pressed. Reading clears the flag!
bool up();                          // Returns true if button was released. Reading clears the flag!
bool hold();                        // Returns true if button was pressed for longer than holdAfter. Reading clears the flag!
unsigned long pressTime();          // Returns how long the button is / was pressed in ms
bool isDown();                      // Returns true if button was pressed during last scan
```

Example of use:

```
#include "CbxButton.h"

CbxButton btn(3);                           // Button on pin 3, int

void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    // Following options are optional :
    btn.debounceTime = 25;                  // Debounce time in ms. Default value is 20 ms. Read / Write, unsigned long
    btn.holdAfter = 800;                    // Time after which the btn.hold() will occur. Default is 1000 ms. Read / Write, unsigned long
}

void loop(){
    btn.scan();
    if (btn.down()){                        // Button has been pressed. Boolean
        Serial.println("Down!");
    }
    if (btn.hold()){                        // Button is being hold for longer than holdAfter(). Boolean
        Serial.println("Hold!");
    }
    if (btn.up()){                          // Button is released. pressTime() returns the time between down(); and up(); in ms. Boolean
        Serial.print("Up! pressTime() = ");
        Serial.print(btn.pressTime());      // Returns unsigned long
        Serial.println(" ms");
    }
    digitalWrite(LED_BUILTIN, btn.isDown());
}
```
