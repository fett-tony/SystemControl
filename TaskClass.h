#ifndef TASKCLASS_H
#define TASKCLASS_H

#include <ncursesw/cursesapp.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ncursesw/panel.h>
#include <ncursesw/unctrl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <csignal>
#include <thread>
#include <cstring>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <locale.h>
#include <systemd/sd-bus-vtable.h>
#include <systemd/sd-bus.h>
#include <term.h>

//#define CTRLD 4
#define BUFSIZE 8192
#define CLEARSCR system ( "clear" )
#define UNUSED(x) (void) (x)
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define SIZEOF(table) (sizeof(table) / sizeof(table[0]))
#define RST   "\x1B[0m";
#define KRED  "\x1B[31m";
#define KGRN  "\x1B[32m";
#define KYEL  "\x1B[33m";
#define KBLU  "\x1B[34m";
#define KMAG  "\x1B[35m";
#define KCYN  "\x1B[36m";
#define KWHT  "\x1B[37m";
#define FRED(x) KRED x RST;
#define FGRN(x) KGRN x RST;
#define FYEL(x) KYEL x RST;
#define FBLU(x) KBLU x RST;
#define FMAG(x) KMAG x RST;
#define FCYN(x) KCYN x RST;
#define FWHT(x) KWHT x RST;

using namespace std;

struct DatumUhrZeit {
    int               n = 0;
    time_t      Zeitstempel;
    tm*             UHRZEIT;
    char    UHRZEITchar[19];
    std::string  UHRZEITstr;
    void TIMEFIELD(WINDOW* TMPWin, int TMPmax_xc) {
        Zeitstempel = time(nullptr);
        UHRZEIT = localtime(&Zeitstempel);
        strftime(UHRZEITchar, size_t(UHRZEITchar), "%d.%m.%Y %T", UHRZEIT);
        UHRZEITstr = std::string(UHRZEITchar);
        wattr_on(TMPWin, COLOR_PAIR(79) | A_STANDOUT | A_BOLD, nullptr); //|A_BOLD,0);
        mvwaddnstr(TMPWin, 0, 0, UHRZEITstr.c_str(), -1);
        wattr_off(TMPWin, COLOR_PAIR(79) | A_STANDOUT | A_BOLD, nullptr); //|A_BOLD,0);
        refresh();
        wrefresh(TMPWin); //TMPmax_xc-2
    }
};

class TaskClass {
  public:
    /*##############################################################################*/
    int ZahlenWerk(int zahlen, std::string i, int max);
    int Zeilen(std::string data, int maxbreite);
    vector<string> StringTeiler(const std::string& str, char delimiter);
    string TERM_AUSGABE(std::string cmd);
    WINDOW* ClearWindow(WINDOW* W);
    int WinFullSize(WINDOW* TmpWin, int WHCRXY, std::string WorH);
    TaskClass();
    ~TaskClass();
    /*##############################################################################*/
};

#endif // TASKCLASS_H
