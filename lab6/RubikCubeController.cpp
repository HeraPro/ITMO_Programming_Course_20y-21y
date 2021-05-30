#define STRICT
#define WIN32_LEAN_AND_MEAN

#include "RubikCubeController.h"

RubikCubeController rubikCubeController;
SolutionStrategy* solutionStrategy = new SolutionStrategy(new RuleEngine(rubikCubeController.getCube()), rubikCubeController.getCube());

RubikCubeController* getRubikCubeController() 
{
	return &rubikCubeController;
}

SolutionStrategy* getSolutionStrategy() 
{
	return solutionStrategy;
}

float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

double g_fSpeedmodifier = 0.0001f;

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
#ifdef MODE_OPENGL

HWND  g_hWnd = NULL;
HDC   g_hDC  = NULL;
HGLRC g_hRC  = NULL;

int WINAPI WinMain( HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR     lpCmdLine,
				   int       nCmdShow )
{
	WNDCLASSEX winClass = {0}; 
	MSG        uMsg;

	memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if (!RegisterClassEx(&winClass)) {
		MessageBox(NULL, "Class registration has failed!", "Error!", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
		"Rubik's cube",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;


	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );

	rubikCubeController.init();

	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
		else
		{
			g_dCurrentTime = timeGetTime();
			g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
			g_dLastTime    = g_dCurrentTime;

			//_sleep(40);
			rubikCubeController.render();
		}
	}

	rubikCubeController.shutDown(); 

	UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );


	return uMsg.wParam;
}

#endif

#ifdef MODE_OPENGL
//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							UINT   msg, 
							WPARAM wParam, 
							LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'M':
				srand (timeGetTime());
				rubikCubeController.getCube()
					->getTransformEngine()->stopRotating();         // to register cTransform

				rubikCubeController.saveCubeColors();
				rubikCubeController.setStepCount(0);                // collecting graphical movements from 0 index
				rubikCubeController.getCube()->getTransformEngine()->cTransformN(rand()%16);  // random transformation saved to history
				rubikCubeController.loadCubeColors();  

				rubikCubeController.getCube()
					->getTransformEngine()->startRotating();        // enable instant rotation (no graphics movements)
				rubikCubeController.setRotatingStep(-1);            // put history index to -1
				break;

			case '2': 
				rubikCubeController.saveCubeColors();                // save current cube. solutionStrategy will do transformations on it
				rubikCubeController.setStepCount(0);                 // start step count from zero
				rubikCubeController.setRotatingStep(0);
				rubikCubeController.getCube()
					->getTransformEngine()->stopRotating();          // no graphical movements allowed
				
				if(solutionStrategy->run())                          // solve cube. this will make transformations on current cube
				{
					rubikCubeController.getCube()->getTransformEngine()->startRotating();      // graphics movements are allowed
					rubikCubeController.loadCubeColors();            // restore cube state to the one that should be solved

					rubikCubeController.setRotatingStep(-1);         // put history pointer back, next one is first one (index 0)

				} else rubikCubeController.setWarning("Error: unable to solve cube");
				break;
			case '9':
				rubikCubeController.setRotatingSpeed(10.0);
				break;
			case '8':
				rubikCubeController.setRotatingSpeed(6.0);
				break;
			case '7':
				rubikCubeController.setRotatingSpeed(3.0);
				break;
			case '6':
				rubikCubeController.setRotatingSpeed(1.0);
				break;

			case 'Q': rubikCubeController.getCube()->getTransformEngine()->cTransformN(0); break;
			case 'W': rubikCubeController.getCube()->getTransformEngine()->cTransformN(1); break;
			case 'E': rubikCubeController.getCube()->getTransformEngine()->cTransformN(2); break;
			case 'R': rubikCubeController.getCube()->getTransformEngine()->cTransformN(3); break;
			case 'T': rubikCubeController.getCube()->getTransformEngine()->cTransformN(4); break;
			case 'Z': rubikCubeController.getCube()->getTransformEngine()->cTransformN(5); break;
			case 'U': rubikCubeController.getCube()->getTransformEngine()->cTransformN(6); break;
			case 'I': rubikCubeController.getCube()->getTransformEngine()->cTransformN(7); break;
			case 'O': rubikCubeController.getCube()->getTransformEngine()->cTransformN(8); break;
			case 'P': rubikCubeController.getCube()->getTransformEngine()->cTransformN(9); break;
			case 'A': rubikCubeController.getCube()->getTransformEngine()->cTransformN(10); break;
			case 'S': rubikCubeController.getCube()->getTransformEngine()->cTransformN(11); break;
			case 'D': rubikCubeController.getCube()->getTransformEngine()->cTransformN(12); break;
			case 'F': rubikCubeController.getCube()->getTransformEngine()->cTransformN(13); break;
			case 'G': rubikCubeController.getCube()->getTransformEngine()->cTransformN(14); break;
			case 'H': rubikCubeController.getCube()->getTransformEngine()->cTransformN(15); break;
			case 'J': rubikCubeController.getCube()->getTransformEngine()->cTransformN(16); break;
			case 'K': rubikCubeController.getCube()->getTransformEngine()->cTransformN(17); break;

			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			case VK_SPACE:
				rubikCubeController.setTravelSpeed(0);
				break;

			case VK_F1:
				g_fSpeedmodifier += 0.0001;
				break;

			case VK_F2:
				g_fSpeedmodifier -= 0.0001;
				break;
			}
		}
		break;
	case WM_SIZE:
		{
			int nWidth  = LOWORD(lParam); 
			int nHeight = HIWORD(lParam);
			glViewport(0, 0, nWidth, nHeight);

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( 45.0f, (float) (800 / 600), 3.0f, 100.0f);

		}
		break;
	case WM_CLOSE:
		{
			PostQuitMessage(0); 
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

#endif

CubeModel* RubikCubeController::getCube()
{
	return &cube;
}

RubikCubeController::RubikCubeController(void)
{
#ifdef MODE_OPENGL
	geometryProvider = new GeometryProvider();
#endif
	rotating = -1;
	rotatingStep = -1;
	rotatingSpeed = 3.0;
	rotatingSpeedCurrent = 3.0;
	stillRotate = 0;
	changed = 0;
	speed = 0.0f;
	step = 0;

	g_vEye.x = 10.0; g_vEye.y = 5.0; g_vEye.z = 10.0;
	g_vLook.x = -0.66; g_vLook.y = -0.28; g_vLook.z = -0.69;
	g_vUp.x = 0.0f; g_vUp.y = 1.0f; g_vUp.z = 0.0f;
	g_vRight.x = 1.0f; g_vRight.y = 0.0f; g_vRight.z = 0.0f;
	g_vGravity.x = 0.0f; g_vGravity.z = 0.0f; g_vGravity.z = 0.0f;
	g_vView.x = -0.66; g_vView.y = -0.28; g_vView.z = -0.69;

	/*g_ptLastMousePosit;
	g_ptCurrentMousePosit;*/
	g_bMousing = false;
	g_fMoveSpeed = 0.6f;
	g_fMoveSpeed_turn = 1.0f;
	g_fMoveSpeed_Travel = 2;
	g_fMoveSpeed_Travel_small = 1.5;
}

void RubikCubeController::setTravelSpeed(float travelSpeed)
{
	speed = travelSpeed;
}

void RubikCubeController::setWarning(char* text)
{
	sprintf(warning, text);
}

void RubikCubeController::setRotatingStep(int step)
{
	rotatingStep = step;
}

int RubikCubeController::getStepCount()
{
	return step;
}

void RubikCubeController::setStepCount(int stepCount)
{
	step = stepCount;
}

void RubikCubeController::setRotatingSpeed(int speed) 
{
	rotatingSpeed = speed;
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------

void RubikCubeController::init( void )
{
#ifdef MODE_OPENGL
	GLuint PixelFormat;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	g_hDC = GetDC( g_hWnd );
	PixelFormat = ChoosePixelFormat( g_hDC, &pfd );
	SetPixelFormat( g_hDC, PixelFormat, &pfd);
	g_hRC = wglCreateContext( g_hDC );
	wglMakeCurrent( g_hDC, g_hRC );
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 800.0f / 600.0f, 3.0f, 100.0f);
#endif

}


//-----------------------------------------------------------------------------
// Name : updateViewMatrix() 
// Desc : Builds a view matrix suitable for OpenGL.
//
// Here's what the final view matrix should look like:
//
//  |  rx   ry   rz  -(r.e) |
//  |  ux   uy   uz  -(u.e) |
//  | -lx  -ly  -lz   (l.e) |
//  |   0    0    0     1   |
//
// Where r = Right vector
//       u = Up vector
//       l = Look vector
//       e = Eye position in world space
//       . = Dot-product operation
//
//-----------------------------------------------------------------------------
void RubikCubeController::updateViewMatrix( void )
{
	matrix4x4f view;
	view.identity();

	g_vLook.normalize();

	g_vRight = vector3f::crossProduct(g_vView, g_vUp);
	g_vRight.normalize();

	g_vUp = vector3f::crossProduct(g_vRight, g_vView);
	g_vUp.normalize();

	view.m[0] =  g_vRight.x;
	view.m[1] =  g_vUp.x;
	view.m[2] = -g_vView.x;
	view.m[3] =  0.0f;

	view.m[4] =  g_vRight.y;
	view.m[5] =  g_vUp.y;
	view.m[6] = -g_vView.y;
	view.m[7] =  0.0f;

	view.m[8]  =  g_vRight.z;
	view.m[9]  =  g_vUp.z;
	view.m[10] = -g_vView.z;
	view.m[11] =  0.0f;

	float f = 1.3;
	
	view.m[12] = -vector3f::dotProduct(g_vRight, g_vEye);
	view.m[13] = -vector3f::dotProduct(g_vUp, g_vEye);
	view.m[14] =  vector3f::dotProduct(g_vView, g_vEye);
	view.m[15] =  1.0f;

#ifdef MODE_OPENGL
	glMultMatrixf( view.m );
#endif
}


//-----------------------------------------------------------------------------
// Name: getRealTimeUserInput()
// Desc: 
//-----------------------------------------------------------------------------
void RubikCubeController::getRealTimeUserInput( void )
{
#ifdef MODE_OPENGL
	// Mouse input
	POINT mousePosit;
	GetCursorPos( &mousePosit );
	ScreenToClient( g_hWnd, &mousePosit );

	g_ptCurrentMousePosit.x = mousePosit.x;
	g_ptCurrentMousePosit.y = mousePosit.y;

	matrix4x4f matRotation;

	if( g_bMousing )
	{
		int nXDiff = (g_ptCurrentMousePosit.x - g_ptLastMousePosit.x);
		int nYDiff = (g_ptCurrentMousePosit.y - g_ptLastMousePosit.y);

		if( nYDiff != 0 )
		{
			matRotation.rotate( -(float)nYDiff / 3.0f, g_vRight );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}

		if( nXDiff != 0 )
		{
			matRotation.rotate( -(float)nXDiff / 3.0f, vector3f(0.0f, 1.0f, 0.0f) );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}
	}

	g_ptLastMousePosit.x = g_ptCurrentMousePosit.x;
	g_ptLastMousePosit.y = g_ptCurrentMousePosit.y;

	// Get keyboard input...
	
	unsigned char keys[256];
	GetKeyboardState( keys );

	vector3f tmpLook  = g_vLook;
	vector3f tmpRight = g_vRight;
	vector3f tmpUp = g_vUp;
	vector3f tmpEye = g_vEye;
	vector3f tmpView = g_vView;

	if(speed > 0)
	{
		g_vEye -= tmpLook*-(g_fMoveSpeed_Travel*speed)*g_fElpasedTime;
	} else if(speed < 0)
	{
		g_vEye += (tmpLook*-(g_fMoveSpeed_Travel* (float)abs(speed)))*g_fElpasedTime;
	}


	if(keys[45] & 0x80) speed = 0;

	// Move forward
	if( keys[VK_F3] & 0x80 )
	{
		speed += 0.1;
		g_vEye -= tmpView*-(g_fMoveSpeed_Travel*speed)*g_fElpasedTime;
		g_vLook = g_vView;
	}

	// Move backwards
	if( keys[VK_F4] & 0x80 )
	{
		speed -= 0.1;
		g_vEye += (tmpView*-(g_fMoveSpeed_Travel*  (float)abs(speed)))*g_fElpasedTime;
		g_vLook = g_vView;
	}

	/* -------------------------------------------------------- */ 
	// Move forward (slowly)
	if( keys[VK_F5] & 0x80 )
	{
		speed += 0.001;
		g_vEye -= tmpView*-(g_fMoveSpeed_Travel_small*speed)*g_fElpasedTime;
		g_vLook = g_vView;
	}

	// Move backwards (slowly)
	if( keys[VK_F6] & 0x80 )
	{
		speed -= 0.001;
		g_vEye += (tmpView*-(g_fMoveSpeed_Travel_small*  (float)abs(speed)))*g_fElpasedTime;
		g_vLook = g_vView;
	}
	//-----------------------------------------------------

	// Up Arrow Key - View moves forward
	if( keys[VK_UP] & 0x80 )
	{
		g_vView -= tmpUp*-g_fMoveSpeed_turn*g_fElpasedTime;
	}

	// Down Arrow Key - View moves backward
	if( keys[VK_DOWN] & 0x80 )
	{
		g_vView += (tmpUp*-g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Left Arrow Key - View side-steps or strafes to the left
	if( keys[VK_LEFT] & 0x80 )
	{
		g_vView -= (tmpRight*g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Right Arrow Key - View side-steps or strafes to the right
	if( keys[VK_RIGHT] & 0x80 )
	{
		g_vView += (tmpRight*g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Home Key - View elevates up
	if( keys[VK_HOME] & 0x80 )
		g_vEye.y += g_fMoveSpeed*g_fElpasedTime; 

	// End Key - View elevates down
	if( keys[VK_END] & 0x80 )
		g_vEye.y -= g_fMoveSpeed*g_fElpasedTime;
#endif
}



//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void RubikCubeController::shutDown( void )   
{
#ifdef MODE_OPENGL
	if( g_hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( g_hRC );
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC( g_hWnd, g_hDC );
		g_hDC = NULL;
	}
#endif
}

void RubikCubeController::render( void )
{
#ifdef MODE_OPENGL
	Vertex g_lineVertices[] =
	{
		{ 255,   0,   0, 255,  0.0f, 0.1f, 0.0f }, // red   = +x Axis (x)
		{ 255,   0,   0, 255,  5.0f, 0.0f, 0.0f },
		{   0, 255,   0, 255,  0.0f, 0.1f, 0.0f }, // green = +z Axis (y)
		{   0, 255,   0, 255,  0.0f, 5.0f, 0.0f },
		{   0,   0, 255, 255,  0.0f, 0.1f, 0.0f }, // blue  = +y Axis (z)
		{   0,   0, 255, 255,  0.0f, 0.0f, 5.0f }
	};

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	getRealTimeUserInput();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	updateViewMatrix();
	
	glDisable( GL_BLEND);
	glEnable( GL_DEPTH_TEST );

	GLfloat LightAmbient[]= {0.8, 0.8, 0.8, 0.8};
	GLfloat LightDiffuse[]= {1.0, 1.0, 1.0, 1.0};
	GLfloat LightPosition[]= { 4.0f, 2.0f, 3.0f, 1.0f};

	int i,j,k;

	if(rotating!=-1)
	{
		if((rotating < 4 || rotating>5) && rotating!=8) glRotatef(CubeTransformData::showLap[rotating].deg, 0.0, 1.0, 0.0);
		else glRotatef(CubeTransformData::showLap[rotating].deg, 1.0, 0.0, 0.0);
		glTranslatef(CubeTransformData::showLap[rotating].x1, CubeTransformData::showLap[rotating].y1, CubeTransformData::showLap[rotating].z1);
		geometryProvider->renderSideCells();
		glTranslatef(-CubeTransformData::showLap[rotating].x1, -CubeTransformData::showLap[rotating].y1, -CubeTransformData::showLap[rotating].z1);
		glTranslatef(CubeTransformData::showLap[rotating].x2, CubeTransformData::showLap[rotating].y2, CubeTransformData::showLap[rotating].z2);
		geometryProvider->renderSideCells();
		glTranslatef(-CubeTransformData::showLap[rotating].x2, -CubeTransformData::showLap[rotating].y2, -CubeTransformData::showLap[rotating].z2);
		if((rotating < 4 || rotating > 5) && rotating != 8) glRotatef(-CubeTransformData::showLap[rotating].deg, 0.0, 1.0, 0.0);
		else glRotatef(-CubeTransformData::showLap[rotating].deg, 1.0, 0.0, 0.0);
	} else
	{
		glTranslatef(0.52, 0.55, 0.52);
		for(i=0; i!=3; i++)
		{
			geometryProvider->renderSideCells();
			glTranslatef(0.0, 0.0, 0.98);
		}
		glTranslatef(0.0, 0.0, -(3*0.98));
		glTranslatef(-0.52, -0.55, -0.52);
	}

	glPushMatrix();
	{
		geometryProvider->renderGrid(10, 0.5);
		refreshCube();

		if(!changed) 
		{
			cube.DefaultColors();
			changed = 1;
		}

		// -------------------- ROTATE --------------
		int snum;
		for(snum=0; snum!=9; snum++)
		{
			if(CubeTransformData::sideRotate[snum].deg != 0.0)
			{
				glRotatef(CubeTransformData::sideRotate[snum].rot[0], CubeTransformData::sideRotate[snum].rot[1], CubeTransformData::sideRotate[snum].rot[2], CubeTransformData::sideRotate[snum].rot[3]);
				
				glTranslatef(CubeTransformData::sideRotate[snum].dist[0], CubeTransformData::sideRotate[snum].dist[1], CubeTransformData::sideRotate[snum].dist[2]);
				glRotatef(CubeTransformData::sideRotate[snum].deg, 0.0, 0.0, 1.0);
				geometryProvider->renderSide(CubeTransformData::sideRotate[snum].colors);
				if(CubeTransformData::sideRotate[snum].deg>0.0) CubeTransformData::sideRotate[snum].deg -= rotatingSpeedCurrent;
				else if(CubeTransformData::sideRotate[snum].deg<0.0) CubeTransformData::sideRotate[snum].deg += rotatingSpeed;

				if(CubeTransformData::sideRotate[snum].deg == 0.0) 
				{
					stillRotate = 0;
					rotating=-1;
					if(rotatingSpeedCurrent != rotatingSpeed) rotatingSpeedCurrent = rotatingSpeed;
				} else 
				{
					stillRotate = 1;
					rotating = snum;
				}
			}
		}
	}

	glPopMatrix();

	glInterleavedArrays( GL_C4UB_V3F, 0, g_lineVertices );
	glDrawArrays( GL_LINES, 0, 6 );

	int h;
	glColor3f(1.0, 1.0, 1.0);
	sprintf(warning, "Steps (not optimized): %d / %d", rotatingStep+1, step);
	geometryProvider->renderTextFull(10.0, 12.0, warning);

	if(rotatingStep == step-1) cube.getTransformEngine()->stopRotating();
	if(rotating==-1 &&cube.getTransformEngine()->getRotating())
	{
		cube.getTransformEngine()->setRotated(1);
		rotatingStep++;
		if(cube.getTransformEngine()->getRotated())
		{
			cube.getTransformEngine()->cTransform(history[rotatingStep].step);
			cube.getTransformEngine()->setRotated(0);
		}
	}
	
	i=0;
	glColor3f(1.0, 1.0, 1.0);

	HelpCommands info[] = {
		{"q,w,e,r,t,z,u,i,o,p,a,s,d,f,g,h,j,k: Rotate commands"},
		{"m: Rotate randomly"},
		{"2: Solve Cube (animated)"},
		{"6,7,8,9: Speed - slower->faster"},
		{"F3: Move towards"},
		{"F4: Move backwards"},
		{"Up, down, left, right: Change moving direction"},
		{"Space: Stop"},
		{""}
	};
	while(strlen(info[i].line))
	{
		sprintf(warning, "%s", info[i].line);
		geometryProvider->renderTextFull(10, (12*i) + 24, warning);
		i++;
	}

	SwapBuffers( g_hDC );
#endif
}

void RubikCubeController::setColorGrid(int lap, int sorszam, double red, double green, double blue)
{
	cubeSide cubeSide[7] = {
		{0.0,  0.0, 0.0, 0.0},
		{90.0, 1.0, 0.0, 0.0},
		{90.0, 0.0, 0.0, 1.0},
		{90.0, 1.0, 0.0, 0.0},
		{90.0, 0.0, 0.0, 1.0},
		{0.0,  0.0, 0.0, 0.0},
		{0.0,  0.0, 0.0, 0.0}
	};

	double x,y,z;
	double fok[4] = { cubeSide[lap].deg, cubeSide[lap].degx, cubeSide[lap].degy, cubeSide[lap].degz };
	x = CubeTransformData::sideCoordinates[lap][sorszam].x;
	y = CubeTransformData::sideCoordinates[lap][sorszam].y;
	z = CubeTransformData::sideCoordinates[lap][sorszam].z;

#ifdef MODE_OPENGL
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glRotatef(fok[0], fok[1], fok[2], fok[3]);
		geometryProvider->renderGridColor(0.8, red, green, blue);
		glTranslatef(-x, -y, -z);

	}
	glPopMatrix();
#endif
}

void RubikCubeController::refreshCube()
{
	int i;
	int j;
	int k,l=1;
	for(i=1; i!=7; i++)
	{
		if(CubeTransformData::sideRotate[i-1].deg > 0.0) continue;
		if(i==1 && g_vEye.z < 2.5) continue;
		else if(i==2 && g_vEye.x < 2.5) continue;
		else if(i==3 && g_vEye.z > 0) continue;
		else if(i==4 && g_vEye.x > 0) continue;
		else if(i==5 && g_vEye.y < 2.5) continue;
		else if(i==6 && g_vEye.y > 0) continue;

		for(j=1; j!=10; j++)
		{
			l=1;
			if(rotating != -1)
			{
				int s = rotating + (rotating-1)+1;

				for(k=0; k!=21; k++)
					if(CubeTransformData::cellColors[s].e[k].side == i && CubeTransformData::cellColors[s].e[k].place==j) 
						l=0;
				if(!l) continue;
			}

			setColorGrid(i, j, cube.GetCellColor(i, j).Red, cube.GetCellColor(i, j).Green, cube.GetCellColor(i, j).Blue);
		}
	}
}

void RubikCubeController::saveCubeColors()
{
	for(int a=1; a!=7; a++) {
		for(int b=1; b!=10; b++) {
			oldCube.SetCellColor(a, b, cube.GetCellColor(a, b));
		}
	}
	return;

}

void RubikCubeController::loadCubeColors()
{
	for(int a=1; a!=7; a++) 
	{
		for(int b=1; b!=10; b++) {
			cube.SetCellColor(a, b, oldCube.GetCellColor(a, b));
		}
	}
	
	return;
}

void RubikCubeController::cAddQueue(char *cmd)
{
	sprintf(history[step].step, "%s", cmd);
	step++;
}

void RubikCubeController::rotateColorSide(int num)
{
	int i;
	int n = num/2;
	
	for(i=0; i!=21; i++)
	{
		CubeModel::CubeColor color = cube.GetCellColor(CubeTransformData::cellColors[num].e[i].side, CubeTransformData::cellColors[num].e[i].place);

		CubeTransformData::sideRotate[n].colors[i].red = color.Red;
		CubeTransformData::sideRotate[n].colors[i].green = color.Green;
		CubeTransformData::sideRotate[n].colors[i].blue = color.Blue;
	}
	if((num%2) != 0) CubeTransformData::sideRotate[n].deg = -90;
	else CubeTransformData::sideRotate[n].deg = 90;

	if(num==8 || num==9 || num==14 || num==15) CubeTransformData::sideRotate[n].deg = -1 * CubeTransformData::sideRotate[n].deg;
}