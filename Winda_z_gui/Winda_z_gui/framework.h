// header.h: plik dołączany dla standardowych systemowych plików dołączanych,
// lub pliki dołączane specyficzne dla projektu
//

#pragma once

#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN             // Wyklucz rzadko używane rzeczy z nagłówków systemu Windows
// Pliki nagłówkowe systemu Windows
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


// Pliki nagłówkowe środowiska uruchomieniowego języka C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <stdlib.h> //srand, rand
#include <time.h> //time
//potrzebne do zapoczątkowania ziarna losującego oraz wygenerowania liczby losowej
#include <iostream>
//#include <queue>
#include<vector>