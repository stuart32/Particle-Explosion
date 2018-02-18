#pragma once

#include "Physics.h"
#include "Particles.h"
#include "Vector.h"



	Physics particles[100];

	Particles::Particles() {
		particles[100];
	};

	void Particles::updateState(float time) {
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			particles[i].updateState(time);
		}
	};

	void Particles::applyForce() {
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			vec3 force = vec3((rand() % 1500 - 750) / 10000.0f, (rand() % 1500 - 750) / 10000.0f, (rand() % 1500 - 750) / 10000.0f).unit();
			particles[i].applyForce(force*10);
		}
	};