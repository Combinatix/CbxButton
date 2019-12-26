/*****************************************************************************************************************************\

@file			CbxButton.h
@version		1.0
@author			Jiri Kosar
@editor			Notepad++
@git			https://github.com/Combinatix/CbxButton
@description
	Class for reading a pull-down button on a single pin

@methods
	CbxButton(int pin);					// Constructor
	unsigned long debounceTime = 20;	// Debounce time in ms
	unsigned long holdAfter = 1000;		// Time in ms after which the Buton.hold returns true
	void scan();						// Scan the button. Call as often as possible.
	bool down();						// Returns true if button was pressed. Reading clears the flag!
	bool up();							// Returns true if button was released. Reading clears the flag!
	bool hold();						// Returns true if button was pressed for longer than holdAfter. Reading clears the flag
	unsigned long pressTime();			// Returns how long the button is / was pressed in ms
	bool isDown();						// Returns true if button is was pressed during last scan

\*****************************************************************************************************************************/

#ifndef CBXBUTTON_H
#define CBXBUTTON_H

#include <Arduino.h>

class CbxButton{						// Class for reading a pull-down button on single pin
public:
	CbxButton(int pin);					// Constructor
	unsigned long debounceTime = 20;	// Debounce time in ms
	unsigned long holdAfter = 1000;		// Time in ms after which the Buton.hold returns true
	void scan();						// Scan the button. Call as often as possible.
	bool down();						// Returns true if button was pressed. Reading clears the flag
	bool up();							// Returns true if button was released. Reading clears the flag
	bool hold();						// Returns true if button was pressed for longer than holdAfter. Reading clears the flag
	unsigned long pressTime();			// Returns how long the button is pressed in ms
	bool isDown();						// Returns true if button is / was pressed during last scan

private:
	unsigned long _lastChange;			// Last state change time
	unsigned long _holdTime;			// How long the button is being held
	int  _pin;							// Button pin
	bool _pressed;						// Millis() value since _down detected
	bool _prevState;					// Previous state
	bool _down;							// Is pressed flag
	bool _up;							// Is released flag
	bool _hold;							// Is hold flag
	bool _waiting = false;				// Is waiting for hold flag
};

#endif