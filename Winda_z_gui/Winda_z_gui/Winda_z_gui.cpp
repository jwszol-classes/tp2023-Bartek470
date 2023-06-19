

#include "framework.h"
#include "Winda_z_gui.h"

#define MAX_LOADSTRING 100
#define Timer1 1
//Stale globalne
const unsigned int NUMBER_OF_FLOORS = 5;
const unsigned int ELEVATOR_CAPACITY = 10;
const unsigned int LIFTING_CAPACITY = 600;
//charakterystyka windy

const unsigned int MIN_PASSANGER_WEIGHT = 60;
const unsigned int MAX_PASSANGER_WEIGHT = 80;
//zakres wagi pasazerow
int offset = 0;
int i = 0;
int timer = 0;

// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego




//handlery przyciskow
HWND hwndButton, hwndText;

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
    bool isinside;
public:
    unsigned int get_start()
    {
        return start_floor;
    }
    unsigned int get_end()
    {
        return end_floor;
    }
    bool get_isinside()
    {
        return isinside;
    }
    void set_isinside()
    {
        isinside = 1;
    }
    unsigned int how_heavy()
    {
        return weight;
    }

    Human(unsigned int x, unsigned int y)
    {
        start_floor = x;
        end_floor = y;
        srand(time(NULL));
        weight = MIN_PASSANGER_WEIGHT + rand() % (MAX_PASSANGER_WEIGHT - MIN_PASSANGER_WEIGHT);
        isinside = false;
    }
    ~Human()
    {
        start_floor = NULL;
        end_floor = NULL;
        weight = NULL;
        isinside = NULL;
    }
};

class Elevator
{
private:

    unsigned int curentposition;
    unsigned int nextposition;
    unsigned int load;
    bool ismoving; 
    unsigned int capacity;

public:
    unsigned int get_capacity()
    {
        return capacity;
    }
    void add_capacity()
    {
        capacity++;
    }
    void sub_capacity()
    {
        capacity--;
    }
    unsigned int get_curentposition()
    {
        return curentposition;
    }
    unsigned int get_nextposition()
    {
        return nextposition;
    }
    void set_nextposition(int x)
    {
        nextposition = x;
    }
    void curentPositionEqual()
    {
        curentposition = nextposition;
    }
    unsigned int get_load()
    {
        return load;
    }
    void add_load(unsigned int x)
    {
        load = load + x;
    }
    void sub_load(unsigned int x)
    {
        load = load - x;
    }
    void starte()
    {
        ismoving =true;
    }
    void stope()
    {
        ismoving = false;
    }
    bool isitmoving()
    {
        return ismoving;
    }
    Elevator()
    {
        curentposition = 1;
        load = 0;
        ismoving = false;
        capacity = 0;
    }

};

Elevator elevator;
std::vector<Human>qpassengers;
void serch_vector(std::vector <Human> qpassengers)
{
    int vsize = qpassengers.size();
    int factor = (int)elevator.get_curentposition();
    std::vector<int> holder;
    std::vector<unsigned int> bufor;
    int hp;
    int anwser = 0;
    int best_cell = 0;
    int lowest_value = 11;
   
    if (vsize == 0)elevator.set_nextposition(elevator.get_curentposition());
    else if (elevator.get_capacity() >= ELEVATOR_CAPACITY)
    {
        for (int x = 0; x < vsize; x++)
        {

            if (qpassengers[x].get_isinside() == 1)
            {
                bufor.push_back(qpassengers[x].get_end());
                hp = abs((int)qpassengers[x].get_end() - factor);
                if (hp == 0)
                    holder.push_back(10);
                else
                    holder.push_back(hp);
            }
            else
                holder.push_back(10);
        }
    }
    else
    {
        for (int x = 0; x < vsize; x++)
        {
            bufor.push_back(qpassengers[x].get_start());
            hp = abs((int)qpassengers[x].get_start() - factor);
            if (hp == 0)
                holder.push_back(10);
            else
                holder.push_back(hp);

            if (qpassengers[x].get_isinside() == 1)
            {
                bufor.push_back(qpassengers[x].get_end());
                hp = abs((int)qpassengers[x].get_end() - factor);
                if (hp == 0)
                    holder.push_back(10);
                else
                    holder.push_back(hp);
            }
        }
    }
    int hsize = holder.size();

    for (int x = 0; x < hsize; x++)
    {
        if (holder[x] < lowest_value)
            best_cell = x;
    }
    if(vsize !=0)
    elevator.set_nextposition(bufor[best_cell]);
}

void beggin()
{
    int qsize = qpassengers.size();
    for (int x=0; x < qsize; x++)
    {
        if (qpassengers[x].get_isinside() == 0 and qpassengers[x].get_start() == elevator.get_curentposition() and elevator.get_capacity() < ELEVATOR_CAPACITY and elevator.get_load() < LIFTING_CAPACITY-80)
        {
            qpassengers[x].set_isinside();
            elevator.add_capacity();
            elevator.add_load(qpassengers[x].how_heavy());
        }
    }
}

//wysiadanie
void arrive(std::vector <Human>& qpassengers)
{
    int qsize = qpassengers.size();
    std::vector<int>eraser;
    for (int x = 0; x <qsize; x++)
    {
        if (qpassengers[x].get_isinside() == 1 && qpassengers[x].get_end() == elevator.get_curentposition())
        {
            elevator.sub_capacity();
            elevator.sub_load(qpassengers[x].how_heavy());
            eraser.push_back(x);
        }
    }
    int esize = eraser.size();
    if (esize > 0)
    {
        for (int x = esize - 1; x >= 0; x--)
        {
            qpassengers.erase(qpassengers.begin() + eraser[x]);
        }
    }
}
void scale(HDC hdc)
{
    TCHAR text[256];
    swprintf_s(text, 256, L"Obciazenie: %d", elevator.get_load());
    TextOut(hdc, 390, 10, text, wcslen(text));
}


void OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen1(Color(255, 0, 0,0),5.0);
    Pen pen2(Color(200, 0, 150, 255), 3.0);
    Pen pen3(Color(150, 0, 0, 0), 2.0);
    Pen pen4(Color(255, 255, 0, 0),2.0);
    Pen pen5(Color(255, 0, 255, 0), 2.0);

    //pietra
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
    for(int x = 0; x < elevator.get_capacity();x++)
    {
     graphics.DrawRectangle(&pen4, 100 + (20*x), 560 - offset, 20, 30);
    }
    

    //winda
    graphics.DrawRectangle(&pen2, 100, 500 - offset, 200, 90);
    graphics.DrawRectangle(&pen3, 198, 1 - offset, 4, 498);
    scale(hdc);
}
void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps)
{
    InvalidateRect(hWnd, NULL, TRUE); 
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
   
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_WINDAZGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDAZGUI));
    

    
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


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
   hInst = hInstance; 

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
                if(!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR1_TO3:
                qpassengers.push_back(Human(1, 3));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR1_TO4:
                qpassengers.push_back(Human(1, 4));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR1_TO5:
                qpassengers.push_back(Human(1, 5));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;

            case ID_BUTTON_FLOOR2_TO1:
                qpassengers.push_back(Human(2, 1));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR2_TO3:
                qpassengers.push_back(Human(2, 3));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR2_TO4:
                qpassengers.push_back(Human(2, 4));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR2_TO5:
                qpassengers.push_back(Human(2, 5));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;

            case ID_BUTTON_FLOOR3_TO1:
                qpassengers.push_back(Human(3, 1));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR3_TO2:
                qpassengers.push_back(Human(3, 2));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR3_TO4:
                qpassengers.push_back(Human(3, 4));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR3_TO5:
                qpassengers.push_back(Human(3, 5));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;

            case ID_BUTTON_FLOOR4_TO1:
                qpassengers.push_back(Human(4, 1));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR4_TO2:
                qpassengers.push_back(Human(4, 2));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR4_TO3:
                qpassengers.push_back(Human(4, 3));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR4_TO5:
                qpassengers.push_back(Human(4, 5));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;

            case ID_BUTTON_FLOOR5_TO1:
                qpassengers.push_back(Human(5, 1));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR5_TO2:
                qpassengers.push_back(Human(5, 2));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR5_TO3:
                qpassengers.push_back(Human(5, 3));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
                break;
            case ID_BUTTON_FLOOR5_TO4:
                qpassengers.push_back(Human(5, 4));
                if (!elevator.isitmoving())
                serch_vector(qpassengers);
                
                SetTimer(hWnd, Timer1, 15, (TIMERPROC)NULL);
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
    case WM_TIMER: //do przepisania
        switch (wParam) {
        case Timer1:
            if (qpassengers.size() != 0)
            {
                if (elevator.get_nextposition() != 0)
                {
                    if (elevator.get_curentposition() != elevator.get_nextposition());
                    if (i != (elevator.get_nextposition() - elevator.get_curentposition()) * 120) { //wyznacza ilosc pikseli o jakie ma sie przemiescic do pietra startowego
                        i = i + (elevator.get_nextposition() - elevator.get_curentposition()) * 2;
                        offset = offset + (elevator.get_nextposition() - elevator.get_curentposition()) * 2;
                        elevator.starte();
                    }
                    else {
                        elevator.curentPositionEqual();
                        
                        arrive(qpassengers);
                        
                        beggin();
                        Sleep(500);
                        serch_vector(qpassengers);
                        i = 0;
                        if (qpassengers.empty()) {
                            elevator.stope();
                          
                            //KillTimer(hWnd, Timer1);
                        }
                    }
                }
            }
            else {
                if (elevator.isitmoving() == false) {
                    elevator.set_nextposition(1);
                    timer = timer + 15;
                    if (timer > 5000) {
                        if (offset != 0) {
                            offset = offset - 2;
                        }
                        else {
                            elevator.curentPositionEqual();
                            KillTimer(hWnd, Timer1);
                        }
                    }
                }
            }

                
            repaintWindow(hWnd, hdc, ps);
            
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
