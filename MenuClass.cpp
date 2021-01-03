#include <src/ServiceClass.h>
#include <src/MenuClass.h>
#include <src/WinClass.h>
#include <src/TaskClass.h>
#include <src/Info.h>

using namespace std;

extern class TaskClass * TaskPtr;
//extern class MenuClass * MenuPtr;
extern class ServiceClass * ServicePtr;
extern class WinClass * WinPtr;
extern class ServiceTableClass * TablePtr;

void MenuClass::Hauptmenu(void) {
    MENEU.HMID = 0;
    MENEU.HMName = string("HAUPTMENÜ");
    MENEU.HMItem = static_cast<ITEM **>(calloc(5, sizeof(ITEM *)));
    MENEU.HMItem[0] = new_item(" Datei", MENEU.HMName.c_str());
    MENEU.HMItem[1] = new_item("DaemonType", MENEU.HMName.c_str());
    MENEU.HMItem[2] = new_item("Systemctl", MENEU.HMName.c_str());
    MENEU.HMItem[3] = new_item("Info", MENEU.HMName.c_str());
    MENEU.HMItem[4] = nullptr;
    MENEU.HMMenu = new_menu(MENEU.HMItem);
    MENEU.HMWin = newwin(1, WinPtr->WinSize->WCX()-26, 0, 0);
    set_menu_win (MENEU.HMMenu, MENEU.HMWin);
    set_menu_sub(MENEU.HMMenu, MENEU.HMWin);
    //###############################################################
    //set_menu_sub(MENEU.UME.UMEMenu, MENEU.HMWin);
    //###############################################################
    set_menu_spacing(MENEU.HMMenu, 1, 0, 0);
    set_menu_format(MENEU.HMMenu, 0, 5);
    menu_opts_off(MENEU.HMMenu, O_SHOWDESC);
    menu_opts_off(MENEU.HMMenu, O_NONCYCLIC);
    wbkgd(MENEU.HMWin, COLOR_PAIR(HMcolor.HaMeFe_HG)|A_BOLD);
    //set_item_fore(MENEU.HMItem[1], COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(MENEU.HMMenu, COLOR_PAIR(HMcolor.HaMe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(MENEU.HMMenu, COLOR_PAIR(HMcolor.HaMe_HG));//|A_BOLD);
    set_menu_grey(MENEU.HMMenu, COLOR_PAIR(HMcolor.HaMe_grey)|A_BOLD);
    set_menu_mark(MENEU.HMMenu,"");
    post_menu(MENEU.HMMenu);
} /* Hauptmenü */

void MenuClass::Datei_menu(void) {
    MENEU.UME.UMID = 1;
    MENEU.UME.UMEName = string("Datei");
    MENEU.UME.UMEWin = newwin(6, 15, 1, 0);
    wbkgd(MENEU.UME.UMEWin,COLOR_PAIR(HMcolor.UMeFe_HG));
    box(MENEU.UME.UMEWin, 0, 0);
    MENEU.UME.UMEItem = static_cast<ITEM **>(calloc(7, sizeof(ITEM *)));
    MENEU.UME.UMEItem[0] = new_item("Man Systemctl", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[1] = new_item("Einstellung", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[2] = new_item("Remotectl", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[3] = new_item("Beenden", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[4] = nullptr;
    MENEU.UME.UMEMenu = new_menu(MENEU.UME.UMEItem);
    set_menu_win(MENEU.UME.UMEMenu, MENEU.UME.UMEWin);
    set_menu_sub (MENEU.UME.UMEMenu, derwin(MENEU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(MENEU.UME.UMEMenu, 0,0,0);
    set_menu_format(MENEU.UME.UMEMenu, 5, 0);
    menu_opts_off(MENEU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(MENEU.UME.UMEMenu, O_NONCYCLIC);
    //set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_HG));//|A_BOLD);
    set_menu_grey(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.HaMe_grey)|A_BOLD);
    set_menu_mark(MENEU.UME.UMEMenu,"");
    set_current_item(MENEU.UME.UMEMenu, MENEU.UME.UMEItem[0]);
    post_menu(MENEU.UME.UMEMenu);
} /* Datei Menü */

void MenuClass::DaemonType_menu(void) {
    MENEU.UME.UMID = 2;
    MENEU.UME.UMEName = string("DaemonType");
    MENEU.UME.UMEWin = newwin(12, 10, 1, 11);
    box(MENEU.UME.UMEWin, 0, 0);
    MENEU.UME.UMEItem = static_cast<ITEM **>(calloc(11, sizeof(ITEM *)));
    MENEU.UME.UMEItem[0] = new_item("Device", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[1] = new_item("Mount", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[2] = new_item("Path", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[3] = new_item("Service", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[4] = new_item("Scope", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[5] = new_item("Slice", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[6] = new_item("Socket", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[7] = new_item("Swap", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[8] = new_item("Target", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[9] = new_item("Timer", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[10] = nullptr;
    MENEU.UME.UMEMenu = new_menu(MENEU.UME.UMEItem);
    set_menu_win (MENEU.UME.UMEMenu, MENEU.UME.UMEWin);
    set_menu_sub(MENEU.UME.UMEMenu, derwin(MENEU.UME.UMEWin,0,0,1,1));
    set_menu_spacing(MENEU.UME.UMEMenu, 0, 0, 1);
    set_menu_format(MENEU.UME.UMEMenu, 11, 0);
    menu_opts_off(MENEU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(MENEU.UME.UMEMenu, O_NONCYCLIC);
    wbkgd(MENEU.UME.UMEWin,COLOR_PAIR(HMcolor.UMeFe_HG));
    set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_HG));//|A_BOLD);
    set_menu_grey(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.HaMe_grey)|A_BOLD);
    set_menu_mark(MENEU.UME.UMEMenu,"");
    set_current_item(MENEU.UME.UMEMenu, MENEU.UME.UMEItem[0]);
    post_menu(MENEU.UME.UMEMenu);

} /* System Untermenü */

void MenuClass::Systemctl_menu(void) {
    MENEU.UME.UMID = 3;
    MENEU.UME.UMEName = string("Systemctl");
    MENEU.UME.UMEWin = newwin(12, 18, 1, 22);
    box(MENEU.UME.UMEWin, 0, 0);
    MENEU.UME.UMEItem = static_cast<ITEM **>(calloc(11, sizeof(ITEM *)));
    MENEU.UME.UMEItem[0] = new_item("START", "F1");
    MENEU.UME.UMEItem[1] = new_item("STOP", "F1");
    MENEU.UME.UMEItem[2] = new_item("STATUS", "F3");
    MENEU.UME.UMEItem[3] = new_item("ENABLE", "F2");
    MENEU.UME.UMEItem[4] = new_item("DISABLE", "F2");
    MENEU.UME.UMEItem[5] = new_item("MASK", "F4");
    MENEU.UME.UMEItem[6] = new_item("UNMASK", "F4");
    MENEU.UME.UMEItem[7] = new_item("RESTART", "F5");
    MENEU.UME.UMEItem[8] = new_item("RELOAD", "F6");
    MENEU.UME.UMEItem[9] = new_item("Reload-daemon", "F7");
    MENEU.UME.UMEItem[10] = nullptr;
    MENEU.UME.UMEMenu = new_menu(MENEU.UME.UMEItem);
    set_menu_win (MENEU.UME.UMEMenu, MENEU.UME.UMEWin);
    set_menu_sub(MENEU.UME.UMEMenu, derwin(MENEU.UME.UMEWin,0,0,1,1));
    set_menu_spacing(MENEU.UME.UMEMenu, 1, 0, 0);
    set_menu_format(MENEU.UME.UMEMenu, 11, 0);
    menu_opts_on(MENEU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(MENEU.UME.UMEMenu, O_NONCYCLIC);
    wbkgd(MENEU.UME.UMEWin,COLOR_PAIR(HMcolor.UMeFe_HG));
    set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_HG));//|A_BOLD);
    set_menu_grey(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.HaMe_grey)|A_BOLD);
    set_menu_mark(MENEU.UME.UMEMenu,"");
    set_current_item(MENEU.UME.UMEMenu, MENEU.UME.UMEItem[0]);
    post_menu(MENEU.UME.UMEMenu);
} /* Server Untermenü */

void MenuClass::Info_menu(void) {
    MENEU.UME.UMID = 4;
    MENEU.UME.UMEName = string("Info");
    MENEU.UME.UMEWin = newwin(5, 12, 1, 33);
    wbkgd(MENEU.UME.UMEWin,COLOR_PAIR(HMcolor.UMeFe_HG));
    box(MENEU.UME.UMEWin,0,0);
    //MENEU.UME.UMEItem = (ITEM **)calloc(4, sizeof(ITEM *));
    MENEU.UME.UMEItem = static_cast<ITEM **>(calloc(4, sizeof(ITEM *)));
    MENEU.UME.UMEItem[0] = new_item("journalctl", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[1] = new_item("E-Mail", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[2] = new_item("Beenden", MENEU.UME.UMEName.c_str());
    MENEU.UME.UMEItem[3] = nullptr;
    MENEU.UME.UMEMenu = new_menu(MENEU.UME.UMEItem);
    set_menu_win(MENEU.UME.UMEMenu, MENEU.UME.UMEWin);
    set_menu_sub (MENEU.UME.UMEMenu, derwin(MENEU.UME.UMEWin, 0, 0, 1, 1));
    set_menu_spacing(MENEU.UME.UMEMenu, 0,0,0);
    set_menu_format(MENEU.UME.UMEMenu, 5, 0);
    menu_opts_off(MENEU.UME.UMEMenu, O_SHOWDESC);
    menu_opts_off(MENEU.UME.UMEMenu, O_NONCYCLIC);
    //set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.UMeFe_HG));//|A_BOLD);
    set_menu_grey(MENEU.UME.UMEMenu, COLOR_PAIR(HMcolor.HaMe_grey)|A_BOLD);
    set_menu_mark(MENEU.UME.UMEMenu,"");
    set_current_item(MENEU.UME.UMEMenu, MENEU.UME.UMEItem[0]);
    post_menu(MENEU.UME.UMEMenu);
} /* Info Menü */

WINDOW *MenuClass::tmpWi(string name, int id) {
    if ((strcmp(name.c_str(),"Datei")==0) || (id==0)){
        Datei_menu();
        HMTMPWIN = MENEU.UME.UMEWin;
        HMTMPMENU = MENEU.UME.UMEMenu;
    }else if ((strcmp(name.c_str(),"DaemonType")==0) || (id==1)){
        DaemonType_menu();
        HMTMPWIN = MENEU.UME.UMEWin;
        HMTMPMENU = MENEU.UME.UMEMenu;
    }else if ((strcmp(name.c_str(),"Systemctl")==0) || (id==2)){
        Systemctl_menu();
        HMTMPWIN = MENEU.UME.UMEWin;
        HMTMPMENU = MENEU.UME.UMEMenu;
    }else if ((strcmp(name.c_str(),"Info")==0) || (id==4)){
        Info_menu();
        HMTMPWIN = MENEU.UME.UMEWin;
        HMTMPMENU = MENEU.UME.UMEMenu;
    }
    return HMTMPWIN;
}

void MenuClass::fensterwahl(string wahl) {
    string menupoint = ServicePtr->AktivName; //item_name(current_item(LiMENU.LMenu));
    string befehl;
    if       (wahl.compare(" Datei") == 0) {
        Datei_menu();
    }else if (wahl.compare("Systemctl") == 0) {
        Systemctl_menu();
    }else if (wahl.compare("DaemonType") == 0) {
        DaemonType_menu();
    }else if (wahl.compare("Systemctl") == 0) {
        Info_menu();
    }else if (wahl.compare("Service") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "service";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Swap") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "swap";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Timer") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "timer";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Device") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "device";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Mount") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "mount";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Path") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "path";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Target") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "target";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Socket") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "socket";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Slice") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "slice";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Scope") == 0) {
        ServicePtr->start = 0;
        ServicePtr->selected = 0;
        ServicePtr->systemctlwahl = "scope";
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("Man Page")==0){
        exit(EXIT_SUCCESS);
        //DATEIMANPAGE::Start_ManP();
    }else if (wahl.compare("Befehle")==0){
        exit(EXIT_SUCCESS);
        //DATEIBEFEHLE::befehle_main();
    }else if (wahl.compare("Einstellung")==0){
        exit(EXIT_SUCCESS);
        //einDa();
    }else if (wahl.compare("Beenden")==0){
        exit(EXIT_SUCCESS);
    }else if (wahl.compare("START") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl start " + menupoint + " --now";
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("STOP") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl stop " + menupoint + " --now";
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("RELOAD") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl reload " + menupoint + " --now";
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("RESTART") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl restart " + menupoint + " --now";
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("ENABLE") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl enable " + menupoint;
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("DISABLE") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl disable " + menupoint;
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("STATUS") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl status " + menupoint;
        ServicePtr->Statusabfrage(TaskPtr->TERM_AUSGABE(befehl));
    }else if (wahl.compare("UNMASK") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl unmask " + menupoint;
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("MASK") == 0) {
        pos_menu_cursor(LiMENU.LMenu);
        befehl = "systemctl mask " + menupoint;
        TaskPtr->TERM_AUSGABE(befehl);
        ServicePtr->ServiceListFill();
    }else if (wahl.compare("journalctl") == 0) {
        befehl = "journalctl -b -u " + menupoint;
        ServicePtr->Statusabfrage(TaskPtr->TERM_AUSGABE(befehl));
    }
}

void MenuClass::QUIT(void){
    try {
        //###############--Hauptmenu--###############################################
        int E = item_count(MENEU.HMMenu);
        unpost_menu(MENEU.HMMenu);
        SAFE_DELETE(MENEU.HMMenu);
        SAFE_DELETE_ARRAY(MENEU.HMItem);
        wborder(MENEU.HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(MENEU.HMWin,0,E+1);
        delwin(MENEU.HMWin);
        endwin();
        //###############--Untermenu--###############################################
        E = item_count(MENEU.UME.UMEMenu);
        unpost_menu(MENEU.UME.UMEMenu);
        SAFE_DELETE(MENEU.UME.UMEMenu);
        SAFE_DELETE_ARRAY(MENEU.UME.UMEItem);
        wborder(MENEU.UME.UMEWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(MENEU.UME.UMEWin,0,E+1);
        delwin(MENEU.UME.UMEWin);
        endwin();

        refresh();
        redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));

    } catch (const NCursesException *e) {
        endwin();
        std::cerr << string(e->classname()) << std::endl;
        //res = e.errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        //res = e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        //res = EXIT_FAILURE;
    }
}

void MenuClass::MenuStart(void){
    try {
        set_current_item(MENEU.HMMenu, MENEU.HMItem[MeInAl]);
        HMTMPWIN = tmpWi(item_name(current_item(MENEU.HMMenu)),item_index(current_item(MENEU.HMMenu)));
        string tmpMeNa = string(item_name(current_item(MENEU.HMMenu)));
        string MeAuWa = "";
        //        std::string PATTER = "";
        ServicePtr->TableMoveRow();
        int tabkey = 1;
        int key;
        while ((key=wgetch(stdscr)) != KEY_F(10)) {
            switch(tabkey){
            case 1:{ // MainWindow ListMenu
                switch (key) {
//                case '/':{
//                    ServicePtr->searchInput();
//                    break;}
                case '?':{
                    ServicePtr->Statusabfrage(ABOUT_INFO);
                    break;}
                case KEY_RESIZE:{
                    resize();
                    break;}
                case KEY_DOWN:{
                    //menu_driver(LiMENU.LMenu, REQ_DOWN_ITEM);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_DOWN_ITEM);
                    ServicePtr->TableMoveRow();
                    break; }
                case KEY_UP:{
                    //menu_driver(LiMENU.LMenu, REQ_UP_ITEM);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_UP_ITEM);
                    ServicePtr->TableMoveRow();
                    break; }
                case KEY_NPAGE:{
                    //menu_driver(LiMENU.LMenu, REQ_UP_ITEM);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_SCR_DPAGE);
                    ServicePtr->TableMoveRow();
                    break; }
                case KEY_PPAGE:{
                    //menu_driver(LiMENU.LMenu, REQ_UP_ITEM);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_SCR_UPAGE);
                    ServicePtr->TableMoveRow();
                    break; }
                case KEY_END:{
                    //menu_driver(LiMENU.LMenu, REQ_UP_ITEM);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_LAST_ITEM);
                    ServicePtr->TableMoveRow();
                    break; }
                case KEY_HOME:{
                    //menu_driver(LiMENU.LMenu, REQ_UP_ITEM);
                    ServicePtr->start = 0;
                    ServicePtr->selected = 0;
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_FIRST_ITEM);
                    ServicePtr->TableMoveRow();
                    break; }
                case 0x09: {
                    tabkey = TaskPtr->ZahlenWerk(1,"++",2);
                    HMTMPWIN = tmpWi("Datei",0);
                    redrawwin(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    wrefresh(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    break; }
                case KEY_BTAB:{
                    tabkey = TaskPtr->ZahlenWerk(1,"--",2);
                    HMTMPWIN = tmpWi("Datei",0);
                    redrawwin(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    wrefresh(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    break; }
                case KEY_BACKSPACE:{
                    //menu_driver(LiMENU.LMenu, REQ_BACK_PATTERN);
                    ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_BACK_PATTERN);
                    break; }
                case 10:{
                    //string menupoint = item_name(current_item(LiMENU.LMenu));
                    string menupoint = ServicePtr->AktivName;
                    string befehl;
                    befehl = "systemctl status " + menupoint;
                    //pos_menu_cursor(LiMENU.LMenu);
                    ServicePtr->Statusabfrage(TaskPtr->TERM_AUSGABE(befehl));
                    break; }
                case 32:{
                    ServicePtr->tabledriver(ServicePtr->ServiceList, REQ_TOGGLE_ITEM);
                    //menu_driver(LiMENU.LMenu, REQ_TOGGLE_ITEM);
                    break; }
                default:{
                    if (key > 10 && key < 128) {
                        sprintf(ServicePtr->searchString,"%c",key);
                        PATTER.append(string(ServicePtr->searchString));
                        mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, PATTER.c_str(),-1);
                        ServicePtr->tabledriver(ServicePtr->ServiceList,REQ_NEXT_MATCH);
                        //            sprintf(searchString,"%c",key);
                    }
                    break; }
                }
                if (tabkey==1) {
                    ServicePtr->INFOWINDOW(ServicePtr->AktivName);
                    //ServicePtr->INFOWINDOW(item_name(current_item(LiMENU.LMenu)));
                    refresh();
                    touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
                    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
                    prefresh(LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1, WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));// -2
                } else if (tabkey==2) {
                    refresh();
                    wrefresh(TaskPtr->ClearWindow(MENEU.HMWin));
                    redrawwin(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    wrefresh(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                }
                break; } // MainWindow ListMenu
            case 2:{ //Hauptmenu
                switch(key){
//                case '/':{
//                    ServicePtr->searchInput();
//                    //ServicePtr->inputFor = INPUT_FOR_SEARCH;
//                    break;}
                case '?':{
                    ServicePtr->Statusabfrage(ABOUT_INFO);
                    break;}
                case KEY_RESIZE:{
                    resize();
                    break;}
                case KEY_DOWN:{
                    menu_driver(MENEU.UME.UMEMenu, REQ_DOWN_ITEM);
                    break; }
                case KEY_UP:{
                    menu_driver(MENEU.UME.UMEMenu, REQ_UP_ITEM);
                    break; }
                case KEY_RIGHT:{
                    MenuClass::MENEU.LoescheUME();
                    menu_driver(MENEU.HMMenu, REQ_RIGHT_ITEM);
                    tmpMeNa = string(item_name(current_item(MENEU.HMMenu)));
                    HMTMPWIN = tmpWi(item_name(current_item(MENEU.HMMenu)), item_index(current_item(MENEU.HMMenu)));
                    break; }
                case KEY_LEFT:{
                    MenuClass::MENEU.LoescheUME(); // delete before menu drive
                    menu_driver(MENEU.HMMenu, REQ_LEFT_ITEM);
                    tmpMeNa = string(item_name(current_item(MENEU.HMMenu)));
                    HMTMPWIN = tmpWi(item_name(current_item(MENEU.HMMenu)), item_index(current_item(MENEU.HMMenu)));
                    break; }
                case 0x09:{
                    tabkey = TaskPtr->ZahlenWerk(2,"++",2);
                    set_current_item(MENEU.HMMenu,  MENEU.HMItem[0]);
                    MenuClass::MENEU.LoescheUME();
                    wrefresh(TaskPtr->ClearWindow(MENEU.HMWin));
                    break; }
                case KEY_BTAB:{
                    tabkey = TaskPtr->ZahlenWerk(2,"--",2);
                    set_current_item(MENEU.HMMenu,  MENEU.HMItem[0]);
                    MenuClass::MENEU.LoescheUME();
                    wrefresh(TaskPtr->ClearWindow(MENEU.HMWin));
                    break;}
                case 10:{
                    MeInAl = item_index(current_item(MENEU.HMMenu));
                    fensterwahl(item_name(current_item(MENEU.UME.UMEMenu)));
                    tabkey = TaskPtr->ZahlenWerk(2,"++",2);
                    set_current_item(MENEU.HMMenu,  MENEU.HMItem[0]);
                    MenuClass::MENEU.LoescheUME();
                    wrefresh(TaskPtr->ClearWindow(MENEU.HMWin));
                    break; }
                }
                if (tabkey==2) {
                    refresh();
                    redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    prefresh(LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1, WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));
                    wrefresh(TaskPtr->ClearWindow(MENEU.HMWin));
                    redrawwin(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                    wrefresh(TaskPtr->ClearWindow(MENEU.UME.UMEWin));
                } else if(tabkey==1){
                    MenuClass::MENEU.LoescheUME();
                    refresh();
                    redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
                    prefresh(LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1, WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));
                }
                break;} // Hauptmenu
            }
        }

        ServicePtr->ENDE_NEW();

        if (LiMENU.LMItem){unpost_menu(LiMENU.LMenu);SAFE_DELETE(LiMENU.LMItem);SAFE_DELETE_ARRAY(LiMENU.LMItem);}
        //        int n_choices, i;
        //        n_choices = ARRAY_SIZE(LiMENU.LMItem);
        //        unpost_menu(LiMENU.LMenu);
        //        for(i = 0; i < n_choices; ++i)
        //            free_item(LiMENU.LMItem[i]);
        //        free_menu(LiMENU.LMenu);
        endwin();

    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        cout << e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        cout << e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        cout << EXIT_FAILURE;
    }
}

void MenuClass::resize(){
    WinPtr->WinSize->WCX(); // = 80;
    WinPtr->WinSize->HRY(); // = 24;
}

MenuClass::MenuClass(){

}

MenuClass::~MenuClass(){

}
