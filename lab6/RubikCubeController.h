#pragma once

#ifndef _RUBIKCUBE_H_INCLUDED_
#define _RUBIKCUBE_H_INCLUDED_

using namespace std;

#define MODE_OPENGL
//#define MODE_COMMAND_LINE

#include <list>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <ostream>

#ifdef MODE_OPENGL

#include <windows.h>
#include <mmsystem.h>
#include <timeapi.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

#endif

#include "TestRunner.h"
#include "CubeTransformData.h"
#include "ISolutionPhase.h"
#include "MovingWhiteCellUpToCenterPhase.h"
#include "MovingTopCornersPhase.h"
#include "MovingCornerWhiteDownPhase.h"
#include "MovingSideCentersPhase.h"
#include "MovingBottomCentersPhase.h"
#include "MovingBottomCornersPhase.h"
#include "CheckSolvedCubePhase.h"
#include "GeometryProvider.h"
#include "matrix4x4f.h"
#include "vector3f.h"
#include "CubeModel.h"
#include "CubeTransform.h"
#include "RuleEngine.h"
#include "SolutionStrategy.h"

struct Vertex
{
	unsigned char r, g, b, a;
	float x, y, z;
};

struct cubeSide
{
	double deg, degx, degy, degz;
}; 

struct HelpCommands
{
	char *line;
};

struct history
{
	char step[16];
};

class RubikCubeController
{
	public:
		RubikCubeController(void);
		CubeModel* getCube();
		void init(void);
		void shutDown(void);
		void refreshCube(void);
		void setColorGrid(int lap, int sorszam, double red, double green, double blue);
		void rotateColorSide(int num);
		void cAddQueue(char *cmd);                    // Add rotate command to queue
		void loadCubeColors();                        // Restore saved cube (from in-memory oldCube)
		void saveCubeColors();                        // Save active cube's state into in-memory oldCube
		void updateViewMatrix( void );
		void getRealTimeUserInput( void );            // Get mouse and keyboard input while traveling
		void render( void );                          // Render screen
		void setRotatingStep(int step);               // Set queue pointer - animation will be started by pulling the next item from queue
		void setRotatingSpeed(int rotatingSpeed);     // Increase or decrease rotating speed
		void setWarning(char* text);                  // Set warning message to be displayed on the top-left of the screen
		void setTravelSpeed(float speed);             // Set traveling speed
		void setStepCount(int step);                  // Set the number of valid commands in rotation command queue
		int getStepCount();

	private:
		CubeModel cube;                               // Active cube we are working on
		CubeModel oldCube;                            // Temporary cube we can work on
#ifdef MODE_OPENGL
		GeometryProvider* geometryProvider;           // Provides rendering functions
		POINT  g_ptLastMousePosit;
		POINT  g_ptCurrentMousePosit;
#endif
		int rotating;
		int rotatingStep;
		int rotatingSpeed;
		int rotatingSpeedCurrent;
		vector3f g_vEye;
		vector3f g_vLook;                             // Look Vector
		vector3f g_vUp;                               // Up Vector
		vector3f g_vRight;                            // Right Vector
		vector3f g_vGravity;
		vector3f g_vView;
		bool   g_bMousing;
		float  g_fMoveSpeed;
		float g_fMoveSpeed_turn;
		float g_fMoveSpeed_Travel;
		float g_fMoveSpeed_Travel_small;
		int stillRotate;
		char warning[256];                            // Warning message to be displayed on screen (bottom right, above commands)
		history history[500];                         // Rotate command queue
		int changed;
		float speed;                                  // Traveling speed
		int step;                                     // Number of valid items in rotation command queue
};

RubikCubeController* getRubikCubeController();
SolutionStrategy* getSolutionStrategy();

#ifdef MODE_OPENGL

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif

#endif