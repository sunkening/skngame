// skngame.cpp : 定义控制台应用程序的入口点。
//
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#define INITGUID
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <tchar.h>
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;

#include "td/GameApp.h"
#include "td/LOG.h"
#include "td/GWindow.h"
#include "td/GameAppExample.h"
#include<IOSTREAM>
using namespace std;
 
 

int _tmain(int ac,char *av[])

{
         HINSTANCE inst;
         inst=(HINSTANCE)GetModuleHandle(NULL);

		 GameAppExample app;
		 GWindow window;
		 window.create(inst,1,800,600,&app);
		 window.run();

		 return 1;
    

}
