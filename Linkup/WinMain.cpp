// T3D Game Console, creates a game console application

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC
#define INITGUID

//#include "t3dlib1.h"
#include "t3dlib1.h"
#include "WinMain.h"


// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"


// GLOBALS ////////////////////////////////////////////////



//DDraw7///////////////////////////////////////////////////


// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
							UINT msg, 
							WPARAM wparam, 
							LPARAM lparam)
{
	return GameFrame::GetGameFramePoint()->ProcEvent(hwnd,msg,wparam,lparam);//所有信息交由GameFrame处理
} // end WinProc

///////////////////////////////////////////////////////////



// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)
{

	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hwnd;	 // generic window handle
	MSG		   msg;		 // generic message
	HDC        hdc;      // graphics device context

	// first fill in the window class stucture
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

	// save hinstance in global
	hinstance_app = hinstance;

	// register the window class
	if (!RegisterClassEx(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindowEx(NULL,                  // extended style
		WINDOW_CLASS_NAME,     // class
		"T3D Game Console Version 1.0", // title
		WS_OVERLAPPED| WS_VISIBLE,
		0,0,	  // initial x,y
		800,600,  // initial width, height
		NULL,	  // handle to parent 
		NULL,	  // handle to menu
		hinstance,// instance of this application
		NULL)))	// extra creation parms
		return(0);

	// save main window handle
	hwnd_app = hwnd;

	// initialize game here
	Game_Init();


	// enter main event loop
	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if


		// main game processing goes here
		Game_Main();

	} // end while

	// closedown game here
	Game_Shutdown();

	// return to Windows like this
	return(msg.wParam);
} // end WinMain

///////////////////////////////////////////////////////////


