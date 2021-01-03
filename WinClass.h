#ifndef WINCLASS_H
#define WINCLASS_H

#include <src/TaskClass.h>

struct FensterColor {
    int FeBk_Main = 78; //Fenster_Background
    int FeFo_Main = 78; //Fenster_Foreground
    int FeBk_Info = 71; //info fenster_Background
    int FeFo_Info = 71; //info fenster foreground
    int FeBk_Help = 74; //help fenster Background
    int FeFo_Help = 74; //help fenster foreground
};

typedef struct RECTANGLE {
    int RAND = 1;
    int WCX(){return static_cast<int>(roundf(getmaxx(stdscr)));};
    int HRY(){return static_cast<int>(roundf(getmaxy(stdscr)));};
    int WCX_Real(){return static_cast<int>(roundf(WCX() - (2 * RAND)));}
    int HRY_Real(){return static_cast<int>(roundf(HRY() - (2 * RAND)));}
    int WCX_Center(){return static_cast<int>(roundf(WCX() / 2));};
    int HRY_Center(){return static_cast<int>(roundf(HRY() / 2));};
    int WCX_TmpWin(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxx(tmpwin)));};
    int HRY_TmpWin(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxy(tmpwin)));};
    int WCX_TmpWinReal(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxx(tmpwin) - (2 * RAND)));};
    int HRY_TmpWinReal(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxy(tmpwin) - (2 * RAND)));};
    int WCX_TmpWinCenter(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxx(tmpwin) / 2));};
    int HRY_TmpWinCenter(WINDOW * tmpwin){return static_cast<int>(roundf(getmaxy(tmpwin) / 2));};
    unsigned long WinHalfDurch(WINDOW * tmpwin, int TeilDurch){return static_cast<int>(roundf(WCX_TmpWinCenter(tmpwin) / TeilDurch));};
    int w {1};
    int h {1};
} RECTANGLE;

struct FENSTER {
    int    FEID              {0};
    std::string FENAME      {""};
    WINDOW *TimeWin    {nullptr};
    WINDOW *TMPWin1    {nullptr};
    WINDOW *TMPWin2    {nullptr};
    WINDOW *TMPWin3    {nullptr};
    WINDOW *TMPWin4    {nullptr};
    WINDOW *TMPWin5    {nullptr};
    int    TMPWinHigh        {0};
    void delwinow(WINDOW *tmpwin){
        if(tmpwin){
            int mx,my,bx,by;
            getbegyx(tmpwin,by,bx);
            getmaxyx(tmpwin,my,mx);
            touchwin(tmpwin);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,bx,mx);
            delwin(tmpwin);
            endwin();
            tmpwin = nullptr;
        }
    }
};

class WinClass {
public:
    RECTANGLE * WinSize = new RECTANGLE;
    FENSTER START;
    FensterColor WindowColor;
    void StartWin();
    void StopWin();
    void SetSize();
    void AppColor();
    void FensterDesign();
    void ScrollPad(WINDOW * SubWin, int StartY, int StartX, int Height, int Width, int PadHeight);
    void printInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color, char *sp);
    void FensterDraw();
    void ChangeSize();
//#########_ende_new_systemd________________
    WinClass();
    ~WinClass();

};



#endif // WINCLASS_H
