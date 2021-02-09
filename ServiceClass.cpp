#include <ServiceClass.h>

using namespace std;

TaskClass *TaskClass_SC = new TaskClass();
//MenuClass *MenuPtr_SC = new MenuClass();
ServiceClass *ServiceClass_SC = new ServiceClass();
//WinClass *WinPtr_SC = new WinClass();
MenuWinClass *MenuWinClass_SC = new MenuWinClass();

int X = 0;
/*##################################################################################*/
void ServiceClass::ServiceListFill() {
    string tmpService = TaskClass_SC->TERM_AUSGABE("systemctl list-unit-files -t "+ systemctlwahl +" | grep '."+ systemctlwahl +"' | awk '{$1=$1};1' | sort");
    string tmpServiceInfo = TaskClass_SC->TERM_AUSGABE("systemctl --all --type="+ systemctlwahl +" | grep '."+ systemctlwahl +"' | awk '{$1=$1};1' | sed 's/● //g' | sort");
    string tmpstr1,tmpstr2;
    std::vector<std::string> tmpaa,tmpbb;
    ServiceList.clear();
    vector<SERVICES>().swap(ServiceList);
    unsigned long X = 0;
    istringstream filestream(tmpService.c_str());

    if (filestream) {
        while (getline(filestream,tmpstr1)){
            tmpaa.push_back(string());
            tmpaa = TaskClass_SC->StringTeiler(tmpstr1,' ');
            ServiceList.push_back(SERVICES());
            ServiceList[X].SID = static_cast<int>(X);
            ServiceList[X].Name = tmpaa[0];
            ServiceList[X].Status = tmpaa[1];
            ServiceList[X].Target = systemctlwahl;
            X++;
            tmpaa.clear();
            vector<string>().swap(tmpaa);
        }
    } else {
        mvwaddnstr(MenuWinClass::START.TMPWin3, 5, 5, "failed to open or read" ,-1);
    }

    X = 0;
    istringstream filestream2(tmpServiceInfo.c_str());
    if (filestream2) {
        while (getline(filestream2,tmpstr2)){
            tmpbb.push_back(string());
            tmpbb = TaskClass_SC->StringTeiler(tmpstr2,' ');
            for(unsigned long Z = 0; Z < static_cast<unsigned long>(ServiceList.size()); Z++) {
                if (ServiceList[Z].Name.compare(tmpbb[0].c_str())==0) {
                    ServiceList.push_back(SERVICES());
                    ServiceList[Z].Load = tmpbb[1];
                    ServiceList[Z].Active = tmpbb[2];
                    ServiceList[Z].SubStatus = tmpbb[3];
                    for (unsigned long Y = 4; Y <  tmpbb.size(); Y++) {
                        if (Y == 4) {
                            ServiceList[Z].Description = tmpbb[Y];
                        } else {
                            ServiceList[Z].Description.append(" " + tmpbb[Y]);
                        }
                    }
                    break;
                }
            }
            X++;
            tmpbb.clear();
            vector<string>().swap(tmpbb);
        }
    } else {
        mvwaddnstr(MenuWinClass::START.TMPWin3, 5, 5, "failed to open or read" ,-1);
    }
    SetStateOption();
    //    ServiceListe();
}
void ServiceClass::ServiceListe(){
    if (MenuWinClass_SC->SERVICEMENU.LMItem){unpost_menu(MenuWinClass_SC->SERVICEMENU.LMenu);SAFE_DELETE(MenuWinClass_SC->SERVICEMENU.LMItem);SAFE_DELETE_ARRAY(MenuWinClass_SC->SERVICEMENU.LMItem);}
    if (MenuWinClass::START.TMPWin4){werase(MenuWinClass::START.TMPWin4);delwin(MenuWinClass::START.TMPWin4);endwin();}
    int mrows = 0;
    int mcols = 0;
    unsigned long count = ServiceList.size();
    MenuWinClass_SC->SERVICEMENU.LMItem = static_cast<ITEM **>(calloc(count, sizeof(ITEM *)));
    for (unsigned long i = 0; i < (count-2); i++)
    {
        MenuWinClass_SC->SERVICEMENU.LMItem[i] = new_item(ServiceList[i].Name.c_str(), ServiceList[i].Status.c_str());
    }
    MenuWinClass_SC->SERVICEMENU.LMItem[count-1] = nullptr;
    MenuWinClass_SC->SERVICEMENU.LMenu = new_menu(MenuWinClass_SC->SERVICEMENU.LMItem);
    scale_menu(MenuWinClass_SC->SERVICEMENU.LMenu, &mrows, &mcols);
    MenuWinClass::START.TMPWin4 = newpad(TaskClass_SC->WinFullSize(MenuWinClass::START.TMPWin2,static_cast<int>(count),"H"), TaskClass_SC->WinFullSize(MenuWinClass::START.TMPWin2,mcols,"W"));
    wbkgd(MenuWinClass::START.TMPWin4, COLOR_PAIR(MenuWinClass::START.WinColor.BK_LISTPAD));
    set_menu_win(MenuWinClass_SC->SERVICEMENU.LMenu, MenuWinClass::START.TMPWin4);
    set_menu_sub(MenuWinClass_SC->SERVICEMENU.LMenu, MenuWinClass::START.TMPWin4);
    set_menu_format(MenuWinClass_SC->SERVICEMENU.LMenu, MenuWinClass_SC->START.HRY()-9, 1); //-3
    set_menu_spacing(MenuWinClass_SC->SERVICEMENU.LMenu, 0, 0, 0);
    menu_opts_off(MenuWinClass_SC->SERVICEMENU.LMenu, O_SELECTABLE);
    menu_opts_on(MenuWinClass_SC->SERVICEMENU.LMenu, O_NONCYCLIC);
    set_menu_fore(MenuWinClass_SC->SERVICEMENU.LMenu, COLOR_PAIR(20)|A_BOLD|A_REVERSE);
    set_menu_back(MenuWinClass_SC->SERVICEMENU.LMenu, COLOR_PAIR(78)|A_BOLD);
    set_menu_grey(MenuWinClass_SC->SERVICEMENU.LMenu, COLOR_PAIR(30));
    set_menu_mark(MenuWinClass_SC->SERVICEMENU.LMenu, "");
    post_menu(MenuWinClass_SC->SERVICEMENU.LMenu);
}
void ServiceClass::INFOWINDOW(string Name){
    werase(MenuWinClass::START.TMPWin5);
    wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(MenuWinClass::START.WinColor.BK_INFOWIN)|A_BOLD,nullptr);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 1, "STATE:                   " ,-1);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 2, 1, "LOAD:                    " ,-1);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 3, 1, "AKTIVE:                  " ,-1); //9
    mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 1, "SUB:                     " ,-1);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 26, "DESC:" ,-1);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 26, "Suche:" ,-1);
    //mvwaddnstr(MenuWinClass::START.TMPWin3, 6, 1, "                  " ,-1);
    wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(MenuWinClass::START.WinColor.BK_INFOWIN)|A_BOLD,nullptr);

    for (unsigned long X = 0; X < static_cast<unsigned long>(ServiceList.size());X++){
        if (ServiceList[X].Name.compare(Name)==0) {
            switch (ServiceList[X].state) {
            case UNIT_STATE_ENABLED:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_BAD:
            case UNIT_STATE_DISABLED:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_STATIC:
            case UNIT_STATE_MASKED:
            case UNIT_STATE_GENERATED:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_TMP:
            default:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            } // ende status switch
            switch (ServiceList[X].load) {
            case UNIT_LOADSTATE_LOADED:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_LOADSTATE_NOTFOUND:
            case UNIT_LOADSTATE_UNLOAD:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            } // ende load switch
            switch (ServiceList[X].active) {
            case UNIT_ACTIVESTATE_ACTIVE:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_ACTIVESTATE_INACTIVE:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            }
            switch (ServiceList[X].substate) {
            case UNIT_SUBSTATE_RUNNING:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_SUBSTATE_CONNECTED:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
            case UNIT_SUBSTATE_INVALID:
            case UNIT_SUBSTATE_EXITED:
            case UNIT_SUBSTATE_DEAD:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(MenuWinClass::START.TMPWin3, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            }
            //wattr_on(MenuWinClass::START.TMPWin5, COLOR_PAIR(78)|A_BOLD,nullptr);
            mvwaddnstr(MenuWinClass::START.TMPWin5, 0, 0, ServiceList[X].Description.c_str() ,-1);
            //wattr_off(MenuWinClass::START.TMPWin5, COLOR_PAIR(78)|A_BOLD,nullptr);
        }
    }
}
void ServiceClass::Statusabfrage(string ausgabestatus) {
    int hoehe;
    int rowy = MenuWinClass_SC->START.HRY()-4;
    int ROWS = 0; int Key;
    STATUSWIN = newwin(MenuWinClass_SC->START.HRY()-2, MenuWinClass_SC->START.WCX()-2, 1, 1);
    wbkgd(STATUSWIN, COLOR_PAIR(MenuWinClass::START.WinColor.WinBk_Help)|A_BOLD);
    box(STATUSWIN, 0,0);

    hoehe = TaskClass_SC->Zeilen(ausgabestatus.c_str(),MenuWinClass_SC->START.WCX()-4);
    STATUSINFO = newpad(hoehe, MenuWinClass_SC->START.WCX()-4);
    wbkgd(STATUSINFO, COLOR_PAIR(MenuWinClass::START.WinColor.WinBk_Help)|A_BOLD);
    STATUSINFO = derwin(STATUSWIN, MenuWinClass_SC->START.HRY()-4, MenuWinClass_SC->START.WCX()-4, 1, 1);
    wattr_on(STATUSINFO, COLOR_PAIR(MenuWinClass::START.WinColor.WinFo_Help)|A_BOLD,nullptr);
    mvwaddnstr(STATUSINFO, 0, 0, ausgabestatus.c_str(),-1);
    wattr_off(STATUSINFO, COLOR_PAIR(MenuWinClass::START.WinColor.WinFo_Info)|A_BOLD,nullptr);
    wattr_on(STATUSWIN, COLOR_PAIR(70)|A_BOLD,nullptr);
    mvwaddnstr(STATUSWIN, MenuWinClass_SC->START.HRY() -3, MenuWinClass_SC->START.WCX()-15, "[ EXIT ESC ]" ,-1);
    wattr_off(STATUSWIN, COLOR_PAIR(70)|A_BOLD,nullptr);

    wrefresh(STATUSWIN);
    touchwin(STATUSWIN);
    prefresh(STATUSINFO, 0, 0, 0, 0, MenuWinClass_SC->START.HRY() -4, MenuWinClass_SC->START.WCX()-4);

    while ((Key=getch()) != 27) {
        switch (Key) {
        case KEY_DOWN:{
            if ((ROWS + rowy +1) >= hoehe){
                ROWS = hoehe;
            }else {
                ROWS++;
            }
            break;}
        case KEY_UP:{
            if (ROWS <= 0){
                ROWS = 0;
            }else {
                ROWS--;
            }
            break;}
        default:{
            break; }
        }
        refresh();
        touchwin(STATUSWIN);
        prefresh(STATUSINFO, ROWS, 0, 0, 0, MenuWinClass_SC->START.HRY() -4, MenuWinClass_SC->START.WCX()-4);
    }
    if (STATUSINFO){werase(STATUSINFO);delwin(STATUSINFO);}
    if (STATUSWIN){werase(STATUSWIN);delwin(STATUSWIN);}
    redrawwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
    wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
    redrawwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
    wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
    prefresh(MenuWinClass_SC->START.TMPWin4, 0, 0, 2, 1, MenuWinClass_SC->START.HRYw4() + 1, MenuWinClass_SC->START.WCXw4());
    prefresh(MenuWinClass_SC->START.TMPWin5, 0, 0, MenuWinClass_SC->START.HRY()-4, MenuWinClass_SC->START.WCX()-46, MenuWinClass_SC->START.HRYw5(), MenuWinClass_SC->START.WCXw5());
}
void ServiceClass::ENDE() {
//    try {
    if (MenuWinClass::START.TimeWin) {werase(MenuWinClass::START.TimeWin); delwin(MenuWinClass::START.TimeWin); endwin();}
    if (MenuWinClass::SERVICEMENU.LMItem) {unpost_menu(MenuWinClass::SERVICEMENU.LMenu); SAFE_DELETE(MenuWinClass::SERVICEMENU.LMItem); SAFE_DELETE_ARRAY(MenuWinClass::SERVICEMENU.LMItem);}
    if (MenuWinClass::TOPMENU.UME.UMEItem) { unpost_menu(MenuWinClass::TOPMENU.UME.UMEMenu); SAFE_DELETE(MenuWinClass::TOPMENU.UME.UMEItem); SAFE_DELETE_ARRAY(MenuWinClass::TOPMENU.UME.UMEItem);}
    if (MenuWinClass::TOPMENU.HMItem) { unpost_menu(MenuWinClass::TOPMENU.HMMenu); SAFE_DELETE(MenuWinClass::TOPMENU.HMItem); SAFE_DELETE_ARRAY(MenuWinClass::TOPMENU.HMItem);}
    if (MenuWinClass::START.TMPWin5) {werase(MenuWinClass::START.TMPWin5); delwin(MenuWinClass::START.TMPWin5); endwin();}
    if (MenuWinClass::START.TMPWin4) {werase(MenuWinClass::START.TMPWin4); delwin(MenuWinClass::START.TMPWin4); endwin();}
    if (MenuWinClass::START.TMPWin3) {werase(MenuWinClass::START.TMPWin3); delwin(MenuWinClass::START.TMPWin3); endwin();}
    if (MenuWinClass::START.TMPWin2) {werase(MenuWinClass::START.TMPWin2); delwin(MenuWinClass::START.TMPWin2); endwin();}
    if (MenuWinClass::START.TMPWin1) {werase(MenuWinClass::START.TMPWin1); delwin(MenuWinClass::START.TMPWin1); endwin();}
    werase(stdscr);
    ServiceList.clear();
    vector<SERVICES>(ServiceList).swap (ServiceList);
    clear();
//    } catch (const NCursesException *e) { endwin(); std::cerr << e->message << std::endl; cout << e->errorno;
//    } catch (const NCursesException &e) { endwin(); std::cerr << e.message << std::endl; cout << e.errorno;
//    } catch (const std::exception &e) { endwin(); std::cerr << "Exception: " << e.what() << std::endl; cout << EXIT_FAILURE; }
}
/*##################################################################################*/
// new Systemd bestandteile
void ServiceClass::SetStateOption() { //SERVICES unit // pushitem
    //vector<SERVICES>().swap(ServiceList);
    //UnitItem *item = new UnitItem();
    //string name(unit->id);
    //item->Name = name;
    //item->target       = name.substr(name.find_last_of('.') + 1, name.length());
    //item->description  = string(unit->description == nullptr ? "" : unit->description);
    //item->Status       = string(unit->state       == nullptr ? "" : unit->state);
    //item->SubStatus    = string(unit->subState    == nullptr ? "" : unit->subState);
    //item->LoadStatus   = string(unit->loadState   == nullptr ? "" : unit->loadState);
    //item->ActiveStatus = string(unit->activeState == nullptr ? "" : unit->activeState);
    //item->ServicePath  = string(unit->unitPath    == nullptr ? "" : unit->unitPath);

    for (unsigned long i =0; i<ServiceList.size();i++) {
        if (!ServiceList[i].Name.empty()) {
            //string state(unit->state);
            //string sub(unit->substate == nullptr ? "" : unit->substate);
            //string load(unit->load == nullptr ? "" : unit->load);
            //string aktiv(unit->active == nullptr ? "" : unit->active);
            if (ServiceList[i].Status.compare("enabled") == 0) {
                ServiceList[i].state = UNIT_STATE_ENABLED;
            } else if (ServiceList[i].Status.compare("masked") == 0) {
                ServiceList[i].state = UNIT_STATE_MASKED;
            } else if (ServiceList[i].Status.compare("static") == 0) {
                ServiceList[i].state = UNIT_STATE_STATIC;
            } else if (ServiceList[i].Status.compare("bad") == 0 || ServiceList[i].Status.compare("removed") == 0) {
                ServiceList[i].state = UNIT_STATE_BAD;
            } else if (ServiceList[i].Status.compare("disabled") == 0){
                ServiceList[i].state = UNIT_STATE_DISABLED;
            } else if (ServiceList[i].Status.compare("generated") == 0){
                ServiceList[i].state = UNIT_STATE_GENERATED;
            } else{
                ServiceList[i].state = UNIT_STATE_TMP;
            }
            if (!ServiceList[i].SubStatus.empty()) {
                if (ServiceList[i].SubStatus.compare("running") == 0) {
                    ServiceList[i].substate = UNIT_SUBSTATE_RUNNING;
                } else if (ServiceList[i].SubStatus.compare("dead") == 0) {
                    ServiceList[i].substate = UNIT_SUBSTATE_DEAD;
                } else if (ServiceList[i].SubStatus.compare("exited") == 0) {
                    ServiceList[i].substate = UNIT_SUBSTATE_EXITED;
                } else{
                    ServiceList[i].substate = UNIT_SUBSTATE_CONNECTED;
                }
            } else {
                ServiceList[i].substate = UNIT_SUBSTATE_INVALID;
            }
            if (!ServiceList[i].Load.empty()) {
                if (ServiceList[i].Load.compare("loaded") == 0) {
                    ServiceList[i].load = UNIT_LOADSTATE_LOADED;
                } else if (ServiceList[i].Load.compare("not-found") == 0) {
                    ServiceList[i].load = UNIT_LOADSTATE_NOTFOUND;
                } else if (ServiceList[i].Load.compare("unloaded") == 0) {
                    ServiceList[i].load = UNIT_LOADSTATE_UNLOAD;
                }
            } else {
                ServiceList[i].load = UNIT_SUBSTATE_INVALID;
            }
            if (!ServiceList[i].Active.empty()) {
                if (ServiceList[i].Active.compare("active") == 0) {
                    ServiceList[i].active = UNIT_ACTIVESTATE_ACTIVE;
                } else if (ServiceList[i].Active.compare("inactive") == 0) {
                    ServiceList[i].active = UNIT_ACTIVESTATE_INACTIVE;
                }
            } else {
                ServiceList[i].active = UNIT_SUBSTATE_INVALID;
            }
        } else {
            ServiceList[i].state = UNIT_STATE_MASKED;
        }
    }
    // freeUnitInfo(unit);
    // items.push_back(item);
    BuildWin();
};
void ServiceClass::BuildWin() {
    if (MenuWinClass_SC->SERVICEMENU.LMItem){unpost_menu(MenuWinClass_SC->SERVICEMENU.LMenu);SAFE_DELETE(MenuWinClass_SC->SERVICEMENU.LMItem);SAFE_DELETE_ARRAY(MenuWinClass_SC->SERVICEMENU.LMItem);}
    if (MenuWinClass_SC->START.TMPWin4){werase(MenuWinClass_SC->START.TMPWin4);delwin(MenuWinClass_SC->START.TMPWin4);endwin();}
    StateColor.Green = 28;
    StateColor.Yellow = 38;
    StateColor.Red = 18;
    StateColor.White = 78;
    unsigned long count = ServiceList.size();
    MenuWinClass_SC->START.TMPWin4 = newpad(static_cast<int>(count), MenuWinClass_SC->START.WinSize.WCX_TmpWinReal(MenuWinClass::START.TMPWin2));
    wbkgd(MenuWinClass_SC->START.TMPWin4, COLOR_PAIR(MenuWinClass::START.WinColor.BK_LISTPAD));

    for (unsigned long i = 0; i < ServiceList.size(); i++) {
        TableDraw(ServiceList[i], static_cast<int>(i));
        //TableMoveRow();
    }
}
void ServiceClass::TableMoveRow() { //drawUnits
    if (ServiceList.empty()) {
        // updateUnits();
        ServiceListFill();
    }
    //  const int oneX = unit->sub & A_COLOR;
    for (int i = 0; i < MenuWinClass_SC->START.HRYw4(); i++) {
        if ((i + ServiceClass::start) > static_cast<int>(ServiceList.size() - 1)) {
            break;
        }
        SERVICES unit = ServiceList[static_cast<unsigned long>(start + i)];
        if (i == selected) {
            StateColor.SetSignalColor(17, 37, 27, 87);
            MenuWinClass::SERVICEMENU.AktivName = ServiceList[static_cast<unsigned long>(start + selected)].Name;
            wattron(MenuWinClass_SC->START.TMPWin4, COLOR_PAIR(87)|A_BOLD);
        }
        TableDraw(unit, i);
        wattroff(MenuWinClass_SC->START.TMPWin4, COLOR_PAIR(87)|A_BOLD);
        StateColor.SetSignalColor(18, 38, 28, 78);
    }
    /*    if (inputFor == INPUT_FOR_LIST) {
    //        drawInfo();
    //    } else {
    //        drawSearch();
    //    }*/
    refresh();
    touchwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
    wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
    touchwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
    wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
    prefresh(MenuWinClass::START.TMPWin4, 0, 0, 2, 1, MenuWinClass::START.HRYw4() + 1, MenuWinClass::START.WCXw4());
    prefresh(MenuWinClass::START.TMPWin5, 0, 0, MenuWinClass::START.HRY() - 4, MenuWinClass::START.WCX() - 46, MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5());
}
void ServiceClass::TableDraw(SERVICES unit, int y) {
    if (unit.Target.compare(systemctlwahl)==0) {
        //unit.SID = unit.SID++;
        if (unit.Name.size() < static_cast<unsigned long>(MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2))) {
            unit.Name.resize(MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2), ' ');
        }else {
            unit.Name.resize(MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2));
        }
        if (unit.Status.size() <= MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4)) {
            unit.Status.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4), ' ');
        }else {
            unit.Status.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4));
        }
        if (unit.SubStatus.size() <= MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4) ) {
            unit.SubStatus.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4), ' ');
        } else {
            unit.SubStatus.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4));
        }
        if (unit.Active.size() <= MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4) ) {
            unit.Active.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4), ' ');
        }else {
            unit.Active.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4));
        }
        if (unit.Load.size() <= MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4) ) {
            unit.Load.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4), ' ');
        }else {
            unit.Load.resize(MenuWinClass_SC->START.WinSize.WinHalfDurch(MenuWinClass_SC->START.TMPWin2, 4));
        }

        std::string name(unit.Name);

        wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
        mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.RAND-1, "%s", name.c_str());
        wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);

        switch (unit.state) {
        case UNIT_STATE_ENABLED:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, "%s  ", unit.Status.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_STATE_BAD:
        case UNIT_STATE_DISABLED:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, "%s ", unit.Status.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        case UNIT_STATE_STATIC:
        case UNIT_STATE_MASKED:
        case UNIT_STATE_GENERATED:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, "%s   ", unit.Status.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            break;
        case UNIT_STATE_TMP:
        default:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+1, "%9s", unit.Status.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.load) {
        case UNIT_LOADSTATE_LOADED:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX() - 11, unit.LoadStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_LOADSTATE_NOTFOUND:
        case UNIT_LOADSTATE_UNLOAD:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX()- 11, unit.LoadStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX() - 11, unit.LoadStatus.c_str()); // 3 jetzt 9
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.active) {
        case UNIT_ACTIVESTATE_ACTIVE:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX()- 21, unit.ActiveStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_ACTIVESTATE_INACTIVE:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX()- 21, unit.ActiveStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX() - 11, unit.LoadStatus.c_str()); // 3 jetzt 9
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.substate) {
        case UNIT_SUBSTATE_RUNNING:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_SUBSTATE_CONNECTED:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
        case UNIT_SUBSTATE_INVALID:
        case UNIT_SUBSTATE_EXITED:
        case UNIT_SUBSTATE_DEAD:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuWinClass::START.TMPWin4, y, MenuWinClass_SC->START.WinSize.WCX_TmpWinCenter(MenuWinClass_SC->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str()); // 3 jetzt 9
            wattroff(MenuWinClass::START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
    }
}
void ServiceClass::TableDriver(std::vector<SERVICES> SRVLIST,int key){
    int ps = MenuWinClass_SC->START.HRYw4()-1;
    switch(key){
    case REQ_LEFT_ITEM:{
        break;}
    case REQ_RIGHT_ITEM:{
        break;}
    case REQ_UP_ITEM:{
        if (start > 0 && selected < ps) { // / 2
            start--;
        } else if (selected > 0) {
            selected--;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_DOWN_ITEM:{
        int offset = start + selected;
        int max = static_cast<int>(SRVLIST.size());
        if ((start + ps) < max) {
            if (selected < ps) { // / 2
                selected++;
            } else {
                start++;
            }
        } else if (offset < max) {
            selected++;
        }
        if (offset >= max) {
            selected = ps;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_DOWN_ITEM);
        }
        break;}
    case REQ_SCR_ULINE:{
        break;}
    case REQ_SCR_DLINE:{
        break;}
    case REQ_SCR_UPAGE:{
        if (start > 0) {
            start -= ps;
        }
        if (start < 0) {
            start = 0;
            selected = 0;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_SCR_DPAGE:{
        int max = static_cast<int>(SRVLIST.size()-1);
        if ((start + ps) < max) { // / 2
            start += ps;
        }
        if ((start + ps) > max) {
            start = max - ps;
            selected = ps;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_DOWN_ITEM);
        }
        break;}
    case REQ_FIRST_ITEM:{
        if (start > 0 && selected < ps) { // / 2
            start--;
        } else if (selected > 0) {
            selected--;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_LAST_ITEM:{
        int max = static_cast<int>(SRVLIST.size()-1);
        start = max - ps;
        selected = ps;
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_NEXT_ITEM:{
        if (start > 0 && selected < ps) { // / 2
            start--;
        } else if (selected > 0) {
            selected--;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_PREV_ITEM:{
        int offset = start + selected;
        int max = static_cast<int>(SRVLIST.size());

        if ((start + ps) < max) {
            if (selected < ps) { // / 2
                selected++;
            } else {
                start++;
            }
        } else if (offset < max) {
            selected++;
        }
        if (offset >= max) {
            selected = ps;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::TableDriver(SRVLIST,REQ_DOWN_ITEM);
        }
        break;}
    case REQ_TOGGLE_ITEM:{
        break;}
    case REQ_CLEAR_PATTERN:{
        break;}
    case REQ_BACK_PATTERN:{
        if (MenuWinClass_SC->PATTERN.size()>0) {MenuWinClass_SC->PATTERN.pop_back(); MenuWinClass_SC->PATTERN.shrink_to_fit();};
        mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, "                      ",-1);
        mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass_SC->PATTERN.c_str(),-1);
        break;}
    case REQ_NEXT_MATCH:{
        int position = 0;
        for (auto unit : ServiceList) {
            if (!unit.Name.empty()) {
                if (unit.Name.rfind(MenuWinClass_SC->PATTERN.c_str()) != std::string::npos) {
                    lastFound = position;
                    moveTo(position); }
                position++;
            } else {
                continue;
            }
        }
        if (lastFound == 0) {
            MenuWinClass_SC->PATTERN.clear();
            return;
        }
        lastFound = 0;
        TableDriver(ServiceList,REQ_NEXT_MATCH);
        break;}
    case REQ_PREV_MATCH:{
        break;}
    }
}
void ServiceClass::searchInput() {
    int key;
    while ((key=wgetch(stdscr)) != KEY_F(10)) {
        switch(key) {
        case 27:{ // ESC
            MenuWinClass_SC->PATTERN.clear();
            mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, "                      ",-1);
            break;}
        case KEY_ENTER: // Ctrl-M
        case 10: {// Enter
            TableDriver(ServiceList,REQ_NEXT_MATCH);
            break;}
        case KEY_BACKSPACE:{
            if (MenuWinClass_SC->PATTERN.size()>0) {MenuWinClass_SC->PATTERN.pop_back(); MenuWinClass_SC->PATTERN.shrink_to_fit();};
            mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, "                      ",-1);
            mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass_SC->PATTERN.c_str(),-1);
            TableDriver(ServiceList,REQ_NEXT_MATCH);
            break;}
        default:{
            if (key > 10 && key < 128) {
                sprintf(searchString,"%c",key);
                MenuWinClass_SC->PATTERN.append(string(searchString));
                mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass_SC->PATTERN.c_str(),-1);
                TableDriver(ServiceList,REQ_NEXT_MATCH);
            }
            break;}
        }
        refresh();
        touchwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
        wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin2));
        touchwin(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
        wrefresh(TaskClass_SC->ClearWindow(MenuWinClass::START.TMPWin3));
        prefresh(MenuWinClass::START.TMPWin4, 0, 0, 2, 1, MenuWinClass::START.HRYw4() + 1, MenuWinClass::START.WCXw4());
        prefresh(MenuWinClass::START.TMPWin5, 0, 0, MenuWinClass::START.HRY()-4, MenuWinClass::START.WCX()-46, MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5());
    }
}
void ServiceClass::drawSearch() {
    /*  * Lets indicate it is a search input   */
    char text[BUFSIZ] = "";
    if (lastFound == 0) {
        sprintf(searchString,"%s",text);
        MenuWinClass_SC->PATTERN.append(string(searchString));
        //sprintf(text, "%s%s", text, searchString);
    }
    /*   * Draw it using any visible, light color   */
    //drawStatus(1, text, 0);
    mvwaddnstr(MenuWinClass::START.TMPWin3, 4, 33, MenuWinClass_SC->PATTERN.c_str(),-1);
}
void ServiceClass::moveTo(int position) {
    start = selected = 0;
    for (int i = 0; i < position; i++) {
        TableDriver(ServiceList,REQ_UP_ITEM);
    }
}

string ServiceClass::SearchDriver(SeaReq drv, WINDOW *Win, int Key, string Search, int Posi) {
    static const int Start = 33;
    int hry, wcx;
    getyx(Win, hry, wcx);
    int MaxSearchTextLaenge = (MenuWinClass::START.WCX() - (Start + MenuWinClass::START.BorderWeight));
    int Laenge = Search.length();
    int AbsolPosi;
    AbsolPosi = (Start + Posi);
    char TmpKey[BUFSIZE] = "";
    sprintf(TmpKey, "%c", Key);
    string dummi;
    dummi.assign(MaxSearchTextLaenge,' ');
    switch (drv) {
    case REQ_DEL_BACKSPACE:{
        if ((wcx > Start) && (wcx <= (Start + Laenge))) {
            Search.erase(Posi-1, 1);
            mvwaddnstr(Win, 4, Start, dummi.c_str(), -1);
            mvwaddnstr(Win, 4, Start, Search.c_str(), -1);
            wmove(Win, 4, AbsolPosi - 1);
        }
        break; }
    case REQ_DEL_DC:{
        if ((wcx > Start) && (wcx < (Start + Laenge))) {
            Search.erase(Posi+1, 1);
            mvwaddnstr(Win, 4, Start, dummi.c_str(), -1);
            mvwaddnstr(Win, 4, Start, Search.c_str(), -1);
            wmove(Win, 4, AbsolPosi - 1);
        }
        break; }
    case REQ_RIGHT:{
        if ((wcx > Start) && (wcx <= (Start + Laenge))) {
        //if ((Posi != 0) || ((Posi-1) <= Laenge)) {
            int cursorbewegen = AbsolPosi +1;
            wmove(Win, 4, cursorbewegen);
        }
        break; }
    case REQ_LEFT:{
        if ((wcx > Start) && (wcx <= (Start + Laenge))) {
        //if ((Posi != 0) || ((Posi-1) <= Laenge)) {
            int cursorbewegen = AbsolPosi -1;
            wmove(Win, 4, cursorbewegen);
        }
        break; }
    case REQ_INS_DEFAULT:{
        if (Key > 10 && Key < 128) {
            if (Posi < Laenge) {
                Search.insert(Posi, string(TmpKey));
                mvwaddnstr(Win, 4, Start, Search.c_str(), -1);
                wmove(Win, 4, (Start + Posi));
            } else {
                Search.append(string(TmpKey));
                mvwaddnstr(Win, 4, Start, Search.c_str(), -1);
            }
        };
        break;}
    }
    wrefresh(Win);
    return Search;
}
/*##################################################################################*/
ServiceClass::ServiceClass(){
    systemctlwahl = "service";
}
ServiceClass::~ServiceClass(){

}
/*##################################################################################*/
