/*****************************************************************************************************************************\

@file			CbxButton.cpp
@version		1.0
@author			Jiri Kosar
@editor			Notepad++
@git			https://github.com/Combinatix/CbxButton
@description
	Class for reading a pull-down button on a single pin

@methods
	CbxButton(int pin);					// Constructor (requires pin number)
	unsigned long debounceTime = 20;	// Debounce time in ms (R/W, Optional)
	unsigned long holdAfter = 1000;		// Time in ms after which the Buton.hold() returns true (R/W, Optional)
	void scan();						// Scan the button. Call as often as possible.
	bool down();						// Returns true if button was pressed. Reading clears the flag!
	bool up();							// Returns true if button was released. Reading clears the flag!
	bool hold();						// Returns true if button was pressed for longer than holdAfter. Reading clears the flag!
	unsigned long pressTime();			// Returns how long the button is / was pressed in ms
	bool isDown();						// Returns true if button is pressed

\*****************************************************************************************************************************/

#include "Arduino.h"
#include "CbxButton.h"

unsigned long debounceTime = 20;						// debounce time in ms
unsigned long holdAfter = 1000;							// time in ms after which the Buton.hold returns true

CbxButton::CbxButton(int pin){							// constructor
	_pin = pin;
	pinMode(_pin, INPUT_PULLUP);
}

void CbxButton::scan(){									// scan as often as possible
	bool x = digitalRead(_pin) == LOW;					// active = LOW
	if (x != _prevState){								// if button state has changed
		_lastChange = millis();							// store current time
		_prevState = x;									// store current state
		return;											// and return
	}
	unsigned long t = millis() - _lastChange;			// calculate time since last change
	if (t < debounceTime) return;						// if time is less than debounce, do nothing and return
	if (x && !_pressed){								// ### DOWN EVENT ###
		_pressed = true;								// change current button state
		_holdTime = _lastChange;						// store timestamp
		_down = true;									// set _down flag
		_waiting = true;								// set waiting for hold
	} else if (!x && _pressed){							// ### UP EVENT ###
		_pressed = false;								// change current button state
		_waiting = false;								// clear waiting flag
		_holdTime = _lastChange - _holdTime;			// calculate total value of _holdTime
		_up = true;										// set the flag
	} else if (_waiting && pressTime()>=holdAfter){		// ### HOLD EVENT ###
		_waiting = false;
		_hold = true;
	}
}

bool CbxButton::down(){									// Returns true if button was pressed. Reading clears the flag
	noInterrupts();										// disabling interrupts is important only when Button.scan() is fired by timer and events are read in loop().
	bool val = _down;
	_down = false;
	interrupts();
	return val;
}

bool CbxButton::up(){									// Returns true if button was released
	noInterrupts();
	bool val = _up;
	_up = false;
	interrupts();
	return val;
}

bool CbxButton::hold(){									// Returns true if button was pressed for longer than holdAfter
	noInterrupts();
	bool val = _hold;
	_hold = false;
	interrupts();
	return val;
}

unsigned long CbxButton::pressTime(){					// Returns how long the button was pressed
	return _pressed ? millis() - _holdTime : _holdTime;
}

bool CbxButton::isDown(){								// Returns true if the button is pressed.
	return _pressed;
}