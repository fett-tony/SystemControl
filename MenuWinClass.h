#ifndef MENUWINCLASS_H
#define MENUWINCLASS_H

#include <TaskClass.h>
#include <ServiceClass.h>
#include <Info.h>

using namespace std;

enum WinID { MENUWIN = 0, MAINWIN = 1, INFOWIN = 2, LISTPAD = 3, DESCWIN = 4, TIMEWIN = 5, ENDWIN = 6 };
enum MenuID { DATEIMENU = 0, DAEMONMENU = 1, SYSTEMCTLMENU = 2, INFOMENU = 3, MAINMENU = 4, ENDMENU = 5 };

struct FENSTER   {
    int     FEID         {0};
    string  FENAME       {""};
    int     BorderWeight {1};
    int     BorderHeight {1};
    int     WCX()        {return static_cast<int>(roundf(getmaxx(stdscr)));};  /* W=weight C=column X=x achse */
    int     HRY()        {return static_cast<int>(roundf(getmaxy(stdscr)));};  /* H=height R=row    Y=y achse */
    int     HRYw1()      {return static_cast<int>(roundf(1));};
    int     WCXw1()      {return static_cast<int>(roundf(WCX()));};
    WinID   TMPWin1ID    {MENUWIN};
    WINDOW  *TMPWin1     = newwin(HRYw1(), WCXw1(), 0, 0);
    int     HRYw2()      {return static_cast<int>(roundf(HRY() - (HRYw1() + HRYw3())));};
    int     WCXw2()      {return static_cast<int>(roundf(WCX()));};
    WinID   TMPWin2ID    {MAINWIN};
    WINDOW  *TMPWin2     = newwin(HRYw2(), WCXw2(), 1, 0);
    int     HRYw3()      {return static_cast<int>(roundf(6));};
    int     WCXw3()      {return static_cast<int>(roundf(WCX()));};
    WinID   TMPWin3ID    {INFOWIN};
    WINDOW  *TMPWin3     = newwin(HRYw3(), WCXw3(), (HRYw1() + HRYw2()), 0);
    int     HRYw4()      {return static_cast<int>(roundf(HRYw2() - ((BorderWeight * 2))));};
    int     WCXw4()      {return static_cast<int>(roundf(WCXw2() - (BorderWeight * 2)));};
    WinID   TMPWin4ID    {LISTPAD};
    WINDOW  *TMPWin4     = newpad(HRYw4(), WCXw4());
    int     HRYw5()      {return static_cast<int>(roundf(HRYw3() - ((BorderWeight * 2) + 1)));};
    int     WCXw5()      {return static_cast<int>(roundf(WCXw3() - ((BorderWeight * 2) + 32)));};
    WinID   TMPWin5ID    {DESCWIN};
    WINDOW  *TMPWin5     = newpad(HRYw5(), WCXw5());
    int     HRYtime()    {return static_cast<int>(roundf(1));};
    int     WCXtime()    {return static_cast<int>(roundf(20));};
    WinID   TimeWinID    {TIMEWIN};
    WINDOW  *TimeWin     = newwin(HRYtime(), WCXtime(), 0, (WCX() - 20));
    int     TMPWinHigh   {0};
    FORM    *TMPForm1    {nullptr};
    FIELD   **TMPField1  {nullptr};
    struct WinSize {
        int RAND = 1;
        int w {1};
        int h {1};
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
    } WinSize;
    struct WinColor {
        int BK_MENUWIN = 78; // 78 Text=MY_LIGHT_WHITE, Bk=MY_MARIN_BLUE
        int BK_MAINWIN = 78; // 87 Text=MY_MARIN_BLUE, Bk=MY_LIGHT_WHITE
        int BK_INFOWIN = 78;
        int BK_LISTPAD = 78;
        int BK_DESCWIN = 78;
        int BK_TIMEWIN = 70;
        int BK_HELPWIN = 74;
        int WinBk_Main = 78; //Fenster_Background
        int WinFo_Main = 78; //Fenster_Foreground
        int WinBk_Info = 78; //info fenster_Background
        int WinFo_Info = 78; //info fenster foreground
        int WinBk_Help = 74; //help fenster Background
        int WinFo_Help = 74; //help fenster foreground
    } WinColor;
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
            tmpwin=nullptr;
        }
    }
    /*    void delmenu(WINDOW *tmpwin, MENU *tmpmenu, ITEM **tmpitem){
        if (tmpmenu){
            int E = item_count(tmpmenu);
            unpost_menu(tmpmenu);
            SAFE_DELETE(tmpmenu);
            SAFE_DELETE_ARRAY(tmpitem);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,0,E+1);
            delwin(tmpwin);
            endwin();
        }
    }*/
    void delform(WINDOW *tmpwin, FORM *tmpform, FIELD **tmpfield){
        if (tmpform){
            int mx,my,bx,by;
            getbegyx(tmpwin,by,bx);
            getmaxyx(tmpwin,my,mx);
            unpost_form(tmpform);
            SAFE_DELETE(tmpform);
            SAFE_DELETE_ARRAY(tmpfield);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,bx,mx);
            delwin(tmpwin);
            endwin();
        }
    }
};
struct HAUPTMENU {
    MenuID     MID;
    string  HMName;
    MENU   *HMMenu {nullptr};
    ITEM  **HMItem {nullptr};
    //###############################################
    struct UNTERMENU {
        int       UMID;
        string UMEName;
        WINDOW *UMEWin;
        MENU  *UMEMenu;
        ITEM **UMEItem;
    }UME;
    struct MenuColor {
        int BK_MAINMENU  = 78; // 78 Text=MY_LIGHT_WHITE, Bk=MY_MARIN_BLUE
        int BK_UNTERMENU = 78; // 87 Text=MY_MARIN_BLUE, Bk=MY_LIGHT_WHITE
        int BK_AKTIVHAME = 18;
        int BK_AKTIVUNME = 18;
        int BK_UNUSEDHM  = 78;
        int BK_UNUSEDUM  = 78;
    } MenuColor;
    void LoescheUME(){
        int E = item_count(UME.UMEMenu);
        unpost_menu(UME.UMEMenu);
        SAFE_DELETE(UME.UMEMenu);
        SAFE_DELETE_ARRAY(UME.UMEItem);
        wborder(UME.UMEWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(UME.UMEWin,0,E+1);
        delwin(UME.UMEWin);
        endwin();
        refresh();
    }
};
struct INAPPMENU {
    friend class MenuWinClass;
    int                LMID;
    std::string      LMName;
    MENU*   LMenu {nullptr};
    ITEM** LMItem {nullptr};
    string AktivName = "";

};

class MenuWinClass: public INAPPMENU {
public:
    /*################################################*/
    static FENSTER START;
    static HAUPTMENU TOPMENU;
    static int MeInAl;
    static WINDOW *TMPWIN;
    static MENU *TMPMENU;
    static INAPPMENU SERVICEMENU;
    static int LiMeInAl;
    static WINDOW* LiTMPWIN;
    static MENU* LiTMPMENU;
    static string PATTERN;
    static int TabKey;// {1};
    /*#############_WINDOW_###########################*/
    static void StartWin();
    static void StopWin();
    static void SetWinSize();
    static void AppColor();
    static void CreateWin(WINDOW *win, WinID WID);
    void FensterDraw();
    static void ResizeHandler(int signal);
    void ScrollPad(WINDOW *SubWin, int StartY, int StartX, int Height, int Width, int PadHeight);
    void printInMiddle(WINDOW *win, int starty, int startx, int width, char *text, chtype color, char *sp);
    /*#############_MENÜ_#############################*/
    static void Hauptmenu(void);
    static void DateiMenu(void);
    static void DaemonTypeMenu(void);
    static void SystemctlMenu(void);
    static void InfoMenu(void);
    static WINDOW* TempWin(string Name, MenuID MID);
    static void StartMenuAuswahl(string wahl);
    static void RefreshWindows();
    static int MenuStart(int Key);
    /*#############_Constructor/De_###################*/
    MenuWinClass();
    ~MenuWinClass();
    /*################################################*/
};



#endif // MENUWINCLASS_H
