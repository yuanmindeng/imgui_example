#pragma once
#pragma once

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include <stdio.h>
#include <iostream>
#include <memory>



/*
The class representing the Bezier Curve application.
*/
class Application
{

public:
	
	static std::shared_ptr<Application> _staticInstance;
	// The reference to the window
	GLFWwindow * _window;
	/*
	Constructor of the class.
	*/
	Application();

	/*
	Destructor of the class.
	*/
	~Application();

	/*
	Removes everything from the screen.
	*/
	void ClearAll();

	/*
	Renders the content of the application.
	*/
	void Draw();

	/*
	Renders the user interface.
	*/
	void DrawUI();


	void Update();
	/*
	Initialize the objects of the application.
	*/
	void Init();

	/*
	Returns a static instance of the application.
	*/
	static std::shared_ptr<Application> GetInstance();

	/*
	The callback function for error events.
	@param int error
	@param const char * description
	*/
	static void ErrorCallback(int error, const char * description);



	/*
	Runs the application.
	@param int argc
	@param char ** argv
	*/
	static int Run(int argc, char ** argv);

protected:
	// The width of the window
	double _windowWidth = 1280;

	// The height of the window
	double _windowHeight = 720;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};

#endif
