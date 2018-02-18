#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>

#include "Physics.h"
#include "Vector.h"

vec3 g = vec3(0.0f, -9.8f, 0.0f);


float mass;
vec3 i_velocity = vec3(0.0f,0.0f,0.0f);
vec3 f_velocity = vec3(0.0f, 0.0f, 0.0f);
vec3 position = vec3(0.0f, 0.0f, -20.0f);
vec3 acceleration = vec3(0.0f, 0.0f, 0.0f);
vec3 weight = vec3(0.0f, 0.0f, 0.0f);
vec3 force = vec3(0.0f, 0.0f, 0.0f);

Physics::Physics() {
	g = vec3(0.0f, -9.8f, 0.0f);
	 i_velocity = vec3(0.0f, 0.0f, 0.0f);
	 f_velocity = vec3(0.0f, 0.0f, 0.0f);
	 position = vec3(0.0f, 0.0f, -20.0f);
	 acceleration = vec3(0.0f, 0.0f, 0.0f);
	 weight = vec3(0.0f, 0.0f, 0.0f);
	 force = vec3(0.0f, 0.0f, 0.0f);
	 int lifetime = 150;

}




void Physics::setMass(float m){
	mass = m;
	weight = g*(m);
};


void Physics::setPosition(vec3 p) {
	position = p;
};


void Physics::calcPosition(float time) {
	vec3 t_velocity = i_velocity.operator+(f_velocity);
	vec3 displacement = t_velocity.operator*((float)time).operator/(2);
	position = position.operator+(displacement);
};



void Physics::calcForce() {
	
	force = force;
	
	
};


void Physics::calcAcceleration() {
	acceleration = force.operator/(mass);
};


void Physics::calcVelocity(float time) {
	f_velocity = i_velocity + acceleration.operator*(time);
};

void Physics::updateState(float time) {
	calcForce();
	calcAcceleration();
	calcVelocity(time);
	calcPosition(time);
	acceleration = acceleration * 0;
	force - force * 0;
	i_velocity = f_velocity;
	lifetime = lifetime - 1;
};

bool Physics::isDead() {
	if (lifetime == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Physics::applyForce(vec3 f) {
	force = force + f;
}


float Physics::getMass() {
	return mass;
};

vec3 Physics::getPosition() {
	return position;
};

vec3 Physics::getVelocity() {
	return i_velocity;
}

vec3 Physics::getAcceleration() {
	return acceleration;
};

vec3 Physics::getForce() {
	return force;
};







