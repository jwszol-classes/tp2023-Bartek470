// Winda_z_gui.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "Winda_z_gui.h"

#define MAX_LOADSTRING 100
#define Timer1 1
//Stale globalne
const unsigned int NUMBER_OF_FLOORS = 5;
const unsigned int ELEVATOR_CAPACITY = 10;
//charakterystyka windy

const unsigned int MIN_PASSANGER_WEIGHT = 60;
const unsigned int MAX_PASSANGER_WEIGHT = 80;
//zakres wagi pasazerow
int przesuniecie = 0;
int i = 0;
int start_floor = 1;
int end_floor = 3;
// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego




//handlery przyciskow
HWND hwndButton;

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

class Human
{
private:
    unsigned int start_floor;
    unsigned int end_floor;
    unsigned int weight;
    bool is_inside;
public:
   /* void assign_start_floor(int x)
    {
        start_floor = x;
    }
    void assign_end_floor(int x)
    {
        end_floor = x;
    }
    void assign_weight() //wartość losowa między 60 a 80
    {
        
    }*/
    Human(unsigned int x,unsigned int y)
    {
        start_floor = x;
        end_floor = y;
        srand(time(NULL));
        weight = MIN_PASSANGER_WEIGHT + rand() % (MAX_PASSANGER_WEIGHT - MIN_PASSANGER_WEIGHT);
        is_inside = 0;
    }
    
};

class Elevator //: public Human
{
private:
    
    unsigned int curentposition;
    unsigned int load;
  //  bool moving; //potrzebne do prawidlowego dzialania animacji (w pozniejszym etapie)
   //bool direction; //na razie nwm czy potrzebne w razie pauzy zapisywalo by kierunek w ktorym ma sie poruszac platforma (1 - gora, 0 -dol)
    unsigned int capacity[ELEVATOR_CAPACITY];
public:
    void move_up()
    {
        if (curentposition < NUMBER_OF_FLOORS)
        {
            //SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
            curentposition++;
        }
    }
    void move_down()
    {
        if (curentposition > 0)
        {
           // SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
            curentposition--;
        }
    }
    Elevator()
    {
        curentposition = 1;
        load = 0;
       // moving = 0;
      //  direction = 1;
    }
    
};


std::vector<Human>qpassengers;


void OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen1(Color(255, 0, 0,0),5.0);
    Pen pen2(Color(200, 0, 150, 255), 3.0);
    Pen pen3(Color(150, 0, 0, 0), 2.0);
    Pen pen4(Color(255, 255, 0, 0),2.0);
    Pen pen5(Color(255, 0, 255, 0), 2.0);
    Pen pen6(Color(255, 255, 255, 0), 2.0); //bialy
    //piętra
    graphics.DrawLine(&pen1, 20, 110, 100, 110); //5
    graphics.DrawLine(&pen1, 300, 110, 380, 110);
   
    graphics.DrawLine(&pen1, 20, 230, 100, 230); //4
    graphics.DrawLine(&pen1, 300, 230, 380, 230);

    graphics.DrawLine(&pen1, 20, 350, 100, 350); //3
    graphics.DrawLine(&pen1, 300, 350, 380, 350);

    graphics.DrawLine(&pen1, 20, 470, 100, 470); //2
    graphics.DrawLine(&pen1, 300, 470, 380, 470);

    graphics.DrawLine(&pen1, 20, 590, 100, 590); //1
    graphics.DrawLine(&pen1, 300, 590, 380, 590);

    //ludzie
    graphics.DrawRectangle(&pen4, 100, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen5, 120, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen4, 140, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen5, 160, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen4, 180, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen5, 200, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen4, 220, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen5, 240, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen4, 260, 560 - przesuniecie, 20, 30);
    graphics.DrawRectangle(&pen5, 280, 560 - przesuniecie, 20, 30);

    //winda
    graphics.DrawRectangle(&pen2, 100, 500 - przesuniecie, 200, 90);
    graphics.DrawRectangle(&pen3, 198, 1 - przesuniecie, 4, 498);
}
void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{

    if (drawArea == NULL)
        InvalidateRect(hWnd, NULL, TRUE); // repaint all
    else
        InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
    hdc = BeginPaint(hWnd, &ps);
    OnPaint(hdc);
    EndPaint(hWnd, &ps);
}
int APIENTRY wWinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HACCEL hAccelTable;
    MSG msg;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // TODO: W tym miejscu umieść kod.

   /* Elevator lift;
    bool works = 1;
    */
    
    
    // Inicjuj ciągi globalne
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WINDAZGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDAZGUI));
    

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDAZGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDAZGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
   hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 700, nullptr, nullptr, hInstance, nullptr);
 //przyciski pietro 5
   hwndButton = CreateWindow(L"BUTTON", L"1",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 10,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR5_TO1, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"2",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 35,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR5_TO2, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"3",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 60,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR5_TO3, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"4",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 85,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR5_TO4, hInstance, NULL);
   //przyciski pietro 4
   hwndButton = CreateWindow(L"BUTTON", L"1",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 130,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR4_TO1, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"2",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 155,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR4_TO2, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"3",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 180,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR4_TO3, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"5",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 205,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR4_TO5, hInstance, NULL);
   
   //przyciski pietro 3
   hwndButton = CreateWindow(L"BUTTON", L"1",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 250,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR3_TO1, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"2",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 275,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR3_TO2, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"4",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 300,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR3_TO4, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"5",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 325,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR3_TO5, hInstance, NULL);

   //przyciski pietro 2
   hwndButton = CreateWindow(L"BUTTON", L"1",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 370,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR2_TO1, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"3",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 395,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR2_TO3, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"4",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 420,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR2_TO4, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"5",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 445,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR2_TO5, hInstance, NULL);

   //przyciski pietro 1
   hwndButton = CreateWindow(L"BUTTON", L"2",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 490,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR1_TO2, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"3",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 515,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR1_TO3, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"4",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 540,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR1_TO4, hInstance, NULL);
   hwndButton = CreateWindow(L"BUTTON", L"5",
       WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       30, 565,
       20, 20,
       hWnd, (HMENU)ID_BUTTON_FLOOR1_TO5, hInstance, NULL);

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
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HDC hdc;
        PAINTSTRUCT ps;
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

            case ID_BUTTON_FLOOR1_TO2:
                qpassengers.push_back(Human(1, 2));
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR1_TO3:
                qpassengers.push_back(Human(1, 3));
                break;
            case ID_BUTTON_FLOOR1_TO4:
                qpassengers.push_back(Human(1, 4));
                break;
            case ID_BUTTON_FLOOR1_TO5:
                qpassengers.push_back(Human(1, 5));
                break;

            case ID_BUTTON_FLOOR2_TO1:
                qpassengers.push_back(Human(2, 1));
                break;
            case ID_BUTTON_FLOOR2_TO3:
                qpassengers.push_back(Human(2, 3));
                break;
            case ID_BUTTON_FLOOR2_TO4:
                qpassengers.push_back(Human(2, 4));
                break;
            case ID_BUTTON_FLOOR2_TO5:
                qpassengers.push_back(Human(2, 5));
                break;

            case ID_BUTTON_FLOOR3_TO1:
                qpassengers.push_back(Human(3, 1));
                break;
            case ID_BUTTON_FLOOR3_TO2:
                qpassengers.push_back(Human(3, 2));
                break;
            case ID_BUTTON_FLOOR3_TO4:
                qpassengers.push_back(Human(3, 4));
                break;
            case ID_BUTTON_FLOOR3_TO5:
                qpassengers.push_back(Human(3, 5));
                break;

            case ID_BUTTON_FLOOR4_TO1:
                qpassengers.push_back(Human(4, 1));
                break;
            case ID_BUTTON_FLOOR4_TO2:
                qpassengers.push_back(Human(4, 2));
                break;
            case ID_BUTTON_FLOOR4_TO3:
                qpassengers.push_back(Human(4, 3));
                break;
            case ID_BUTTON_FLOOR4_TO5:
                qpassengers.push_back(Human(4, 5));
                break;

            case ID_BUTTON_FLOOR5_TO1:
                qpassengers.push_back(Human(5, 1));
                break;
            case ID_BUTTON_FLOOR5_TO2:
                qpassengers.push_back(Human(5, 2));
                break;
            case ID_BUTTON_FLOOR5_TO3:
                qpassengers.push_back(Human(5, 3));
                break;
            case ID_BUTTON_FLOOR5_TO4:
                qpassengers.push_back(Human(5, 4));
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
           
             hdc = BeginPaint(hWnd, &ps);
            // TODO: Tutaj dodaj kod rysujący używający elementu hdc...
            OnPaint(hdc);
            EndPaint(hWnd, &ps);
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_TIMER:
        switch (wParam) {
        case Timer1:
            if (end_floor != start_floor) {
                if (i != (end_floor - start_floor) * 120) {
                    i = i + (end_floor - start_floor) * 2;
                    przesuniecie = przesuniecie + (end_floor - start_floor) * 2;
                }
            }
            else {
                i = 0;
                KillTimer(hWnd, Timer1);
            }
            repaintWindow(hWnd, hdc, ps, NULL);
            
            break;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
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
