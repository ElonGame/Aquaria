#ifndef BBGE_JOYSTICK_H
#define BBGE_JOYSTICK_H

#include <SDL_joystick.h>

#ifdef BBGE_BUILD_SDL2
#include <SDL_gamecontroller.h>
#include <SDL_haptic.h>
#endif

#include "Vector.h"

#define MAX_JOYSTICK_BTN 32
#define MAX_JOYSTICK_AXIS 32

const static float JOY_AXIS_THRESHOLD = 0.6f;

class Joystick
{
public:
	static unsigned GetNumJoysticks();

	Joystick();
	bool init(int stick=0);
	void shutdown();
	//Ranges from 0 to 1 (full speed).
	void rumble(float leftMotor, float rightMotor, float time);
	void update(float dt);
	Vector position;

	float deadZone1, deadZone2;
	float clearRumbleTime;

	void calibrate(Vector &vec, float dead);
	bool anyButton() const;
	bool getButton(unsigned id) const { return !!(buttonBitmask & (1u << id)); }
	float getAxisUncalibrated(int id) const;
	int getNumAxes() const;
	int getIndex() const { return stickIndex; }
	int getInstanceID() const { return instanceID; }
	inline bool isEnabled() const { return enabled; }

	const char *getAxisName(int axis) const;
	const char *getButtonName(int btn) const;
	const char *getName() const;
	const char *getGUID() const;

	Vector rightStick;

	int s1ax, s1ay, s2ax, s2ay;

private:
	void clearAxes();
	bool enabled;
	int stickIndex;
	int instanceID;
	unsigned buttonBitmask;
	int numJoyAxes;
	SDL_Joystick *sdl_joy;
	float axisRaw[MAX_JOYSTICK_AXIS];
	std::string name;
	std::string guid;

#  ifdef BBGE_BUILD_SDL2
	SDL_GameController *sdl_controller;
	SDL_Haptic *sdl_haptic;
#  endif
};


#endif