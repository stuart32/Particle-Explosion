// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// 
// Update 2018/01 updated libraries and created project for VS2015.

// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <chrono>


#include "graphics.h"
#include "shapes.h"
#include "Physics.h"
#include "Particles.h"

// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Cube		myCube;
Sphere		mySphere;
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;


Particles	p;

float angleY = 0.0f;

float t = 0.001f;			// Global variable for animation

std::chrono::duration<int> s;
std::chrono::duration<float, std::milli> ms;
std::chrono::duration<int, std::ratio<60 * 60>> h;

float deltaTime;



int main()
{

	double lastTime;
	double currentTime = glfwGetTime();

	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).

												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys

																			// MAIN LOOP run until the window is closed
	do {
		lastTime = currentTime;
		currentTime = glfwGetTime();		// retrieve timelapse
		deltaTime = (float)(currentTime - lastTime);
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.

		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0;i < 10;i++) {
		p.particles[i].setMass(1.0f);
		
	}
	p.applyForce();

	myGraphics.SetOptimisations();		// Cull and depth testing
}

void update(double currentTime) {

	// Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/


	

	

	// calculate Sphere movement
	



	t += 0.01f; // increment movement variable

	for (int i = 0;i < (sizeof p.particles / sizeof Physics);i++) {
		if (p.particles[i].lifetime <= 0) {
			p.particles[i].position = p.particles[i].position = vec3(0.0f,0.0f,-20.0f);
			//p.particles[i].force = p.particles[i].force*0;
			p.particles[i].acceleration = p.particles[i].acceleration * 0;
			p.particles[i].i_velocity = p.particles[i].i_velocity * 0;
			p.particles[i].lifetime = 100;
		}
	}

	p.updateState(deltaTime);
	
	
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	for (int i = 0; i < (sizeof p.particles / sizeof Physics); i++) {
		glm::mat4 mv_matrix_sphere =
			glm::translate(glm::vec3(p.particles[i].getPosition().x, p.particles[i].getPosition().y, p.particles[i].getPosition().z)) *
			glm::rotate(t, glm::vec3(0.0f, 0.1f, 0.0f)) *
			glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::mat4(1.0f);
		mySphere.mv_matrix = mv_matrix_sphere;
		mySphere.proj_matrix = myGraphics.proj_matrix;
		mySphere.Draw();
	}
		/*
		glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(p.particles[i].getPosition().x, p.particles[i].getPosition().y, p.particles[i].getPosition().z)) *
		//glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		//glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere;
	mySphere.proj_matrix = myGraphics.proj_matrix;
	}
	
	mySphere.Draw();

	*/
}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}