#include <src/ServiceClass.h>
#include <src/MenuClass.h>
#include <src/WinClass.h>
#include <src/TaskClass.h>
#include <src/Info.h>

using namespace std;

extern class TaskClass * TaskPtr;
extern class MenuClass * MenuPtr;
extern class ServiceClass * ServicePtr;
//extern class WinClass * WinPtr;
extern class ServiceTableClass * TablePtr;

WinClass::WinClass() {
    WinSize->RAND = 1;
    WinSize->h = 1; //rand
    WinSize->w = 1;
    WinSize->WCX(); // = 80;
    WinSize->HRY(); // = 24;
    WinSize->WCX_Real();
    WinSize->HRY_Real();
    WinSize->WCX_Center();
    WinSize->HRY_Center();
    WinSize->WCX_TmpWin(stdscr);
    WinSize->HRY_TmpWin(stdscr);
    WinSize->WCX_TmpWinReal(stdscr);
    WinSize->HRY_TmpWinReal(stdscr);
    WinSize->WCX_TmpWinCenter(stdscr);
    WinSize->HRY_TmpWinCenter(stdscr);
}

void WinClass::AppColor() {
    //start_color();
    short MY_MARIN_BLUE=240, MY_LIGHT_BLUE=250;
    short R=0,G=0;//,B=0;
    init_color(MY_MARIN_BLUE, R, G, static_cast<short int>(300));
    init_color(MY_LIGHT_BLUE, R, G, static_cast<short int>(850));
    // 0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 magenta,
    // 6 cyan, 7 white, 8 marin blue, 9 light blue
    /* hintergrund Schwarz */
    init_pair(00, COLOR_BLACK,  COLOR_BLACK);
    init_pair(10, COLOR_RED,    COLOR_BLACK);
    init_pair(20, COLOR_GREEN,  COLOR_BLACK);
    init_pair(30, COLOR_YELLOW, COLOR_BLACK);
    init_pair(40, COLOR_BLUE,   COLOR_BLACK);
    init_pair(50, COLOR_MAGENTA,COLOR_BLACK);
    init_pair(60, COLOR_CYAN,   COLOR_BLACK);
    init_pair(70, COLOR_WHITE,  COLOR_BLACK);
    init_pair(80, MY_MARIN_BLUE,COLOR_BLACK);
    init_pair(90, MY_LIGHT_BLUE,COLOR_BLACK);
    /* hintergrund Rot */
    init_pair(01, COLOR_BLACK,  COLOR_RED);
    init_pair(11, COLOR_RED,    COLOR_RED);
    init_pair(21, COLOR_GREEN,  COLOR_RED);
    init_pair(31, COLOR_YELLOW, COLOR_RED);
    init_pair(41, COLOR_BLUE,   COLOR_RED);
    init_pair(51, COLOR_MAGENTA,COLOR_RED);
    init_pair(61, COLOR_CYAN,   COLOR_RED);
    init_pair(71, COLOR_WHITE,  COLOR_RED);
    init_pair(81, MY_MARIN_BLUE,COLOR_RED);
    init_pair(91, MY_LIGHT_BLUE,COLOR_RED);
    /* hintergrund Gruen */
    init_pair(02, COLOR_BLACK,  COLOR_GREEN);
    init_pair(12, COLOR_RED,    COLOR_GREEN);
    init_pair(22, COLOR_GREEN,  COLOR_GREEN);
    init_pair(32, COLOR_YELLOW, COLOR_GREEN);
    init_pair(42, COLOR_BLUE,   COLOR_GREEN);
    init_pair(52, COLOR_MAGENTA,COLOR_GREEN);
    init_pair(62, COLOR_CYAN,   COLOR_GREEN);
    init_pair(72, COLOR_WHITE,  COLOR_GREEN);
    init_pair(82, MY_MARIN_BLUE,COLOR_GREEN);
    init_pair(92, MY_LIGHT_BLUE,COLOR_GREEN);
    /* hintergrund Gelb */
    init_pair(03, COLOR_BLACK,  COLOR_YELLOW);
    init_pair(13, COLOR_RED,    COLOR_YELLOW);
    init_pair(23, COLOR_GREEN,  COLOR_YELLOW);
    init_pair(33, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(43, COLOR_BLUE,   COLOR_YELLOW);
    init_pair(53, COLOR_MAGENTA,COLOR_YELLOW);
    init_pair(63, COLOR_CYAN,   COLOR_YELLOW);
    init_pair(73, COLOR_WHITE,  COLOR_YELLOW);
    init_pair(83, MY_MARIN_BLUE,COLOR_YELLOW);
    init_pair(93, MY_LIGHT_BLUE,COLOR_YELLOW);
    /* hintergrund Blau */
    init_pair(04, COLOR_BLACK,  COLOR_BLUE);
    init_pair(14, COLOR_RED,    COLOR_BLUE);
    init_pair(24, COLOR_GREEN,  COLOR_BLUE);
    init_pair(34, COLOR_YELLOW, COLOR_BLUE);
    init_pair(44, COLOR_BLUE,   COLOR_BLUE);
    init_pair(54, COLOR_MAGENTA,COLOR_BLUE);
    init_pair(64, COLOR_CYAN,   COLOR_BLUE);
    init_pair(74, COLOR_WHITE,  COLOR_BLUE);
    init_pair(84, MY_MARIN_BLUE,COLOR_BLUE);
    /* hintergrund Magenta */
    init_pair(05, COLOR_BLACK,  COLOR_MAGENTA);
    init_pair(15, COLOR_RED,    COLOR_MAGENTA);
    init_pair(25, COLOR_GREEN,  COLOR_MAGENTA);
    init_pair(35, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(45, COLOR_BLUE,   COLOR_MAGENTA);
    init_pair(55, COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(65, COLOR_CYAN,   COLOR_MAGENTA);
    init_pair(75, COLOR_WHITE,  COLOR_MAGENTA);
    /* hintergrund Cyan */
    init_pair(06, COLOR_BLACK,  COLOR_CYAN);
    init_pair(16, COLOR_RED,    COLOR_CYAN);
    init_pair(26, COLOR_GREEN,  COLOR_CYAN);
    init_pair(36, COLOR_YELLOW, COLOR_CYAN);
    init_pair(46, COLOR_BLUE,   COLOR_CYAN);
    init_pair(56, COLOR_MAGENTA,COLOR_CYAN);
    init_pair(66, COLOR_CYAN,   COLOR_CYAN);
    init_pair(76, COLOR_WHITE,  COLOR_CYAN);
    init_pair(86, MY_MARIN_BLUE,COLOR_CYAN);
    init_pair(96, MY_LIGHT_BLUE,COLOR_CYAN);
    /* hintergrund White */
    init_pair(07, COLOR_BLACK,  COLOR_WHITE);
    init_pair(17, COLOR_RED,    COLOR_WHITE);
    init_pair(27, COLOR_GREEN,  COLOR_WHITE);
    init_pair(37, COLOR_YELLOW, COLOR_WHITE);
    init_pair(47, COLOR_BLUE,   COLOR_WHITE);
    init_pair(57, COLOR_MAGENTA,COLOR_WHITE);
    init_pair(67, COLOR_CYAN,   COLOR_WHITE);
    init_pair(77, COLOR_WHITE,  COLOR_WHITE);
    init_pair(87, MY_MARIN_BLUE,COLOR_WHITE);
    init_pair(97, MY_LIGHT_BLUE,COLOR_WHITE);
    /* hintergrund Marin Blau */
    init_pair(8, COLOR_BLACK,  MY_MARIN_BLUE);
    init_pair(18, COLOR_RED,    MY_MARIN_BLUE);
    init_pair(28, COLOR_GREEN,  MY_MARIN_BLUE);
    init_pair(38, COLOR_YELLOW, MY_MARIN_BLUE);
    init_pair(48, COLOR_BLUE,   MY_MARIN_BLUE);
    init_pair(58, COLOR_MAGENTA,MY_MARIN_BLUE);
    init_pair(68, COLOR_CYAN,   MY_MARIN_BLUE);
    init_pair(78, COLOR_WHITE,  MY_MARIN_BLUE);
    init_pair(88, MY_MARIN_BLUE,MY_MARIN_BLUE);
    init_pair(98, MY_LIGHT_BLUE,MY_MARIN_BLUE);
    /* hintergrund Light Blue */
    init_pair(9, COLOR_BLACK,  MY_LIGHT_BLUE);
    init_pair(19, COLOR_RED,    MY_LIGHT_BLUE);
    init_pair(29, COLOR_GREEN,  MY_LIGHT_BLUE);
    init_pair(39, COLOR_YELLOW, MY_LIGHT_BLUE);
    init_pair(49, COLOR_BLUE,   MY_LIGHT_BLUE);
    init_pair(59, COLOR_MAGENTA,MY_LIGHT_BLUE);
    init_pair(69, COLOR_CYAN,   MY_LIGHT_BLUE);
    init_pair(79, COLOR_WHITE,  MY_LIGHT_BLUE);
    init_pair(89, MY_MARIN_BLUE,MY_LIGHT_BLUE);
    init_pair(99, MY_LIGHT_BLUE,MY_LIGHT_BLUE);

} /*---------Programm_Farben------------------------*/

void WinClass::FensterDesign() {
    if (MenuPtr->MENEU.HMWin)  {werase(MenuPtr->MENEU.HMWin);  delwin(MenuPtr->MENEU.HMWin);  endwin();}
    if (MenuPtr->LiMENU.LMWin) {werase(MenuPtr->LiMENU.LMWin); delwin(MenuPtr->LiMENU.LMWin); endwin();}
    if (MenuPtr->NEW_UNIT_MENU.LMWin) {werase(MenuPtr->NEW_UNIT_MENU.LMWin); delwin(MenuPtr->NEW_UNIT_MENU.LMWin); endwin();}
    if (START.TimeWin) {werase(START.TimeWin); delwin(START.TimeWin); endwin();}
    if (START.TMPWin1) {werase(START.TMPWin1); delwin(START.TMPWin1); endwin();}
    if (START.TMPWin2) {werase(START.TMPWin2); delwin(START.TMPWin2); endwin();}
    if (START.TMPWin3) {werase(START.TMPWin3); delwin(START.TMPWin3); endwin();}
    if (START.TMPWin4) {werase(START.TMPWin4); delwin(START.TMPWin4); endwin();}
    if (START.TMPWin5) {werase(START.TMPWin5); delwin(START.TMPWin5); endwin();}
    //
    START.FEID = 0;
    START.FENAME = string("VARSYSMAN");
    START.TimeWin = newwin(1, 20, 0, WinSize->WCX()-20);
    START.TMPWin1 = newwin(1, WinSize->WCX(), 0, 0);
    MenuPtr->MENEU.HMWin = derwin(START.TMPWin1, 1, WinSize->WCX()-20, 0, 0);
    START.TimeWin = derwin(START.TMPWin1, 1, 20, 0, WinSize->WCX()-20);
    wbkgd(START.TMPWin1, COLOR_PAIR(MenuPtr->HMcolor.HaMeFe_HG));
    // Hauptfenster TMPWin2
    START.TMPWin2 = newwin(WinSize->HRY() -7, WinSize->WCX(), 1, 0); //-1 -20
    wbkgd(START.TMPWin2, COLOR_PAIR(WindowColor.FeBk_Main));
    box(START.TMPWin2, 0,0);
    // Listen Menü LMWin at the MainWindow as PAD
    MenuPtr->LiMENU.LMWin = newpad(WinSize->HRY() -9, WinSize->WCX()-2); //-5 -20
    wbkgd(MenuPtr->LiMENU.LMWin, COLOR_PAIR(WindowColor.FeBk_Main));
    MenuPtr->LiMENU.LMWin = derwin(START.TMPWin2, WinSize->HRY_TmpWinReal(START.TMPWin2), WinSize->WCX_TmpWinReal(START.TMPWin2), 3, 2); //-4 -20
    //MenuPtr->NEW_UNIT_MENU.LMWin = derwin(START.TMPWin2, WinSize->HRY_REALMAINWIN(START.TMPWin2), WinSize->WCX_REALMAINWIN(START.TMPWin2), 3, 2); //-4 -20
    // Secondary Window on the bottom, hinweiss leiste unten TMPWin4
    START.TMPWin4 = newwin(WinSize->HRY() -18, WinSize->WCX(), WinSize->HRY()-6, 0);//-1 -60 1 -20
    box_set(START.TMPWin4, 0,0);
    wbkgd(START.TMPWin4, COLOR_PAIR(WindowColor.FeBk_Info));
    wattr_on(START.TMPWin4, COLOR_PAIR(01)|A_BOLD,nullptr);
    mvwaddnstr(START.TMPWin4, WinSize->HRY_TmpWin(START.TMPWin4) -1, WinSize->WCX_TmpWin(START.TMPWin4) -14, "[ EXIT F10 ]" ,-1); //12+2
    mvwaddnstr(START.TMPWin4, WinSize->HRY_TmpWin(START.TMPWin4) -1, WinSize->WCX_TmpWin(START.TMPWin4) -26, "[ MENÜ TAB ]" ,-1);  //11+2
    wattr_off(START.TMPWin4, COLOR_PAIR(01)|A_BOLD,nullptr);
    // Description fenster unten
    START.TMPWin5 = newwin(3, WinSize->WCX() -33, WinSize->HRY()-5, WinSize->WCX() -48);
    wbkgd(START.TMPWin5, COLOR_PAIR(WindowColor.FeFo_Info)|A_BOLD); //42
    START.TMPWin5 = derwin(START.TMPWin4, 3, WinSize->WCX() -33, 1, WinSize->WCX() -48);
    //ServicePtr->ServiceListFill();
    // Service_Class.ServiceHauptMenu();
} /*---------Fenster sub----------------------------*/

void WinClass::ScrollPad(WINDOW * SubWin, int StartY, int StartX, int Height, int Width, int PadHeight) {
    int Choice = 0, Key = 0;
    keypad(SubWin, true);
    refresh();
    int cols = 0;
    while (Choice == 0) {
        prefresh(SubWin, cols,0,StartY,StartX,Height,Width);
        Key = wgetch(SubWin);
        switch(Key)
        {
        case KEY_UP:
        {
            if (cols <= 0) continue;
            cols--;
            break;
        }
        case KEY_DOWN:
        {
            if (cols+Height+1 >= PadHeight) continue;
            cols++;
            break;
        }
        case KEY_PPAGE: /* Page Up */
        {
            if (cols <= 0) continue;
            cols -= Height;
            if (cols < 0) cols = 0;
            break;
        }
        case KEY_NPAGE: /* Page Down */
            if (cols+Height+1 >= PadHeight) continue;
            cols += Height;
            if (cols+Height+1 > PadHeight) cols = PadHeight-Height-1;
            break;
        case KEY_HOME:
            cols = 0;
            break;
        case KEY_END:
            cols = PadHeight-Height-1;
            break;
        case 10: /* Enter */
        {
            Choice = 1;
            break;
        }
        }
        refresh();
    }
    delwin(SubWin);
}

void WinClass::FensterDraw() {
    FensterDesign();
    MenuPtr->Hauptmenu();
    ServicePtr->INFOWINDOW("");
    ServicePtr->ServiceListFill();
}

void WinClass::ChangeSize() {
    StopWin();
    StartWin();
    FensterDraw();
}

//________________new_Systemd_________________

WinClass::~WinClass(){
    if (START.TMPWin1) {werase(START.TMPWin1); delwin(START.TMPWin1); endwin();}
    if (START.TMPWin2) {werase(START.TMPWin2); delwin(START.TMPWin2); endwin();}
    if (START.TMPWin3) {werase(START.TMPWin3); delwin(START.TMPWin3); endwin();}
    if (START.TMPWin4) {werase(START.TMPWin4); delwin(START.TMPWin4); endwin();}
    if (START.TMPWin5) {werase(START.TMPWin5); delwin(START.TMPWin5); endwin();}
};

