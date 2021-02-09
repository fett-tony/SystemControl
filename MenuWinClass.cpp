 #include <MenuWinClass.h>

using namespace std;

TaskClass *TaskClass_MWC = new TaskClass();
ServiceClass *ServiceClass_MWC = new ServiceClass();
MenuWinClass *MenuWinClass_MWC = new MenuWinClass();

FENSTER MenuWinClass::START;
HAUPTMENU MenuWinClass::TOPMENU;
WINDOW* MenuWinClass::TMPWIN;
MENU* MenuWinClass::TMPMENU;
int MenuWinClass::MeInAl = 0;
INAPPMENU MenuWinClass::SERVICEMENU;
int MenuWinClass::LiMeInAl;
WINDOW* MenuWinClass::LiTMPWIN;
MENU* MenuWinClass::LiTMPMENU;
string MenuWinClass::PATTERN;
ServiceClass ServiceClass;
vector<SERVICES> ServiceList;
int MenuWinClass::TabKey = 1;

WinID&   operator++(WinID&   WID, int)      {
    return WID = (WID == WinID::ENDWIN) ? WinID::MAINWIN : static_cast<WinID>(static_cast<int>(WID) + 1);
};
WinID&   operator--(WinID&   WID, int)      {
    return WID = (WID == WinID::ENDWIN) ? WinID::MAINWIN : static_cast<WinID>(static_cast<int>(WID) - 1);
};
ostream& operator<<(ostream& WID, WinID e)  {
    static const vector<string> EnumString = {"MENUWIN", "MAINWIN", "TERMWIN", "LISTPAD", "DESCWIN", "ENDWIN"};
    return WID << EnumString[static_cast<WinID>(e)];
};
MenuID&  operator++(MenuID&  MID, int)      {
    return MID = (MID == MenuID::ENDMENU) ? MenuID::MAINMENU : static_cast<MenuID>(static_cast<int>(MID) + 1);
};
MenuID&  operator--(MenuID&  MID, int)      {
    return MID = (MID == MenuID::ENDMENU) ? MenuID::MAINMENU : static_cast<MenuID>(static_cast<int>(MID) - 1);
};
ostream& operator<<(ostream& MID, MenuID e) {
    static const vector<string> EnumString = {"DATEIMENU", "DAEMONMENU", "SYSTEMCTLMENU", "INFOMENU", "MAINMENU", "ENDMENU"};
    return MID << EnumString[static_cast<MenuID>(e)];
};

MenuWinClass::MenuWinClass() {
    START.WinSize.RAND = 1;
    START.WinSize.h = 1; //rand
    START.WinSize.w = 1;
    START.WCX(); // = 80;
    START.HRY(); // = 24;
    START.WinSize.WCX(); // = 80;
    START.WinSize.HRY(); // = 24;
    START.WinSize.WCX_Real();
    START.WinSize.HRY_Real();
    START.WinSize.WCX_Center();
    START.WinSize.HRY_Center();
    START.WinSize.WCX_TmpWin(stdscr);
    START.WinSize.HRY_TmpWin(stdscr);
    START.WinSize.WCX_TmpWinReal(stdscr);
    START.WinSize.HRY_TmpWinReal(stdscr);
    START.WinSize.WCX_TmpWinCenter(stdscr);
    START.WinSize.HRY_TmpWinCenter(stdscr);
}
void MenuWinClass::StartWin() {
    setlocale(LC_CTYPE, "de_DE.UTF-8");
    setlocale(LC_ALL, "de_DE.UTF-8");
    initscr();
    if (has_colors() == FALSE) { endwin(); cout << "Your terminal does not support color\n" << endl; exit(1);}
    start_color();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    MenuWinClass::AppColor();
}
void MenuWinClass::StopWin() {
    endwin();
}
void MenuWinClass::AppColor() {
    start_color();
    short MY_MARIN_BLUE = 240, MY_LIGHT_BLUE = 250, MY_DARK_BLACK = 0, MY_LIGHT_WHITE = 100;
    short R = 0, G = 0, B = 0;
    init_color(MY_MARIN_BLUE, R, G, static_cast<short int>(300));
    init_color(MY_LIGHT_BLUE, R, G, static_cast<short int>(850));
    init_color(MY_DARK_BLACK, R, G, B);
    init_color(MY_LIGHT_WHITE, 1000, 1000, 1000);
    /* 0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 magenta, 6 cyan, 7 white, 8 marin blue, 9 light blue */
    /* hintergrund Schwarz */
    init_pair(00, MY_DARK_BLACK,  MY_DARK_BLACK);
    init_pair(10, COLOR_RED,      MY_DARK_BLACK);
    init_pair(20, COLOR_GREEN,    MY_DARK_BLACK);
    init_pair(30, COLOR_YELLOW,   MY_DARK_BLACK);
    init_pair(40, COLOR_BLUE,     MY_DARK_BLACK);
    init_pair(50, COLOR_MAGENTA,  MY_DARK_BLACK);
    init_pair(60, COLOR_CYAN,     MY_DARK_BLACK);
    init_pair(70, MY_LIGHT_WHITE, MY_DARK_BLACK);
    init_pair(80, MY_MARIN_BLUE,  MY_DARK_BLACK);
    init_pair(90, MY_LIGHT_BLUE,  MY_DARK_BLACK);
    /* hintergrund Rot */
    init_pair(01, MY_DARK_BLACK,  COLOR_RED);
    init_pair(11, COLOR_RED,      COLOR_RED);
    init_pair(21, COLOR_GREEN,    COLOR_RED);
    init_pair(31, COLOR_YELLOW,   COLOR_RED);
    init_pair(41, COLOR_BLUE,     COLOR_RED);
    init_pair(51, COLOR_MAGENTA,  COLOR_RED);
    init_pair(61, COLOR_CYAN,     COLOR_RED);
    init_pair(71, MY_LIGHT_WHITE, COLOR_RED);
    init_pair(81, MY_MARIN_BLUE,  COLOR_RED);
    init_pair(91, MY_LIGHT_BLUE,  COLOR_RED);
    /* hintergrund Gruen */
    init_pair(02, MY_DARK_BLACK,  COLOR_GREEN);
    init_pair(12, COLOR_RED,      COLOR_GREEN);
    init_pair(22, COLOR_GREEN,    COLOR_GREEN);
    init_pair(32, COLOR_YELLOW,   COLOR_GREEN);
    init_pair(42, COLOR_BLUE,     COLOR_GREEN);
    init_pair(52, COLOR_MAGENTA,  COLOR_GREEN);
    init_pair(62, COLOR_CYAN,     COLOR_GREEN);
    init_pair(72, MY_LIGHT_WHITE, COLOR_GREEN);
    init_pair(82, MY_MARIN_BLUE,  COLOR_GREEN);
    init_pair(92, MY_LIGHT_BLUE,  COLOR_GREEN);
    /* hintergrund Gelb */
    init_pair(03, MY_DARK_BLACK,  COLOR_YELLOW);
    init_pair(13, COLOR_RED,      COLOR_YELLOW);
    init_pair(23, COLOR_GREEN,    COLOR_YELLOW);
    init_pair(33, COLOR_YELLOW,   COLOR_YELLOW);
    init_pair(43, COLOR_BLUE,     COLOR_YELLOW);
    init_pair(53, COLOR_MAGENTA,  COLOR_YELLOW);
    init_pair(63, COLOR_CYAN,     COLOR_YELLOW);
    init_pair(73, MY_LIGHT_WHITE, COLOR_YELLOW);
    init_pair(83, MY_MARIN_BLUE,  COLOR_YELLOW);
    init_pair(93, MY_LIGHT_BLUE,  COLOR_YELLOW);
    /* hintergrund Blau */
    init_pair(04, MY_DARK_BLACK,  COLOR_BLUE);
    init_pair(14, COLOR_RED,      COLOR_BLUE);
    init_pair(24, COLOR_GREEN,    COLOR_BLUE);
    init_pair(34, COLOR_YELLOW,   COLOR_BLUE);
    init_pair(44, COLOR_BLUE,     COLOR_BLUE);
    init_pair(54, COLOR_MAGENTA,  COLOR_BLUE);
    init_pair(64, COLOR_CYAN,     COLOR_BLUE);
    init_pair(74, MY_LIGHT_WHITE, COLOR_BLUE);
    init_pair(84, MY_MARIN_BLUE,  COLOR_BLUE);
    /* hintergrund Magenta */
    init_pair(05, MY_DARK_BLACK,  COLOR_MAGENTA);
    init_pair(15, COLOR_RED,      COLOR_MAGENTA);
    init_pair(25, COLOR_GREEN,    COLOR_MAGENTA);
    init_pair(35, COLOR_YELLOW,   COLOR_MAGENTA);
    init_pair(45, COLOR_BLUE,     COLOR_MAGENTA);
    init_pair(55, COLOR_MAGENTA,  COLOR_MAGENTA);
    init_pair(65, COLOR_CYAN,     COLOR_MAGENTA);
    init_pair(75, MY_LIGHT_WHITE, COLOR_MAGENTA);
    /* hintergrund Cyan */
    init_pair(06, MY_DARK_BLACK,  COLOR_CYAN);
    init_pair(16, COLOR_RED,      COLOR_CYAN);
    init_pair(26, COLOR_GREEN,    COLOR_CYAN);
    init_pair(36, COLOR_YELLOW,   COLOR_CYAN);
    init_pair(46, COLOR_BLUE,     COLOR_CYAN);
    init_pair(56, COLOR_MAGENTA,  COLOR_CYAN);
    init_pair(66, COLOR_CYAN,     COLOR_CYAN);
    init_pair(76, MY_LIGHT_WHITE, COLOR_CYAN);
    init_pair(86, MY_MARIN_BLUE,  COLOR_CYAN);
    init_pair(96, MY_LIGHT_BLUE,  COLOR_CYAN);
    /* hintergrund White */
    init_pair(07, MY_DARK_BLACK,  MY_LIGHT_WHITE);
    init_pair(17, COLOR_RED,      MY_LIGHT_WHITE);
    init_pair(27, COLOR_GREEN,    MY_LIGHT_WHITE);
    init_pair(37, COLOR_YELLOW,   MY_LIGHT_WHITE);
    init_pair(47, COLOR_BLUE,     MY_LIGHT_WHITE);
    init_pair(57, COLOR_MAGENTA,  MY_LIGHT_WHITE);
    init_pair(67, COLOR_CYAN,     MY_LIGHT_WHITE);
    init_pair(77, MY_LIGHT_WHITE, MY_LIGHT_WHITE);
    init_pair(87, MY_MARIN_BLUE,  MY_LIGHT_WHITE);
    init_pair(97, MY_LIGHT_BLUE,  MY_LIGHT_WHITE);
    /* hintergrund Marin Blau */
    init_pair(8,  MY_DARK_BLACK,  MY_MARIN_BLUE);
    init_pair(18, COLOR_RED,      MY_MARIN_BLUE);
    init_pair(28, COLOR_GREEN,    MY_MARIN_BLUE);
    init_pair(38, COLOR_YELLOW,   MY_MARIN_BLUE);
    init_pair(48, COLOR_BLUE,     MY_MARIN_BLUE);
    init_pair(58, COLOR_MAGENTA,  MY_MARIN_BLUE);
    init_pair(68, COLOR_CYAN,     MY_MARIN_BLUE);
    init_pair(78, MY_LIGHT_WHITE, MY_MARIN_BLUE);
    init_pair(88, MY_MARIN_BLUE,  MY_MARIN_BLUE);
    init_pair(98, MY_LIGHT_BLUE,  MY_MARIN_BLUE);
    /* hintergrund Light Blue */
    init_pair(9,  MY_DARK_BLACK,  MY_LIGHT_BLUE);
    init_pair(19, COLOR_RED,      MY_LIGHT_BLUE);
    init_pair(29, COLOR_GREEN,    MY_LIGHT_BLUE);
    init_pair(39, COLOR_YELLOW,   MY_LIGHT_BLUE);
    init_pair(49, COLOR_BLUE,     MY_LIGHT_BLUE);
    init_pair(59, COLOR_MAGENTA,  MY_LIGHT_BLUE);
    init_pair(69, COLOR_CYAN,     MY_LIGHT_BLUE);
    init_pair(79, MY_LIGHT_WHITE, MY_LIGHT_BLUE);
    init_pair(89, MY_MARIN_BLUE,  MY_LIGHT_BLUE);
    init_pair(99, MY_LIGHT_BLUE,  MY_LIGHT_BLUE);
} /*---------Programm_Farben------------------------*/
void MenuWinClass::SetWinSize() {
    MenuWinClass::START.WCX();
    MenuWinClass::START.HRY();
    MenuWinClass::START.HRYw1();
    MenuWinClass::START.WCXw1();
    MenuWinClass::START.HRYw2();
    MenuWinClass::START.WCXw2();
    MenuWinClass::START.HRYw3();
    MenuWinClass::START.WCXw3();
    MenuWinClass::START.HRYw4();
    MenuWinClass::START.WCXw4();
    MenuWinClass::START.HRYw5();
    MenuWinClass::START.WCXw5();
    MenuWinClass::START.HRYtime();
    MenuWinClass::START.WCXtime();
    MenuWinClass::START.TMPWin1 = newwin(MenuWinClass::START.HRYw1(), MenuWinClass::START.WCXw1(), 0, 0);
    MenuWinClass::START.TMPWin2 = newwin(MenuWinClass::START.HRYw2(), MenuWinClass::START.WCXw2(), 1, 0);
    MenuWinClass::START.TMPWin3 = newwin(MenuWinClass::START.HRYw3(), MenuWinClass::START.WCXw3(), (MenuWinClass::START.HRYw1() + MenuWinClass::START.HRYw2()), 0);
    MenuWinClass::START.TMPWin4 = newpad(MenuWinClass::START.HRYw4(), MenuWinClass::START.WCXw4());
    //MenuWinClass::START.TMPWin5 = newpad(MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5());
    MenuWinClass::START.TMPWin5 = newwin(MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5(), (MenuWinClass::START.HRYw1() + MenuWinClass::START.HRYw2())+ 1, 33);
} /*---------Fenster_Size_Setzen--------------------*/
void MenuWinClass::CreateWin(WINDOW* win, WinID WID) {
    switch (WID) {
    case MENUWIN: { /*TMPWin1*/
        MenuWinClass::Hauptmenu();
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_MENUWIN));
        break;
    }
    case MAINWIN: { /*TMPWin2*/
        box(win, 0, 0);
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_MAINWIN));
        wsetscrreg(win, 0, MenuWinClass::START.HRYw2() - 2);
        scrollok(win, true);
        break;
    }
    case INFOWIN: { /*TMPWin3*/
        box(win, 0, 0);
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_INFOWIN));
        wattr_on(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_INFOWIN) | A_BOLD, nullptr);
        mvwaddnstr(win, MenuWinClass::START.HRYw3() -1, MenuWinClass::START.WCXw3() - 14, "[ EXIT F10 ]", -1); //12+2
        mvwaddnstr(win, MenuWinClass::START.HRYw3() -1, MenuWinClass::START.WCXw3() - 26, "[ MENÜ TAB ]", -1); //11+2
        wattr_off(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_INFOWIN) | A_BOLD, nullptr);
        break;
    }
    case LISTPAD: { /*TMPWin4*/
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_LISTPAD));
        win = derwin(MenuWinClass::START.TMPWin2, MenuWinClass::START.HRYw4(), MenuWinClass::START.WCXw4(), 1, 1);
        break;
    }
    case DESCWIN: { /*TMPWin5*/
        //win = derwin(MenuWinClass::START.TMPWin3, MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5(), 1, 33);
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_DESCWIN));
        break;
    }
    case TIMEWIN: { /*TimeWin*/
        wbkgd(win, COLOR_PAIR(MenuWinClass::START.WinColor.BK_TIMEWIN));
        win = derwin(MenuWinClass::START.TMPWin1, 1, 20, 0, MenuWinClass::START.WCX() - 20);
        break;
    }
    case ENDWIN: { break; }
    default: { break; }
    }
    refresh();
    wrefresh(win);
} /*---------Fenster_Erzeugen-----------------------*/
void MenuWinClass::ResizeHandler(int signal) {
    UNUSED(signal);
    StopWin();
    StartWin();
    SetWinSize();
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin1, MENUWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin2, MAINWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin3, INFOWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin4, LISTPAD);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin5, DESCWIN);
} /*---------Resize_Fenster_neu_Erzeugen----------------*/
void MenuWinClass::ScrollPad(WINDOW* SubWin, int StartY, int StartX, int Height, int Width, int PadHeight) {
    int Choice = 0, Key = 0;
    keypad(SubWin, true);
    refresh();
    int cols = 0;
    while (Choice == 0) {
        prefresh(SubWin, cols, 0, StartY, StartX, Height, Width);
        Key = wgetch(SubWin);
        switch (Key) {
        case KEY_UP: {
            if (cols <= 0) { continue; }
            cols--;
            break;
        }
        case KEY_DOWN: {
            if (cols + Height + 1 >= PadHeight) { continue; }
            cols++;
            break;
        }
        case KEY_PPAGE: { /* Page Up */
            if (cols <= 0) { continue; }
            cols -= Height;
            if (cols < 0) { cols = 0; }
            break;
        }
        case KEY_NPAGE: { /* Page Down */
            if (cols + Height + 1 >= PadHeight) { continue; }
            cols += Height;
            if (cols + Height + 1 > PadHeight) { cols = PadHeight - Height - 1; }
            break;
        }
        case KEY_HOME: {
            cols = 0;
            break;
        }
        case KEY_END: {
            cols = PadHeight - Height - 1;
            break;
        }
        case 10: { /* Enter */
            Choice = 1;
            break;
        }
        }
        refresh();
    }
    delwin(SubWin);
}
void MenuWinClass::printInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color, char *sp) {
    int x, y;
    unsigned long length;
    float temp;

    if(win == nullptr)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - static_cast<int>(length))/ 2;
    x = startx + static_cast<int>(temp);
    wattron(win, color);

    if (sp) {
        for (int i = startx; i < width; i++) {
            mvwprintw(win, y, i, "%c", sp);
        }
    }

    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
}
void MenuWinClass::FensterDraw() {
    ServiceClass_MWC->INFOWINDOW("");
    ServiceClass_MWC->ServiceListFill();
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin1, MENUWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin2, MAINWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin3, INFOWIN);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin4, LISTPAD);
    MenuWinClass::CreateWin(MenuWinClass::START.TMPWin5, DESCWIN);
}
void MenuWinClass::Hauptmenu(void) {
    MenuWinClass::TOPMENU.MID = MAINMENU;
    MenuWinClass::TOPMENU.HMName = string("HAUPTMENÜ");
    MenuWinClass::TOPMENU.HMItem = static_cast<ITEM**>(calloc(5, sizeof(ITEM*)));
    MenuWinClass::TOPMENU.HMItem[0] = new_item(" Datei", MenuWinClass::TOPMENU.HMName.c_str());
    MenuWinClass::TOPMENU.HMItem[1] = new_item("DaemonType", MenuWinClass::TOPMENU.HMName.c_str());
    MenuWinClass::TOPMENU.HMItem[2] = new_item("Systemctl", MenuWinClass::TOPMENU.HMName.c_str());
    MenuWinClass::TOPMENU.HMItem[3] = new_item("Info", MenuWinClass::TOPMENU.HMName.c_str());
    MenuWinClass::TOPMENU.HMItem[4] = nullptr;
    MenuWinClass::TOPMENU.HMMenu = new_menu(MenuWinClass::TOPMENU.HMItem);
    MenuWinClass::START.TMPWin1 = newwin(MenuWinClass::START.HRYw1(), MenuWinClass::START.WCXw1(), 0, 0);
    set_menu_win(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::START.TMPWin1);
    set_menu_sub(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::START.TMPWin1);
    //###############################################################
    //set_menu_sub(TOPMENU.UME.UMEMenu, MenuWinClass::START.TMPWin1);
    //###############################################################
    set_menu_spacing(MenuWinClass::TOPMENU.HMMenu, 1, 0, 0);
    set_menu_format(MenuWinClass::TOPMENU.HMMenu, 0, 5);
    menu_opts_off(MenuWinClass::TOPMENU.HMMenu, O_SHOWDESC);
    menu_opts_off(MenuWinClass::TOPMENU.HMMenu, O_NONCYCLIC);
    wbkgd(MenuWinClass::START.TMPWin1, COLOR_PAIR(MenuWinClass::TOPMENU.MenuColor.BK_MAINMENU));
    set_menu_fore(MenuWinClass::TOPMENU.HMMenu, COLOR_PAIR(MenuWinClass::TOPMENU.MenuColor.BK_AKTIVHAME) | A_BOLD);
    set_menu_back(MenuWinClass::TOPMENU.HMMenu, COLOR_PAIR(MenuWinClass::TOPMENU.MenuColor.BK_MAINMENU));
    set_menu_grey(MenuWinClass::TOPMENU.HMMenu, COLOR_PAIR(MenuWinClass::TOPMENU.MenuColor.BK_UNUSEDHM));
    set_menu_mark(MenuWinClass::TOPMENU.HMMenu, "");
    post_menu(MenuWinClass::TOPMENU.HMMenu);
} /* Hauptmenü */
void MenuWinClass::DateiMenu(void) {
    TOPMENU.UME.UMID = 1;
    TOPMENU.UME.UMEName = string("Datei");
    TOPMENU.UME.UMEWin = newwin(6, 15, 1, 0);
    wbkgd(TOPMENU.UME.UMEWin, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    box(TOPMENU.UME.UMEWin, 0, 0);
    TOPMENU.UME.UMEItem = static_cast<ITEM**>(calloc(7, sizeof(ITEM*)));
    TOPMENU.UME.UMEItem[0] = new_item("Man Systemctl", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[1] = new_item("Einstellung", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[2] = new_item("Remotectl", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[3] = new_item("Beenden", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[4] = nullptr;
    TOPMENU.UME.UMEMenu = new_menu(TOPMENU.UME.UMEItem);
    set_menu_win(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEWin);
    set_menu_sub(TOPMENU.UME.UMEMenu, derwin(TOPMENU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(TOPMENU.UME.UMEMenu, 0, 0, 0);
    set_menu_format(TOPMENU.UME.UMEMenu, 5, 0);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_NONCYCLIC);
    set_menu_fore(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_AKTIVUNME)|A_REVERSE|A_BOLD);
    set_menu_back(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_grey(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNUSEDUM)|A_BOLD);
    set_menu_mark(TOPMENU.UME.UMEMenu, "");
    set_current_item(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEItem[0]);
    post_menu(TOPMENU.UME.UMEMenu);
} /* Datei Untermenü */
void MenuWinClass::DaemonTypeMenu(void) {
    TOPMENU.UME.UMID = 2;
    TOPMENU.UME.UMEName = string("DaemonType");
    TOPMENU.UME.UMEWin = newwin(12, 10, 1, 11);
    box(TOPMENU.UME.UMEWin, 0, 0);
    TOPMENU.UME.UMEItem = static_cast<ITEM**>(calloc(11, sizeof(ITEM*)));
    TOPMENU.UME.UMEItem[0] = new_item("Device", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[1] = new_item("Mount", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[2] = new_item("Path", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[3] = new_item("Service", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[4] = new_item("Scope", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[5] = new_item("Slice", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[6] = new_item("Socket", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[7] = new_item("Swap", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[8] = new_item("Target", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[9] = new_item("Timer", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[10] = nullptr;
    TOPMENU.UME.UMEMenu = new_menu(TOPMENU.UME.UMEItem);
    set_menu_win(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEWin);
    set_menu_sub(TOPMENU.UME.UMEMenu, derwin(TOPMENU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(TOPMENU.UME.UMEMenu, 0, 0, 1);
    set_menu_format(TOPMENU.UME.UMEMenu, 11, 0);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_NONCYCLIC);
    wbkgd(TOPMENU.UME.UMEWin, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_fore(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_AKTIVUNME)|A_REVERSE|A_BOLD);
    set_menu_back(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_grey(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNUSEDUM)|A_BOLD);
    set_menu_mark(TOPMENU.UME.UMEMenu, "");
    set_current_item(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEItem[0]);
    post_menu(TOPMENU.UME.UMEMenu);
} /* DaemonType Untermenü */
void MenuWinClass::SystemctlMenu(void) {
    TOPMENU.UME.UMID = 3;
    TOPMENU.UME.UMEName = string("Systemctl");
    TOPMENU.UME.UMEWin = newwin(12, 18, 1, 22);
    box(TOPMENU.UME.UMEWin, 0, 0);
    TOPMENU.UME.UMEItem = static_cast<ITEM**>(calloc(11, sizeof(ITEM*)));
    TOPMENU.UME.UMEItem[0] = new_item("START", "F1");
    TOPMENU.UME.UMEItem[1] = new_item("STOP", "F1");
    TOPMENU.UME.UMEItem[2] = new_item("STATUS", "F3");
    TOPMENU.UME.UMEItem[3] = new_item("ENABLE", "F2");
    TOPMENU.UME.UMEItem[4] = new_item("DISABLE", "F2");
    TOPMENU.UME.UMEItem[5] = new_item("MASK", "F4");
    TOPMENU.UME.UMEItem[6] = new_item("UNMASK", "F4");
    TOPMENU.UME.UMEItem[7] = new_item("RESTART", "F5");
    TOPMENU.UME.UMEItem[8] = new_item("RELOAD", "F6");
    TOPMENU.UME.UMEItem[9] = new_item("Reload-daemon", "F7");
    TOPMENU.UME.UMEItem[10] = nullptr;
    TOPMENU.UME.UMEMenu = new_menu(TOPMENU.UME.UMEItem);
    set_menu_win(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEWin);
    set_menu_sub(TOPMENU.UME.UMEMenu, derwin(TOPMENU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(TOPMENU.UME.UMEMenu, 1, 0, 0);
    set_menu_format(TOPMENU.UME.UMEMenu, 11, 0);
    menu_opts_on(TOPMENU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_NONCYCLIC);
    wbkgd(TOPMENU.UME.UMEWin, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_fore(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_AKTIVUNME)|A_REVERSE|A_BOLD);
    set_menu_back(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_grey(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNUSEDUM)|A_BOLD);
    set_menu_mark(TOPMENU.UME.UMEMenu, "");
    set_current_item(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEItem[0]);
    post_menu(TOPMENU.UME.UMEMenu);
} /* Systemctl Untermenü */
void MenuWinClass::InfoMenu(void) {
    TOPMENU.UME.UMID = 4;
    TOPMENU.UME.UMEName = string("Info");
    TOPMENU.UME.UMEWin = newwin(5, 12, 1, 33);
    wbkgd(TOPMENU.UME.UMEWin, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    box(TOPMENU.UME.UMEWin, 0, 0);
    TOPMENU.UME.UMEItem = static_cast<ITEM**>(calloc(4, sizeof(ITEM*)));
    TOPMENU.UME.UMEItem[0] = new_item("journalctl", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[1] = new_item("E-Mail", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[2] = new_item("Beenden", TOPMENU.UME.UMEName.c_str());
    TOPMENU.UME.UMEItem[3] = nullptr;
    TOPMENU.UME.UMEMenu = new_menu(TOPMENU.UME.UMEItem);
    set_menu_win(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEWin);
    set_menu_sub(TOPMENU.UME.UMEMenu, derwin(TOPMENU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(TOPMENU.UME.UMEMenu, 0, 0, 0);
    set_menu_format(TOPMENU.UME.UMEMenu, 5, 0);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(TOPMENU.UME.UMEMenu, O_NONCYCLIC);
    set_menu_fore(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_AKTIVUNME)|A_REVERSE|A_BOLD);
    set_menu_back(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNTERMENU));
    set_menu_grey(TOPMENU.UME.UMEMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNUSEDUM)|A_BOLD);
    set_menu_mark(TOPMENU.UME.UMEMenu, "");
    set_current_item(TOPMENU.UME.UMEMenu, TOPMENU.UME.UMEItem[0]);
    post_menu(TOPMENU.UME.UMEMenu);
} /* Info Untermenü */
WINDOW* MenuWinClass::TempWin(string Name, MenuID MID) {
    if ((Name.compare(" Datei") == 0) || (MID == DATEIMENU)) {
        //MenuWinClass::CreateMenu(MenuWinClass::TOPMENU.UME.UMEWin, MenuWinClass::TOPMENU.UME.UMEMenu, DATEIMENU, "DATEIMENU");
        MenuWinClass::DateiMenu();
        MenuWinClass::TMPWIN = MenuWinClass::TOPMENU.UME.UMEWin;
        MenuWinClass::TMPMENU = MenuWinClass::TOPMENU.UME.UMEMenu;
    } else if ((Name.compare("DaemonType") == 0) || (MID == DAEMONMENU)) {
        //MenuWinClass::CreateMenu(MenuWinClass::TOPMENU.UME.UMEWin, MenuWinClass::TOPMENU.UME.UMEMenu, SYSTEMMENU, "SYSTEMMENU");
        MenuWinClass::DaemonTypeMenu();
        MenuWinClass::TMPWIN = MenuWinClass::TOPMENU.UME.UMEWin;
        MenuWinClass::TMPMENU = MenuWinClass::TOPMENU.UME.UMEMenu;
    } else if ((Name.compare("Systemctl") == 0) || (MID == SYSTEMCTLMENU)) {
        //MenuWinClass::CreateMenu(MenuWinClass::TOPMENU.UME.UMEWin, MenuWinClass::TOPMENU.UME.UMEMenu, SERVERMENU, "SERVERMENU");
        MenuWinClass::SystemctlMenu();
        MenuWinClass::TMPWIN = MenuWinClass::TOPMENU.UME.UMEWin;
        MenuWinClass::TMPMENU = MenuWinClass::TOPMENU.UME.UMEMenu;
    } else if ((Name.compare("Info") == 0) || (MID == INFOMENU)) {
        //MenuWinClass::CreateMenu(MenuWinClass::TOPMENU.UME.UMEWin, MenuWinClass::TOPMENU.UME.UMEMenu, SOFTWAREMENU, "SOFTWAREMENU");
        MenuWinClass::InfoMenu();
        MenuWinClass::TMPWIN = MenuWinClass::TOPMENU.UME.UMEWin;
        MenuWinClass::TMPMENU = MenuWinClass::TOPMENU.UME.UMEMenu;
    }
    return MenuWinClass::TMPWIN;
} /* Menü und Win Neuzuordnen */
void MenuWinClass::StartMenuAuswahl(string wahl) {
    string menupoint = MenuWinClass::SERVICEMENU.AktivName;
    string befehl;
    if (wahl.compare(" Datei") == 0) {
        DateiMenu();
    } else if (wahl.compare("Systemctl") == 0) {
        SystemctlMenu();
    } else if (wahl.compare("DaemonType") == 0) {
        DaemonTypeMenu();
    } else if (wahl.compare("Systemctl") == 0) {
        InfoMenu();
    } else if (wahl.compare("Service") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "service";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Swap") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "swap";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Timer") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "timer";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Device") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "device";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Mount") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "mount";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Path") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "path";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Target") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "target";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Socket") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "socket";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Slice") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "slice";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Scope") == 0) {
        ServiceClass_MWC->start = 0;
        ServiceClass_MWC->selected = 0;
        ServiceClass_MWC->systemctlwahl = "scope";
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("Man Page") == 0) {
        exit(EXIT_SUCCESS);
        //DATEIMANPAGE::Start_ManP();
    } else if (wahl.compare("Befehle") == 0) {
        exit(EXIT_SUCCESS);
        //DATEIBEFEHLE::befehle_main();
    } else if (wahl.compare("Einstellung") == 0) {
        exit(EXIT_SUCCESS);
        //einDa();
    } else if (wahl.compare("Beenden") == 0) {
        exit(EXIT_SUCCESS);
    } else if (wahl.compare("START") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl start " + menupoint + " --now";
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("STOP") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl stop " + menupoint + " --now";
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("RELOAD") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl reload " + menupoint + " --now";
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("RESTART") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl restart " + menupoint + " --now";
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("ENABLE") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl enable " + menupoint;
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("DISABLE") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl disable " + menupoint;
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("STATUS") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl status " + menupoint;
        ServiceClass_MWC->Statusabfrage(TaskClass_MWC->TERM_AUSGABE(befehl));
    } else if (wahl.compare("UNMASK") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl unmask " + menupoint;
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("MASK") == 0) {
        pos_menu_cursor(MenuWinClass::SERVICEMENU.LMenu);
        befehl = "systemctl mask " + menupoint;
        TaskClass_MWC->TERM_AUSGABE(befehl);
        ServiceClass_MWC->ServiceListFill();
    } else if (wahl.compare("journalctl") == 0) {
        befehl = "journalctl -b -u " + menupoint;
        ServiceClass_MWC->Statusabfrage(TaskClass_MWC->TERM_AUSGABE(befehl));
    }
} /* MenüPoint to command */
void MenuWinClass::RefreshWindows(){
    refresh();
    wrefresh(MenuWinClass::START.TMPWin1);
    redrawwin(MenuWinClass::START.TMPWin2);
    wrefresh(MenuWinClass::START.TMPWin2);
    touchwin(MenuWinClass::START.TMPWin2);
    redrawwin(MenuWinClass::START.TMPWin3);
    wrefresh(MenuWinClass::START.TMPWin3);
    touchwin(MenuWinClass::START.TMPWin3);
    prefresh(MenuWinClass::START.TMPWin4, 0, 0, 2, 1, MenuWinClass::START.HRYw4() + 1, MenuWinClass::START.WCXw4());
    //prefresh(MenuWinClass::START.TMPWin5, 0, 0, MenuWinClass::START.HRY()-4,
    //         MenuWinClass::START.WCX()-46, MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5());
    wrefresh(MenuWinClass::START.TMPWin5);
}

int MenuWinClass::MenuStart(int Key) {
//try {
        set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[MenuWinClass::MeInAl]);
        TMPWIN = TempWin(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)), (MenuID)item_index(current_item(MenuWinClass::TOPMENU.HMMenu)));
        string tmpMeNa = string(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)));
        string MeAuWa = "";
        ServiceClass_MWC->TableMoveRow();
        while ((Key = wgetch(stdscr)) != KEY_F(10)) {
            switch (MenuWinClass::TabKey) {
            case 1: {
                switch (Key) {
                case '?': { ServiceClass_MWC->Statusabfrage(ABOUT_INFO); break; }
                case 27: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(1, "++", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case KEY_DOWN: {
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_DOWN_ITEM);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case KEY_UP: {
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_UP_ITEM);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case KEY_NPAGE: {
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_SCR_DPAGE);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case KEY_PPAGE: {
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_SCR_UPAGE);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case KEY_END: {
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_LAST_ITEM);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case KEY_HOME: {
                    ServiceClass_MWC->start = 0;
                    ServiceClass_MWC->selected = 0;
                    ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_FIRST_ITEM);
                    ServiceClass_MWC->TableMoveRow();
                    break;
                }
                case 0x09: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(1, "++", 3);
                    TMPWIN = TempWin("Datei", DATEIMENU);
                    redrawwin(MenuWinClass::TOPMENU.UME.UMEWin);
                    wrefresh(MenuWinClass::TOPMENU.UME.UMEWin);
                    break;
                }
                case KEY_BTAB: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(1, "--", 3);
                    TMPWIN = TempWin("Datei", DATEIMENU);
                    redrawwin(MenuWinClass::TOPMENU.UME.UMEWin);
                    wrefresh(MenuWinClass::TOPMENU.UME.UMEWin);
                    break;
                }
                case KEY_BACKSPACE: { ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_BACK_PATTERN); break; }
                case 10: {
                    string menupoint = MenuWinClass::SERVICEMENU.AktivName;
                    string befehl = "systemctl status " + menupoint;
                    ServiceClass_MWC->Statusabfrage(TaskClass_MWC->TERM_AUSGABE(befehl));
                    break; }
                case 32: { ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_TOGGLE_ITEM); break; }
                default: { if (Key > 10 && Key < 128) {
                        //ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_NEXT_MATCH);
                    }
                break;}
                }
                if (MenuWinClass_MWC->TabKey == 1) {
                    curs_set(false);
                    ServiceClass_MWC->INFOWINDOW(MenuWinClass::SERVICEMENU.AktivName);
                    MenuWinClass::TOPMENU.LoescheUME();
                    MenuWinClass::RefreshWindows();
                } else if (MenuWinClass_MWC->TabKey == 2) {
                    curs_set(false);
                    MenuWinClass::RefreshWindows();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    redrawwin(MenuWinClass::TOPMENU.UME.UMEWin);
                    wrefresh(MenuWinClass::TOPMENU.UME.UMEWin);
                } else if (MenuWinClass_MWC->TabKey == 3) {
                    curs_set(true);
                    mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass::PATTERN.c_str(), -1);
                    MenuWinClass::RefreshWindows();
                }
                break;
            } /* MainWindow ListMenu */
            case 2: {
                switch (Key) {
                case '?': { ServiceClass_MWC->Statusabfrage(ABOUT_INFO); break; }
                case 27: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(2, "++", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case KEY_DOWN: { menu_driver(TOPMENU.UME.UMEMenu, REQ_DOWN_ITEM); break; }
                case KEY_UP: { menu_driver(TOPMENU.UME.UMEMenu, REQ_UP_ITEM); break; }
                case KEY_RIGHT: {
                    MenuWinClass::TOPMENU.LoescheUME();
                    menu_driver(MenuWinClass::TOPMENU.HMMenu, REQ_RIGHT_ITEM);
                    tmpMeNa = string(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)));
                    TMPWIN = TempWin(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)), (MenuID)item_index(current_item(MenuWinClass::TOPMENU.HMMenu)));
                    break;
                }
                case KEY_LEFT: {
                    MenuWinClass::TOPMENU.LoescheUME(); // delete before menu drive
                    menu_driver(MenuWinClass::TOPMENU.HMMenu, REQ_LEFT_ITEM);
                    tmpMeNa = string(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)));
                    TMPWIN = TempWin(item_name(current_item(MenuWinClass::TOPMENU.HMMenu)), (MenuID)item_index(current_item(MenuWinClass::TOPMENU.HMMenu)));
                    break;
                }
                case 0x09: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(2, "++", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case KEY_BTAB: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(2, "--", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case 10: {
                    MenuWinClass::MeInAl = item_index(current_item(MenuWinClass::TOPMENU.HMMenu));
                    StartMenuAuswahl(item_name(current_item(MenuWinClass::TOPMENU.UME.UMEMenu)));
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(2, "++", 2);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break; }
                }
                if (MenuWinClass_MWC->TabKey == 1) {
                    curs_set(false);
                    ServiceClass_MWC->INFOWINDOW(MenuWinClass::SERVICEMENU.AktivName);
                    MenuWinClass::TOPMENU.LoescheUME();
                    MenuWinClass::RefreshWindows();
                } else if (MenuWinClass_MWC->TabKey == 2) {
                    curs_set(false);
                    MenuWinClass::RefreshWindows();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    redrawwin(MenuWinClass::TOPMENU.UME.UMEWin);
                    wrefresh(MenuWinClass::TOPMENU.UME.UMEWin);
                } else if (MenuWinClass_MWC->TabKey == 3) {
                    curs_set(true);
                    mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass::PATTERN.c_str(), -1);
                    MenuWinClass::RefreshWindows();
                }
                break;
            } /* Hauptmenu */
            case 3:{
                int y,x;
                getyx(MenuWinClass::START.TMPWin3, y, x);
                int curposi = (x - 33);
                switch (Key) {
                case '?':{ ServiceClass_MWC->Statusabfrage(ABOUT_INFO); break; }
                case 27:{ break; }
                case 127:
                case KEY_BACKSPACE:{
                    MenuWinClass::PATTERN = ServiceClass_MWC->SearchDriver(REQ_DEL_BACKSPACE, MenuWinClass::START.TMPWin3, Key, MenuWinClass::PATTERN, curposi);
                    break; }
                case KEY_DC:{
                    MenuWinClass::PATTERN = ServiceClass_MWC->SearchDriver(REQ_DEL_DC, MenuWinClass::START.TMPWin3, Key, MenuWinClass::PATTERN, curposi);
                    break; }
                case KEY_RIGHT:{
                    MenuWinClass::PATTERN = ServiceClass_MWC->SearchDriver(REQ_RIGHT, MenuWinClass::START.TMPWin3, Key, MenuWinClass::PATTERN, curposi);
                    break; }
                case KEY_LEFT:{
                    MenuWinClass::PATTERN = ServiceClass_MWC->SearchDriver(REQ_LEFT, MenuWinClass::START.TMPWin3, Key, MenuWinClass::PATTERN, curposi);
                    break; }
                case 0x09: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(3, "++", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case KEY_BTAB: {
                    MenuWinClass_MWC->TabKey = TaskClass_MWC->ZahlenWerk(3, "--", 3);
                    set_current_item(MenuWinClass::TOPMENU.HMMenu, MenuWinClass::TOPMENU.HMItem[0]);
                    MenuWinClass::TOPMENU.LoescheUME();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    break;
                }
                case KEY_ENTER:
                case 10:{ break; }
                default:{
                    if (Key > 10 && Key < 128) {
                        MenuWinClass::PATTERN = ServiceClass_MWC->SearchDriver(REQ_INS_DEFAULT, MenuWinClass::START.TMPWin3, Key, MenuWinClass::PATTERN, curposi);
                        //ServiceClass_MWC->TableDriver(ServiceClass_MWC->ServiceList, REQ_NEXT_MATCH);
                    }
                    break; }
                }
                if (MenuWinClass_MWC->TabKey == 1) {
                    curs_set(false);
                    ServiceClass_MWC->INFOWINDOW(MenuWinClass::SERVICEMENU.AktivName);
                    MenuWinClass::TOPMENU.LoescheUME();
                    MenuWinClass::RefreshWindows();
                } else if (MenuWinClass_MWC->TabKey == 2) {
                    curs_set(false);
                    MenuWinClass::RefreshWindows();
                    wrefresh(MenuWinClass::START.TMPWin1);
                    redrawwin(MenuWinClass::TOPMENU.UME.UMEWin);
                    wrefresh(MenuWinClass::TOPMENU.UME.UMEWin);
                } else if (MenuWinClass_MWC->TabKey == 3) {
                    curs_set(true);
                    MenuWinClass::RefreshWindows();
                }
                break;
            }/* search at tmpwin3 */
            }
            if (Key == KEY_F(10)) { break; }
        }
    return Key;
//    } catch (const NCursesException* e) { endwin(); std::cerr << e->message << std::endl; cout << e->errorno; return -1;
//    } catch (const NCursesException& e) { endwin(); std::cerr << e.message << std::endl; cout << e.errorno; return -1;
//    } catch (const std::exception& e)   { endwin(); std::cerr << "Exception: " << e.what() << std::endl; cout << EXIT_FAILURE; return -1; }
} /* Menü surf funktion */

MenuWinClass::~MenuWinClass(){
    if (MenuWinClass::START.TMPWin1) {werase(MenuWinClass::START.TMPWin1); delwin(MenuWinClass::START.TMPWin1); endwin();}
    if (MenuWinClass::START.TMPWin2) {werase(MenuWinClass::START.TMPWin2); delwin(MenuWinClass::START.TMPWin2); endwin();}
    if (MenuWinClass::START.TMPWin3) {werase(MenuWinClass::START.TMPWin3); delwin(MenuWinClass::START.TMPWin3); endwin();}
    if (MenuWinClass::START.TMPWin4) {werase(MenuWinClass::START.TMPWin4); delwin(MenuWinClass::START.TMPWin4); endwin();}
    if (MenuWinClass::START.TMPWin5) {werase(MenuWinClass::START.TMPWin5); delwin(MenuWinClass::START.TMPWin5); endwin();}
}


