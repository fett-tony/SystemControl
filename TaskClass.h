#ifndef TASKCLASS_H
#define TASKCLASS_H

#include <ncursesw/cursesapp.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ncursesw/panel.h>
#include <ncursesw/unctrl.h>
#include <csignal>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <vector>
//thrade lib
#include <thread>
//thrade lib
#include <term.h>
#include <set>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <sys/wait.h>
#include <systemd/sd-bus-vtable.h>
#include <systemd/sd-bus.h>
#include <stdarg.h>
#include <locale.h>
//#include <yaml-cpp/yaml.h>
#include <stdnoreturn.h>

#ifdef __GNUC__
#define NO_RETURN __attribute__((noreturn))
#elif __MINGW32__
#define NO_RETURN __attribute__((noreturn))
#elif __clang__
#define NO_RETURN __attribute__((noreturn))
#elif _MSC_VER
#define NO_RETURN __declspec(noreturn)
#endif

//#define     CTRLD                   4
#define     BUFSIZE                 8192
#define     CLEARSCR system         ( "clear" )
#define     UNUSED(x)               (void) (x)
#define     SAFE_DELETE(p)          { if(p) { delete (p); (p) = nullptr; } }
#define     SAFE_DELETE_ARRAY(p)    { if(p) { delete[] (p); (p) = nullptr; } }
#define     ARRAY_SIZE(a)           (sizeof(a) / sizeof(a[0]))
#define     SIZEOF(table)           (sizeof(table) / sizeof(table[0]))

#define RST   "\x1B[0m":
#define KRED  "\x1B[31m":
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

struct DatumUhrZeit {
    int               n = 0;
    time_t      Zeitstempel;
    tm             *UHRZEIT;
    char    UHRZEITchar[19];
    std::string  UHRZEITstr;
    void TIMEFIELD(WINDOW *TMPWin, int TMPmax_xc) {
        Zeitstempel = time(nullptr);
        UHRZEIT = localtime(&Zeitstempel);
        strftime(UHRZEITchar, size_t(UHRZEITchar), "%d.%m.%Y %T", UHRZEIT);
        UHRZEITstr = std::string(UHRZEITchar);
        wattr_on(TMPWin, COLOR_PAIR(79)|A_STANDOUT|A_BOLD,nullptr);//|A_BOLD,0);
        mvwaddnstr(TMPWin, 0, 0, UHRZEITstr.c_str(), -1);
        wattr_off(TMPWin, COLOR_PAIR(79)|A_STANDOUT|A_BOLD,nullptr);//|A_BOLD,0);
        refresh();
        wrefresh(TMPWin); //TMPmax_xc-2
    }
};


class TaskClass {
public:
    DatumUhrZeit DateTime;
    void set_flag(int signal);
    void process_signal(std::string command);
    void execute(std::string command);
    static void Resize_Handler(int sig);
    typedef struct {
        int min;
        int max;
        int count(){return max - min;}
        int range{1};
    } RANGE;
    int      ZahlenWerk(int zahlen, std::string i, int max);
    int      ZahlenBerechnen(int posa, RANGE range, std::string wahl);
    int      RangeZahlenWerk(int mina, int posa, int maxa, std::string wahl);
    int      Zeilen(std::string data, int maxbreite);
    std::vector<std::string> StringTeiler(const std::string& str, char delimiter);
    //##############################################################################
    std::string   TERM_AUSGABE(std::string cmd);
    //##############################################################################
    void      centerplace(int hoehe, int weite);
    //##############################################################################
    //--------------------Verlassen-und-Löschen-------------------------------------
    void     TermQuit(int);
    WINDOW   *ClearWindow(WINDOW *W);
    void     ClearScreen();
    void     DeletAllWin(const char *namem);
    int WinFullSize(WINDOW * TmpWin, int WHCRXY, std::string WorH);
    //##############################################################################
    std::string filename;
    std::vector<std::string> ConfigDateiList;
    int CountConfigDatei;
    //###############################################################################

    TaskClass();
    ~TaskClass();
};

#endif // TASKCLASS_H
