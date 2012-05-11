/* CS6680_Bezier_Triangle_Interpolation_2.cpp : Defines the entry point for the
 * console application.
 */

//Visual C++ "Wizard" Includes
#include "stdafx.h"

//Standard includes
#include <iostream>

//Third party includes
//OpenGL includes
#include <GL/glew.h>
//Freeglut includes
#include <GL/freeglut.h>

//Project Includes
#include "WindowData.h"

//Function forward declarations
void initGL();
void draw();
void resize(int, int);

//Initialization functions
void initWindow(int argc, _TCHAR* argv[], const BratsGLUtilities::WindowData& winData)
{
	//Initialize glut and pass "command-line" parameters to it.
	glutInit(&argc, (char**) argv);	//TODO: Find out the correct type of C++ 
									//cast to use
	//Initialize an OpenGL context.
	//Get an OpenGL 4.1 compatible context -
	glutInitContextVersion(4, 1);
#ifndef REQUEST_DEBUG_PROFILE
	//which is forward compatible (General) -
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
#else
	//which is forward compatible and a debug context (For debug builds) -
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
#endif
	//and is a core profile context without Fixed Function Pipeline stuff.
	glutInitContextProfile(GLUT_CORE_PROFILE);

	//Tell GLUT to return to the main program on window close.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, 
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//Initialize OpenGL for double buffering, RGBA colour and depth buffering.
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA  | GLUT_DOUBLE);

	//Initialize a GLUT window from the winData struct passed in.
	glutInitWindowSize(winData.width, winData.height);
	
	//Try creating a GLUT window.
	int windowHandle = glutCreateWindow(winData.windowTitle.c_str());
	//See if that worked
	//If window creation failed, report an error and exit with a fail status.
	if(windowHandle < 1)
	{
		std::cerr << "Failed to create rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}

	//Register callbacks.
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);

	//Initialize OpenGL state (and GLEW).
	initGL();
}

void initGL()
{
	/*Initialize GLEW, the OpenGL extension wrangler
	 * so that I can use OpenGL 4 functions and other nice
	 * extensions.
	 */
	GLenum glewInitResult;
	//Try to initialize GLEW.
	glewInitResult = glewInit();
	//Check to see that initialization worked, if not, report the error and
	//exit with a failure status.
	if (glewInitResult != GLEW_OK)
	{
		std::cerr << "ERROR: " << glewGetErrorString(glewInitResult) 
			<< std::endl;
		exit(EXIT_FAILURE);
	}
	//Set up OpenGL state
	//The window should be cleared to black.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//The parameters are GLClampf
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//Depth testing uses GL_LESS as the test function, so the depth buffer
	//should be cleared to 1.0
	glClearDepth(1.0);	//The parameters are GLClampd
	//Enable back face culling - Back face = counterclockwise i.e. the default.
	glEnable(GL_CULL_FACE);
}

//GLUT Callback Implementations
void draw()
{
	//Clear the color and the depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Swap the front and back buffers. (automatically causes OpenGL to work!!)
	glutSwapBuffers();
}

void resize(int width, int height)
{
	//Resize the viewport to fill the whole window
	glViewport(0, 0, width, height);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize a window data struct.
	BratsGLUtilities::WindowData winData("Bezier Triangle Interpolation");
	//Initialize glut and create a window.
	initWindow(argc, argv, winData);
	//Report the OpenGL version
	std::cout << "INFO: OpenGL Version - " << glGetString(GL_VERSION) 
		<< std::endl;
	//Start the GLUT event loop.
	glutMainLoop();
	return 0;
}