// TP_PROJECT4.cpp: Okreœla punkt wejœcia dla aplikacji.
//

#include "stdafx.h"
#include "TP_PROJECT4.h"
#include "Resource.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#define MAX_LOADSTRING 100

HPEN Pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
HPEN Pen2 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
class HUMAN
{
public:
	int positionX;
	int positionY;
	int destination;
	int source;
	int weight = 70;
	int number;
	void drawhuman(HDC hdc, int destination)
	{
		SelectObject(hdc, Pen);
		Ellipse(hdc, positionX - 20, positionY - 45, positionX, positionY - 25); //głowa
		Rectangle(hdc, positionX - 30, positionY - 25, positionX + 10, positionY); //ręce
		Rectangle(hdc, positionX - 20, positionY - 25, positionX, positionY); //brzuch
		Rectangle(hdc, positionX - 20, positionY, positionX - 10, positionY + 25); //lewa noga
		Rectangle(hdc, positionX - 10, positionY, positionX, positionY + 25); //prawa noga
		SelectObject(hdc, Pen2);
		switch (destination)
		{
		case 120:
			MoveToEx(hdc, positionX - 3, positionY - 60, NULL);
			LineTo(hdc, positionX - 3, positionY - 45);
			MoveToEx(hdc, positionX - 17, positionY - 60, NULL);
			LineTo(hdc, positionX - 17, positionY - 45);
		case 336:
			MoveToEx(hdc, positionX - 6, positionY - 60, NULL);
			LineTo(hdc, positionX - 6, positionY - 45);
			MoveToEx(hdc, positionX - 14, positionY - 60, NULL);
			LineTo(hdc, positionX - 14, positionY - 45);
		case 552:
			MoveToEx(hdc, positionX - 10, positionY - 60, NULL);
			LineTo(hdc, positionX - 10, positionY - 45);
			break;
		case 228:
			MoveToEx(hdc, positionX - 3, positionY - 60, NULL);
			LineTo(hdc, positionX - 3, positionY - 45);
			MoveToEx(hdc, positionX - 17, positionY - 60, NULL);
			LineTo(hdc, positionX - 17, positionY - 45);
		case 444:
			MoveToEx(hdc, positionX - 7, positionY - 60, NULL);
			LineTo(hdc, positionX - 7, positionY - 45);
			MoveToEx(hdc, positionX - 13, positionY - 60, NULL);
			LineTo(hdc, positionX - 13, positionY - 45);
			break;
		}
	}
};

HWND hwndButton;
HDC hdc;
int middle = 678;
int floorsHeight = 552;
int currentPosition = 552;
bool controller = TRUE;									//<----------
int speed = 0;
bool controllerBlock = TRUE;
bool controllerBlock_2 = FALSE;
bool timerblock = TRUE;
bool memorycontroller = TRUE;
bool controller10 = TRUE;
bool veccontrl = TRUE;
int memory2 = 1;
int memory1 = 1;
int valueTimer1 = 552;
int valueTimer2 = 552;
bool TIMER1 = TRUE;
bool TIMER2 = TRUE;
bool TIMER3 = TRUE;
int updown = 0;
std::vector<int> floors;
std::vector<HUMAN> peopleF5;
std::vector<HUMAN> peopleF4;
std::vector<HUMAN> peopleF3;
std::vector<HUMAN> peopleF2;
std::vector<HUMAN> peopleF1;
std::vector<HUMAN> peopleC;
HUMAN person;
// Zmienne globalne:
HINSTANCE hInst;                                // bie¿¹ce wyst¹pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytu³u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna g³ównego

// Przeka¿ dalej deklaracje funkcji do³¹czonych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void elevator()
{
	SelectObject(hdc, Pen);
	Rectangle(hdc, middle - 162, 10, middle + 162, 573);
	Rectangle(hdc, middle - 152, currentPosition - 89, middle + 152, currentPosition);
	for (int i = 0, j = 119; i < 3; i++, j = j + 216)
	{
		MoveToEx(hdc, middle - 164, j, NULL);
		LineTo(hdc, middle - 564, j);
	}
	for (int i = 0, j = 227; i < 2; i++, j = j + 216)
	{
		MoveToEx(hdc, middle + 162, j, NULL);
		LineTo(hdc, middle + 564, j);
	}
}


void drawpeople(std::vector<HUMAN> &people)
{
	for (int i = 0; i < 10; i++)
	{
		if (people.size() == i)
			break;
		people[i].drawhuman(hdc, people[i].destination);
	}
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps)
{
	if (controller)										//<----------
	{
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
		hdc = BeginPaint(hWnd, &ps);
	}
	elevator();
	drawpeople(peopleF5);
	drawpeople(peopleF4);
	drawpeople(peopleF3);
	drawpeople(peopleF2);
	drawpeople(peopleF1);
	drawpeople(peopleC);
}


bool xyz(int a)
{
	for (int i = 0; i < peopleC.size(); i++)
		if (peopleC[i].destination == a)
			return FALSE;
	return TRUE;
}


void xyz2(int a)
{
	for (;;)
	{
		bool W = TRUE;
		for (int i = 0; i < peopleC.size(); i++)
		{
			if (peopleC[i].destination == a)
			{
				peopleC.erase(peopleC.begin() + i);
				W = FALSE;
				break;
			}
		}
		if (W)
			break;
	}
}


void remove()
{
	if ((peopleF1.empty()) && (xyz(552)))
		xyz2(552);
	if ((peopleF2.empty()) && (xyz(444)))
		xyz2(444);
	if ((peopleF3.empty()) && (xyz(336)))
		xyz2(336);
	if ((peopleF4.empty()) && (xyz(228)))
		xyz2(228);
	if ((peopleF5.empty()) && (xyz(120)))
		xyz2(120);
}


void move(HWND hWnd, PAINTSTRUCT &ps, int a, int b)
{
	valueTimer1 = a;			//żeby wpisać do windy polecenie zabrania ludzi z piętra, winda najpierw musi z niego odjechać
	if (controllerBlock)		//Blokada na wielokrotne wpisywanie polecenia wjazdu na to samo piętro
	{
		floors.push_back(a);
		controllerBlock = FALSE;
	}
	floors.push_back(b);
	repaintWindow(hWnd, hdc, ps);
	if (timerblock)
		SetTimer(hWnd, TMR_1, speed, 0);
}

bool abc()
{
	for (int i = 0; i < peopleC.size(); i++)
		if (peopleC[i].destination == currentPosition)
			return TRUE;
	return FALSE;
}

bool abc2()
{
	if((currentPosition == 120) && (!peopleF5.empty()) || (currentPosition == 228) && (!peopleF4.empty()) || (currentPosition == 336) && (!peopleF3.empty()) ||
		(currentPosition == 444) && (!peopleF2.empty()) || (currentPosition == 552) && (!peopleF1.empty()))
		return TRUE;
	return FALSE;
}

void timer(HWND hWnd, PAINTSTRUCT &ps)
{
	if (memorycontroller)
	{
		memory2 = memory1;
		memorycontroller = FALSE;
	}
	if (currentPosition == valueTimer1)
		controllerBlock_2 = TRUE;
	if ((memory2 != memory1) || ((controllerBlock_2) && (currentPosition != valueTimer1)))// || (floors.empty()))
	{
		controllerBlock = TRUE;
		controllerBlock_2 = FALSE;
	}
	if (TIMER1)
	{
		controller = FALSE;
		repaintWindow(hWnd, hdc, ps);
		if ((peopleC.empty()) && (peopleF1.empty()) && (peopleF2.empty()) && (peopleF3.empty()) && (peopleF4.empty()) && (peopleF5.empty()))
			floors.clear();
		if (floors.empty())
		{
			controllerBlock = TRUE;
			KillTimer(hWnd, TMR_1);
		}
		else if ((peopleC.size() != 8) && (abc2()))
		{
			TIMER1 = FALSE;
			SetTimer(hWnd, TMR_2, 500, 0);
		}
		else if (abc())
		{
			TIMER1 = FALSE;
			SetTimer(hWnd, TMR_3, 500, 0);
		}
		else if ((((peopleC.empty()) && (floors.front() < currentPosition))) || ((!peopleC.empty()) && (peopleC.front().destination < currentPosition)))
		{
			for (int i = 0; i < peopleC.size(); i++)
				peopleC[i].positionY = peopleC[i].positionY - 3;
			currentPosition = currentPosition - 3;
		}
		else if ((((peopleC.empty()) && (floors.front() > currentPosition))) || ((!peopleC.empty()) && (peopleC.front().destination > currentPosition)))
		{
			for (int i = 0; i < peopleC.size(); i++)
				peopleC[i].positionY = peopleC[i].positionY + 3;
			currentPosition = currentPosition + 3;
		}
		else if (floors.front() == currentPosition)
		{
			floors.erase(floors.begin());
			if ((currentPosition == 120) && (!peopleF5.empty()) || (currentPosition == 228) && (!peopleF4.empty()) || (currentPosition == 336) && (!peopleF3.empty()) ||
				(currentPosition == 444) && (!peopleF2.empty()) || (currentPosition == 552) && (!peopleF1.empty()))
			{
				TIMER1 = FALSE;
				SetTimer(hWnd, TMR_2, 500, 0);
			}
			TIMER1 = FALSE;
			SetTimer(hWnd, TMR_3, 500, 0);
		}
		memory2 = memory1;
	}
}


void timer2(HWND hWnd, PAINTSTRUCT &ps, std::vector<HUMAN> &peopleF, int P_M, int position)	//wchodzenie ludzi do windy
{
	TIMER1 = FALSE;
	if (peopleC.size() != 8)
	{
		peopleF.front().positionX = middle + 142 - (peopleC.size() * 37);
		//peopleF.front().number = peopleC.size();
		peopleC.push_back(peopleF.front());
		peopleF.erase(peopleF.begin());
		for (int i = 0; i < peopleF.size(); i++)
			peopleF[i].positionX = position + (P_M * i * 40);
		controller = TRUE;
		repaintWindow(hWnd, hdc, ps);
	}
	if (((peopleF.empty()) && (peopleC.size() <= 8)) || ((!peopleF.empty()) && (peopleC.size() == 8)))
	{
		timerblock = TRUE;
		controller = FALSE;
		TIMER1 = TRUE;
		KillTimer(hWnd, TMR_2);
	}
}


void timer3(HWND hWnd, PAINTSTRUCT &ps)		//wychodzenie ludzi z windy
{
	TIMER1 = FALSE;
	for (;;)
	{
		bool W = TRUE;
		for (int i = 0; i < peopleC.size(); i++)
			if (peopleC[i].destination == currentPosition)
			{
				peopleC.erase(peopleC.begin() + i);
				repaintWindow(hWnd, hdc, ps);
				for (int j = 0; j < peopleC.size(); j++)
				{
					peopleC[j].positionX = middle + 142 - (j * 37);
					repaintWindow(hWnd, hdc, ps);
				}
				W = FALSE;
				break;
			}
		if (W)
			break;
	}
	TIMER1 = TRUE;
	KillTimer(hWnd, TMR_3);
}


void createhuman(std::vector<HUMAN> &people, int positionX, int positionY, int source, int destination, int P_M)
{
	person.positionX = positionX + (P_M * people.size() * 40);
	person.positionY = positionY;
	person.source = source;
	person.destination = destination;
	people.push_back(person);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: W tym miejscu umieœæ kod.

    // Zainicjuj ci¹gi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TP_PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjacje aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TP_PROJECT4));

    MSG msg;

    // G³ówna pêtla wiadomoœci:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasê okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TP_PROJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TP_PROJECT4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojœcie wyst¹pienia i tworzy okno g³ówne
//
//   KOMENTARZE:
//
//        W tej funkcji dojœcie wyst¹pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyœwietlane okno g³ówne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojœcie wyst¹pienia w zmiennej globalnej

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 40, 20, 20, hWnd, (HMENU)ID_BUTTON_5_4, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 60, 20, 20, hWnd, (HMENU)ID_BUTTON_5_3, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 80, 20, 20, hWnd, (HMENU)ID_BUTTON_5_2, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 100, 20, 20, hWnd, (HMENU)ID_BUTTON_5_1, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 148, 20, 20, hWnd, (HMENU)ID_BUTTON_4_5, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 168, 20, 20, hWnd, (HMENU)ID_BUTTON_4_3, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 188, 20, 20, hWnd, (HMENU)ID_BUTTON_4_2, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 208, 20, 20, hWnd, (HMENU)ID_BUTTON_4_1, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 256, 20, 20, hWnd, (HMENU)ID_BUTTON_3_5, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 276, 20, 20, hWnd, (HMENU)ID_BUTTON_3_4, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 296, 20, 20, hWnd, (HMENU)ID_BUTTON_3_2, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 316, 20, 20, hWnd, (HMENU)ID_BUTTON_3_1, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 364, 20, 20, hWnd, (HMENU)ID_BUTTON_2_5, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 384, 20, 20, hWnd, (HMENU)ID_BUTTON_2_4, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 404, 20, 20, hWnd, (HMENU)ID_BUTTON_2_3, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle + 574, 424, 20, 20, hWnd, (HMENU)ID_BUTTON_2_1, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 472, 20, 20, hWnd, (HMENU)ID_BUTTON_1_5, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 492, 20, 20, hWnd, (HMENU)ID_BUTTON_1_4, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 512, 20, 20, hWnd, (HMENU)ID_BUTTON_1_3, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, middle - 594, 532, 20, 20, hWnd, (HMENU)ID_BUTTON_1_2, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("START"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 0, 50, 50, hWnd, (HMENU)ID_START, hInstance, NULL);
  
  
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomoœci dla okna g³ównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno g³ówne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróæ
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_START:
			repaintWindow(hWnd, hdc, ps);
			break;
		case ID_BUTTON_5_4:
			createhuman(peopleF5, 507, 95, 120, 228, -1);
			memory1 = 5;
			move(hWnd, ps, 120, 228);
			break;
		case ID_BUTTON_5_3:
			createhuman(peopleF5, 507, 95, 120, 336, -1);
			memory1 = 5;
			move(hWnd, ps, 120, 336);
			break;
		case ID_BUTTON_5_2:
			createhuman(peopleF5, 507, 95, 120, 444, -1);
			memory1 = 5;
			move(hWnd, ps, 120, 444);
			break;
		case ID_BUTTON_5_1:
			createhuman(peopleF5, 507, 95, 120, 552, -1);
			memory1 = 5;
			move(hWnd, ps, 120, 552);
			break;
		case ID_BUTTON_4_5:
			createhuman(peopleF4, 869, 203, 228, 120, 1);
			memory1 = 4;
			move(hWnd, ps, 228, 120);
			break;
		case ID_BUTTON_4_3:
			createhuman(peopleF4, 869, 203, 228, 336, 1);
			memory1 = 4;
			move(hWnd, ps, 228, 336);
			break;
		case ID_BUTTON_4_2:
			createhuman(peopleF4, 869, 203, 228, 444, 1);
			memory1 = 4;
			move(hWnd, ps, 228, 444);
			break;
		case ID_BUTTON_4_1:
			createhuman(peopleF4, 869, 203, 228, 552, 1);
			memory1 = 4;
			move(hWnd, ps, 228, 552);
			break;
		case ID_BUTTON_3_5:
			createhuman(peopleF3, 507, 311, 336, 120, -1);
			memory1 = 3;
			move(hWnd, ps, 336, 120);
			break;
		case ID_BUTTON_3_4:
			createhuman(peopleF3, 507, 311, 336, 228, -1);
			memory1 = 3;
			move(hWnd, ps, 336, 228);
			break;
		case ID_BUTTON_3_2:
			createhuman(peopleF3, 507, 311, 336, 444, -1);
			memory1 = 3;
			move(hWnd, ps, 336, 444);
			break;
		case ID_BUTTON_3_1:
			createhuman(peopleF3, 507, 311, 336, 552, -1);
			memory1 = 3;
			move(hWnd, ps, 336, 552);
			break;
		case ID_BUTTON_2_5:
			createhuman(peopleF2, 869, 419, 444, 120, 1);
			memory1 = 2;
			move(hWnd, ps, 444, 120);
			break;
		case ID_BUTTON_2_4:
			createhuman(peopleF2, 869, 419, 444, 228, 1);
			memory1 = 2;
			move(hWnd, ps, 444, 228);
			break;
		case ID_BUTTON_2_3:
			createhuman(peopleF2, 869, 419, 444, 336, 1);
			memory1 = 2;
			move(hWnd, ps, 444, 336);
			break;
		case ID_BUTTON_2_1:
			createhuman(peopleF2, 869, 419, 444, 552, 1);
			memory1 = 2;
			move(hWnd, ps, 444, 552);
			break;
		case ID_BUTTON_1_5:
			createhuman(peopleF1, 507, 527, 552, 120, -1);
			memory1 = 1;
			move(hWnd, ps, 552, 120);
			break;
		case ID_BUTTON_1_4:
			createhuman(peopleF1, 507, 527, 552, 228, -1);
			memory1 = 1;
			move(hWnd, ps, 552, 228);
			break;
		case ID_BUTTON_1_3:
			createhuman(peopleF1, 507, 527, 552, 336, -1);
			memory1 = 1;
			move(hWnd, ps, 552, 336);
			break;
		case ID_BUTTON_1_2:
			createhuman(peopleF1, 507, 527, 552, 444, -1);
			memory1 = 1;
			move(hWnd, ps, 552, 444);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: tutaj dodaj kod rysowania używający elementu hdc...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			timer(hWnd, ps);
			break;
		case TMR_2:
			if ((currentPosition == 120) && (!peopleF5.empty()))
				timer2(hWnd, ps, peopleF5, -1, 507);
			else if ((currentPosition == 228) && (!peopleF4.empty()))
				timer2(hWnd, ps, peopleF4, 1, 869);
			else if ((currentPosition == 336) && (!peopleF3.empty()))
				timer2(hWnd, ps, peopleF3, -1, 507);
			else if ((currentPosition == 444) && (!peopleF2.empty()))
				timer2(hWnd, ps, peopleF2, 1, 869);
			else if ((currentPosition == 552) && (!peopleF1.empty()))
				timer2(hWnd, ps, peopleF1, -1, 507);
			break;
		case TMR_3:
			timer3(hWnd, ps);
			break;
		case TMR_4:
			move(hWnd, ps, 552, 552);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//Procedura obs³ugi wiadomoœci dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
