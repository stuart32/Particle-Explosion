#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Vector.h"

class Physics {



public:

	vec3 g = vec3(0.0f, 9.8f, 0.0f);

	vec3 i_velocity;
	vec3 f_velocity;
	float mass;
	vec3 position;
	vec3 acceleration;
	vec3 weight;
	vec3 force;
	int lifetime;


	Physics();

	void setMass(float mass);
	void setPosition(vec3 position);
	void calcForce();
	void calcVelocity(float time);
	void calcAcceleration();
	void calcPosition(float time);
	void updateState(float time);
	float getMass();
	vec3 getPosition();
	vec3 getVelocity();
	vec3 getAcceleration();
	vec3 getForce();
	bool isDead();
	void applyForce(vec3 f);
};