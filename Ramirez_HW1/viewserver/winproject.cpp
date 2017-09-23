//    -------------------------------------    organization    ------------------------------------------
//Name: Andrea Ramirez
//Date: 09/16/17
//Title: Ramirez_HW1.cpp
//Exercise: Draw small dark green	rectangle where your mouse’s position is on the screen. Draw a button on the screen.
//	When you press the button, it should jump to a new location on the screen. Clicking that again should end your program.
//	This button, on both positions, should change its color between red and yellow periodically.
//  --------------------------------------------------------------------------------------------------



#include "ground.h"
#include <vector>
#include <ctime>
//    defines
#define MAX_LOADSTRING 1000
#define TIMER1 111
//    global variables
HINSTANCE hInst;                                            //    program number = instance
TCHAR szTitle[MAX_LOADSTRING];                                //    name in window title
TCHAR szWindowClass[MAX_LOADSTRING];                        //    class name of window
HFONT editfont;                                                //    a font to write
HWND hMain = NULL;                                            //    number of windows = handle window = hwnd
static char MainWin[] = "MainWin";                            //    class name
HBRUSH  hWinCol = CreateSolidBrush(RGB(180, 180, 180));        //    a color
int dx = 0, dy = 0;
int showcross = 1;

//initial position of button 
int button_x = 250, button_y = 250;
//width of button
int button_width = 50;
//flag that checks if mouse pointer is over button
bool flag = false;
//checks if button has been clicked already
bool click = false;
//switches color values
bool color = false; //red = true; yellow = false;
//color values of button
int red = 255;
int green = 0;
int blue = 0;

//timer for the color switch
int timer = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);    //message loop function (containing all switch-case statements
void draw_line(HDC DC, int x, int y, int a, int b, int red, int green, int blue, int width);    //a draw line function
void draw_rectangle(HDC DC, int x, int y, int w, int h, int red, int green, int blue, int width);

int APIENTRY WinMain(                //    the main function in a window program. program starts here
	HINSTANCE hInstance,            //    here the program gets its own number
	HINSTANCE hPrevInstance,        //    in case this program is called from within another program
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{


	hInst = hInstance;                                                //                        save in global variable for further use
																	  // TODO: Hier Code einfügen.
	MSG msg;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, 103, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, 104, szWindowClass, MAX_LOADSTRING);
	//register Window                                                    <<<<<<<<<<            STEP ONE: REGISTER WINDOW                        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	WNDCLASSEX wcex;                                                //                        => Filling out struct WNDCLASSEX
	BOOL Result = TRUE;
	wcex.cbSize = sizeof(WNDCLASSEX);                                //                        size of this struct (don't know why
	wcex.style = CS_HREDRAW | CS_VREDRAW;                            //                        ?
	wcex.lpfnWndProc = (WNDPROC)WndProc;                            //                        The corresponding Proc File -> Message loop switch-case file
	wcex.cbClsExtra = 0;                                            //
	wcex.cbWndExtra = 0;                                            //
	wcex.hInstance = hInstance;                                        //                        The number of the program
	wcex.hIcon = LoadIcon(hInstance, NULL);                            //
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                        //
	wcex.hbrBackground = hWinCol;                                    //                        Background color
	wcex.lpszMenuName = NULL;                                        //
	wcex.lpszClassName = MainWin;                                    //                        Name of the window (must the the same as later when opening the window)
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);                    //
	Result = (RegisterClassEx(&wcex) != 0);                            //                        Register this struct in the OS

																	   //                                                    STEP TWO: OPENING THE WINDOW with x,y position and xlen, ylen !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	hMain = CreateWindow(MainWin, "TestWin CST 325", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 1920 / 2, 1080 / 2 - 100, 500, 500, NULL, NULL, hInst, NULL);
	if (hMain == 0)    return 0;

	ShowWindow(hMain, nCmdShow);
	UpdateWindow(hMain);

	//                                                    STEP THREE: Going into the infinite message loop                              !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	bool quit = FALSE;
	while (!quit)
	{
		//if (GetMessage(&msg, NULL, 0, 0) > 0)
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			if (msg.message == WM_QUIT) { quit = TRUE; break; }


			TranslateMessage(&msg);                                //                        IF a meessage occurs, the WinProc will be called!!!!
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
///////////////////////////////////////////////////

void redr_win_full(HWND hwnd, bool erase)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	InvalidateRect(hwnd, &rt, erase);
}

///////////////////////////////////
//        This Function is called every time the Left Mouse Button is down
///////////////////////////////////
void OnLBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
}
///////////////////////////////////
//        This Function is called every time the Right Mouse Button is down
///////////////////////////////////
void OnRBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
}
///////////////////////////////////
//        This Function is called every time a character key is pressed
///////////////////////////////////
void OnChar(HWND hwnd, UINT ch, int cRepeat)
{

}
///////////////////////////////////
//        This Function is called every time the Left Mouse Button is up
///////////////////////////////////
void OnLBU(HWND hwnd, int x, int y, UINT keyFlags)
{

	if (flag == true) {
		//changes next position of button
		srand(static_cast<unsigned int>(time(0)));
		button_x = (rand() % 400);
		if (button_x >= 355) {
			button_x -= 125;
		}
		button_y = (rand() % 400) + 50;
		//button has already been clicked once. close program 2nd time
		if (click)
		{
			PostQuitMessage(0);
		}
		click = true; //button has been clicked once
		flag = false;
	}

}
///////////////////////////////////
//        This Function is called every time the Right Mouse Button is up
///////////////////////////////////
void OnRBU(HWND hwnd, int x, int y, UINT keyFlags)
{

	PostQuitMessage(0);

}
///////////////////////////////////
//        This Function is called every time the Mouse Moves
///////////////////////////////////
void OnMM(HWND hwnd, int x, int y, UINT keyFlags)
{
	dx = x;
	dy = y;
	//detects if the mouse is over the position of the button
	if ((dx <= button_x + button_width/2 + 100 && dx >= button_x - button_width/2) && (dy <= button_y + button_width/2 && dy >= button_y - button_width/2)) {
		flag = true;
	}
	else { 
		flag = false;
	}

	if ((keyFlags & MK_LBUTTON) == MK_LBUTTON)
	{

	}

	if ((keyFlags & MK_RBUTTON) == MK_RBUTTON)
	{

	}
}
///////////////////////////////////
//        This Function is called once at the begin of a program
///////////////////////////////////
//#define TIMER1 1

BOOL OnCreate(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
{

	hMain = hwnd;
	//editfont = CreateFont(-10, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");    

	if (!SetTimer(hwnd, TIMER1, 50, NULL))
	{
		MessageBox(hwnd, "No Timers Available", "Info", MB_OK);
		return FALSE;
	}


	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	//HWND hwin;

	//switch (id)
	//{
	//default:
	//	break;
	//}

}
//************************************************************************
void OnTimer(HWND hwnd, UINT id)
{
	if (color && timer < 15) //checks if color should be red
	{
		red = 255;
		green = 0;
		blue = 0;
		color = false; //changes color to yellow
	}
	else if(timer >= 15)  //checks if color should be yellow. Timer slows down the color switching
	{
		red = 244;
		green = 235;
		blue = 66;
		color = true; //changes color to red
		if (timer == 25) //when timer reaches 25, it resets goes from yellow back to red
		{
			timer = -1;
		}
	}
	timer++; //increase timer
	redr_win_full(hwnd, FALSE); //calling the OnPaint
}
//************************************************************************
///////////////////////////////////
//        This Function is called every time the window has to be painted again
///////////////////////////////////


void OnPaint(HWND hwnd)
{

	//if(rglobe.EckSizing.active_sizing())return;
	PAINTSTRUCT PaintStruct;
	HDC DC_ = BeginPaint(hwnd, &PaintStruct);
	HBITMAP hbmMem, hbmOld;
	HDC DC = CreateCompatibleDC(DC_);
	RECT rc;
	GetClientRect(hwnd, &rc);
	hbmMem = CreateCompatibleBitmap(DC_, rc.right - rc.left, 2000);
	hbmOld = (HBITMAP)SelectObject(DC, hbmMem);
	COLORREF bg = RGB(180, 180, 180);
	//if(rglobe.EckSizing.active_sizing())
	//bg=RGB(255,255,0);
	HBRUSH hbrBkGnd = CreateSolidBrush(bg);
	FillRect(DC, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	//draws button in initial position
	draw_line(DC, button_x, button_y, button_x + 100, button_y, red, green, blue, button_width);
	if (click)//if button has been clicked, redraw button
	{

		draw_line(DC, button_x, button_y, button_x + 100, button_y, red, green, blue, button_width);

	}



	//draw here:
	//draw_line(DC, 200, 200, 300, 300, 0, 0, 255, 5);
	//draw_line(DC, dx, dy, 300, 300, 255, 255, 255, 5);   //Lines moves with mouse

	//draws green rectangle
	draw_rectangle(DC, dx, dy, dx + 60, dy + 50, 0, 102, 0, 5);


	/*if (showcross == 1)
	{
	draw_line(DC, dx - 10, dy, dx + 10, dy, 255, 0, 0, 5);
	draw_line(DC, dx, dy - 10, dx, dy + 10, 255, 0, 0, 5);
	}
	*/

	//                    DOUBLE BUFFERING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	BitBlt(DC_, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, DC, 0, 0, SRCCOPY);
	SelectObject(DC, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(DC);
	EndPaint(hwnd, &PaintStruct);
}
//****************************************************************************

void draw_line(HDC DC, int x, int y, int a, int b, int red, int green, int blue, int width)
{
	HPEN Stift = CreatePen(PS_SOLID, width, RGB(red, green, blue));
	SelectObject(DC, Stift);
	MoveToEx(DC, x, y, NULL);
	LineTo(DC, a, b);
	DeleteObject(Stift);
}
//*************************************************************************
void draw_rectangle(HDC DC, int from_x, int from_y, int to_x, int to_y, int red, int green, int blue, int width)
{
	draw_line(DC, from_x, from_y, from_x, to_y, red, green, blue, 5);
	draw_line(DC, from_x, from_y, to_x, from_y, red, green, blue, 5);
	draw_line(DC, from_x, to_y, to_x, to_y, red, green, blue, 5);
	draw_line(DC, to_x, from_y, to_x, to_y, red, green, blue, 5);
}
void change_line_color(int red, int green, int blue);

//*************************************************************************
void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{

	switch (vk)
	{
	case 65://a

		break;
	default:break;

	}
}

//*************************************************************************
void OnKeyUp(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	//switch (vk)
	//{
	//default:break;

	//}

}


//**************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

		/*
		#define HANDLE_MSG(hwnd, message, fn)    \
		case (message): return HANDLE_##message((hwnd), (wParam), (lParam), (fn))
		*/

		HANDLE_MSG(hwnd, WM_CHAR, OnChar);            // when a key is pressed and its a character
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLBD);    // when pressing the left button
		HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLBU);        // when releasing the left button
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN, OnRBD);    // when pressing the left button
		HANDLE_MSG(hwnd, WM_RBUTTONUP, OnRBU);        // when releasing the left button
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMM);        // when moving the mouse inside your window
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);        // called only once when the window is created
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);        // drawing stuff
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);    // not used
		HANDLE_MSG(hwnd, WM_KEYDOWN, OnKeyDown);    // press a keyboard key
		HANDLE_MSG(hwnd, WM_KEYUP, OnKeyUp);        // release a keyboard key
		HANDLE_MSG(hwnd, WM_TIMER, OnTimer);        // timer

	case WM_ERASEBKGND:
		return (LRESULT)1;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}







