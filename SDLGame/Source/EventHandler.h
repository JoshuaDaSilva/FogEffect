#pragma once
#include "SDL.h"

enum ControlsEvents
{
	W_PRESSED,
	A_PRESSED,
	S_PRESSED,
	D_PRESSED,
	E_PRESSED,
	Q_PRESSED,

	R_PRESSED,

	Z_PRESSED,
	X_PRESSED,

	UP_PRESSED,
	RIGHT_PRESSED,
	LEFT_PRESSED,
	DOWN_PRESSED,

	DEL_PRESSED,
	PGDOWN_PRESSED,

	K_PRESSED,
	J_PRESSED,
	O_PRESSED,
	P_PRESSED,
	U_PRESSED,
	I_PRESSED,

	NUM_CONTROLS_EVENTS

};

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static bool Update();

	static bool events[ControlsEvents::NUM_CONTROLS_EVENTS];
private:

	static void SetButton(ControlsEvents eventNum, bool pressed);
};


