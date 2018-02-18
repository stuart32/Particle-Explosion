#pragma once

#include "Physics.h"

class Particles {

public:
	Physics particles[100];
	Particles();



	void updateState(float time);
	void applyForce();
};