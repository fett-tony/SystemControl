#include <src/ServiceClass.h>
#include <src/MenuClass.h>
#include <src/WinClass.h>
#include <src/TaskClass.h>
#include <src/Info.h>

using namespace std;

extern class TaskClass * TaskPtr;
extern class MenuClass * MenuPtr;
//extern class ServiceClass * ServicePtr;
extern class WinClass * WinPtr;

int X = 0;

void ServiceClass::ServiceListFill() {
    //string tmpSystemd = TaskPtr->TERM_AUSGABE("systemctl --all | egrep 'timer|target|swap|socket|service|slice|scope|path|mount|device' | awk '{$1=$1};1' | sed 's/● //g'");
    string tmpService = TaskPtr->TERM_AUSGABE("systemctl list-unit-files -t "+ systemctlwahl +" | grep '."+ systemctlwahl +"' | awk '{$1=$1};1' | sort");
    string tmpServiceInfo = TaskPtr->TERM_AUSGABE("systemctl --all --type="+ systemctlwahl +" | grep '."+ systemctlwahl +"' | awk '{$1=$1};1' | sed 's/● //g' | sort");
    string tmpstr1,tmpstr2;
    std::vector<std::string> tmpaa,tmpbb;
    ServiceList.clear();
    vector<SERVICES>().swap(ServiceList);
    unsigned long X = 0;
    istringstream filestream(tmpService.c_str());

    if (filestream) {
        while (getline(filestream,tmpstr1)){
            tmpaa.push_back(string());
            tmpaa = TaskPtr->StringTeiler(tmpstr1,' ');
            ServiceList.push_back(SERVICES());
            ServiceList[X].SID = static_cast<int>(X);
            ServiceList[X].Name = tmpaa[0];
            ServiceList[X].Status = tmpaa[1];
            ServiceList[X].Target = systemctlwahl; //ServiceList[X].Name.substr(ServiceList[X].Name.find(".")+1,ServiceList[X].Name.length());
            X++;
            tmpaa.clear();
            vector<string>().swap(tmpaa);
        }
    } else {
        mvwaddnstr(WinPtr->START.TMPWin3, 5, 5, "failed to open or read" ,-1);
    }

    X = 0;
    istringstream filestream2(tmpServiceInfo.c_str());
    if (filestream2) {
        while (getline(filestream2,tmpstr2)){
            tmpbb.push_back(string());
            tmpbb = TaskPtr->StringTeiler(tmpstr2,' ');
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
        mvwaddnstr(WinPtr->START.TMPWin3, 5, 5, "failed to open or read" ,-1);
    }
    SetStateOption();
    //    ServiceListe();
}

void ServiceClass::ServiceListe(){
    if (MenuPtr->LiMENU.LMItem){unpost_menu(MenuPtr->LiMENU.LMenu);SAFE_DELETE(MenuPtr->LiMENU.LMItem);SAFE_DELETE_ARRAY(MenuPtr->LiMENU.LMItem);}
    if (MenuPtr->LiMENU.LMWin){werase(MenuPtr->LiMENU.LMWin);delwin(MenuPtr->LiMENU.LMWin);endwin();}
    int mrows = 0;
    int mcols = 0;
    unsigned long count = ServiceList.size();
    MenuPtr->LiMENU.LMItem = static_cast<ITEM **>(calloc(count, sizeof(ITEM *)));
    for (unsigned long i = 0; i < (count-2); i++)
    {
        MenuPtr->LiMENU.LMItem[i] = new_item(ServiceList[i].Name.c_str(), ServiceList[i].Status.c_str());
    }
    MenuPtr->LiMENU.LMItem[count-1] = nullptr;
    MenuPtr->LiMENU.LMenu = new_menu(MenuPtr->LiMENU.LMItem);
    scale_menu(MenuPtr->LiMENU.LMenu, &mrows, &mcols);
    MenuPtr->LiMENU.LMWin = newpad(TaskPtr->WinFullSize(WinPtr->START.TMPWin2,static_cast<int>(count),"H"), TaskPtr->WinFullSize(WinPtr->START.TMPWin2,mcols,"W"));
    wbkgd(MenuPtr->LiMENU.LMWin, COLOR_PAIR(WinPtr->WindowColor.FeBk_Main));
    set_menu_win(MenuPtr->LiMENU.LMenu, MenuPtr->LiMENU.LMWin);
    set_menu_sub(MenuPtr->LiMENU.LMenu, MenuPtr->LiMENU.LMWin);
    set_menu_format(MenuPtr->LiMENU.LMenu, WinPtr->WinSize->HRY()-9, 1); //-3
    set_menu_spacing(MenuPtr->LiMENU.LMenu, 0, 0, 0);
    menu_opts_off(MenuPtr->LiMENU.LMenu, O_SELECTABLE);
    menu_opts_on(MenuPtr->LiMENU.LMenu, O_NONCYCLIC);
    set_menu_fore(MenuPtr->LiMENU.LMenu, COLOR_PAIR(20)|A_BOLD|A_REVERSE);
    set_menu_back(MenuPtr->LiMENU.LMenu, COLOR_PAIR(78)|A_BOLD);
    set_menu_grey(MenuPtr->LiMENU.LMenu, COLOR_PAIR(30));
    set_menu_mark(MenuPtr->LiMENU.LMenu, "");
    post_menu(MenuPtr->LiMENU.LMenu);
}

void ServiceClass::INFOWINDOW(string Name){
    werase(WinPtr->START.TMPWin5);
    wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(WinPtr->WindowColor.FeFo_Info)|A_BOLD,nullptr);
    mvwaddnstr(WinPtr->START.TMPWin4, 1, 1, "STATE:                   " ,-1);
    mvwaddnstr(WinPtr->START.TMPWin4, 2, 1, "LOAD:                    " ,-1);
    mvwaddnstr(WinPtr->START.TMPWin4, 3, 1, "AKTIVE:                  " ,-1); //9
    mvwaddnstr(WinPtr->START.TMPWin4, 4, 1, "SUB:                     " ,-1);
    mvwaddnstr(WinPtr->START.TMPWin4, 1, 26, "DESC:" ,-1);
    mvwaddnstr(WinPtr->START.TMPWin4, 4, 26, "Suche:" ,-1);
    //mvwaddnstr(WinPtr->START.TMPWin4, 6, 1, "                  " ,-1);
    wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(WinPtr->WindowColor.FeFo_Info)|A_BOLD,nullptr);

    for (unsigned long X = 0; X < static_cast<unsigned long>(ServiceList.size());X++){
        if (ServiceList[X].Name.compare(Name)==0) {
            switch (ServiceList[X].state) {
            case UNIT_STATE_ENABLED:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_BAD:
            case UNIT_STATE_DISABLED:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_STATIC:
            case UNIT_STATE_MASKED:
            case UNIT_STATE_GENERATED:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                break;
            case UNIT_STATE_TMP:
            default:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 1, 9, ServiceList[X].Status.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            } // ende status switch
            switch (ServiceList[X].load) {
            case UNIT_LOADSTATE_LOADED:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_LOADSTATE_NOTFOUND:
            case UNIT_LOADSTATE_UNLOAD:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 2, 9, ServiceList[X].Load.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            } // ende load switch
            switch (ServiceList[X].active) {
            case UNIT_ACTIVESTATE_ACTIVE:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_ACTIVESTATE_INACTIVE:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 3, 9, ServiceList[X].Active.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            }
            switch (ServiceList[X].substate) {
            case UNIT_SUBSTATE_RUNNING:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Green)|A_BOLD,nullptr);
                break;
            case UNIT_SUBSTATE_CONNECTED:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Yellow)|A_BOLD,nullptr);
            case UNIT_SUBSTATE_INVALID:
            case UNIT_SUBSTATE_EXITED:
            case UNIT_SUBSTATE_DEAD:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.Red)|A_BOLD,nullptr);
                break;
            default:
                wattr_on(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                mvwaddnstr(WinPtr->START.TMPWin4, 4, 9, ServiceList[X].SubStatus.c_str() ,-1);
                wattr_off(WinPtr->START.TMPWin4, COLOR_PAIR(StateColor.White)|A_BOLD,nullptr);
                break;
            }
            wattr_on(WinPtr->START.TMPWin5, COLOR_PAIR(30)|A_BOLD,nullptr);
            mvwaddnstr(WinPtr->START.TMPWin5, 0, 0, ServiceList[X].Description.c_str() ,-1);
            wattr_off(WinPtr->START.TMPWin5, COLOR_PAIR(30)|A_BOLD,nullptr);
        }
    }
}

void ServiceClass::Statusabfrage(string ausgabestatus) {
    int hoehe;
    int rowy = WinPtr->WinSize->HRY()-4;
    int ROWS = 0;
    int keytab;

    STATUSWIN = newwin(WinPtr->WinSize->HRY()-2, WinPtr->WinSize->WCX()-2, 1, 1);
    wbkgd(STATUSWIN, COLOR_PAIR(WinPtr->WindowColor.FeBk_Help)|A_BOLD);
    box(STATUSWIN, 0,0);

    hoehe = TaskPtr->Zeilen(ausgabestatus.c_str(),WinPtr->WinSize->WCX()-4);
    STATUSINFO = newpad(hoehe, WinPtr->WinSize->WCX()-4);
    wbkgd(STATUSINFO, COLOR_PAIR(WinPtr->WindowColor.FeBk_Help)|A_BOLD);
    STATUSINFO = derwin(STATUSWIN, WinPtr->WinSize->HRY()-4, WinPtr->WinSize->WCX()-4, 1, 1);
    wattr_on(STATUSINFO, COLOR_PAIR(WinPtr->WindowColor.FeFo_Help)|A_BOLD,nullptr);
    mvwaddnstr(STATUSINFO, 0, 0, ausgabestatus.c_str(),-1);
    wattr_off(STATUSINFO, COLOR_PAIR(WinPtr->WindowColor.FeFo_Info)|A_BOLD,nullptr);
    wattr_on(STATUSWIN, COLOR_PAIR(70)|A_BOLD,nullptr);
    mvwaddnstr(STATUSWIN, WinPtr->WinSize->HRY() -3, WinPtr->WinSize->WCX()-15, "[ EXIT F10 ]" ,-1);
    wattr_off(STATUSWIN, COLOR_PAIR(70)|A_BOLD,nullptr);

    wrefresh(STATUSWIN);
    touchwin(STATUSWIN);
    prefresh(STATUSINFO, 0, 0, 0, 0, WinPtr->WinSize->HRY() -4, WinPtr->WinSize->WCX()-4);

    while ((keytab=getch()) != KEY_F(10)) {
        switch (keytab) {
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
        prefresh(STATUSINFO, ROWS, 0, 0, 0, WinPtr->WinSize->HRY() -4, WinPtr->WinSize->WCX()-4);
    }
    if (STATUSINFO){werase(STATUSINFO);delwin(STATUSINFO);}
    if (STATUSWIN){werase(STATUSWIN);delwin(STATUSWIN);}
    redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
    prefresh(MenuPtr->LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY()-8, WinPtr->WinSize->WCX()-2);
}

void ServiceClass::ENDE_NEW() {
    try {
        ServiceList.clear();
        //vector<SERVICES>().swap(MenuPtr->ServiceList);
        vector<SERVICES>(ServiceList).swap (ServiceList);
        clear();
        //###############--Hauptmenu--###############################################
        int E = item_count(MenuPtr->MENEU.HMMenu);
        unpost_menu(MenuPtr->MENEU.HMMenu);
        SAFE_DELETE(MenuPtr->MENEU.HMMenu);
        SAFE_DELETE_ARRAY(MenuPtr->MENEU.HMItem);
        wborder(MenuPtr->MENEU.HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(MenuPtr->MENEU.HMWin,0,E+1);
        delwin(MenuPtr->MENEU.HMWin);
        endwin();
        //###############--Untermenu--###############################################
        E = item_count(MenuPtr->MENEU.UME.UMEMenu);
        unpost_menu(MenuPtr->MENEU.UME.UMEMenu);
        SAFE_DELETE(MenuPtr->MENEU.UME.UMEMenu);
        SAFE_DELETE_ARRAY(MenuPtr->MENEU.UME.UMEItem);
        wborder(MenuPtr->MENEU.UME.UMEWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(MenuPtr->MENEU.UME.UMEWin,0,E+1);
        delwin(MenuPtr->MENEU.UME.UMEWin);
        endwin();

        refresh();
        redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin3));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin3));
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

//##################################################################################
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
    if (MenuPtr->LiMENU.LMItem){unpost_menu(MenuPtr->LiMENU.LMenu);SAFE_DELETE(MenuPtr->LiMENU.LMItem);SAFE_DELETE_ARRAY(MenuPtr->LiMENU.LMItem);}
    if (MenuPtr->LiMENU.LMWin){werase(MenuPtr->LiMENU.LMWin);delwin(MenuPtr->LiMENU.LMWin);endwin();}
    StateColor.Green = 28;
    StateColor.Yellow = 38;
    StateColor.Red = 18;
    StateColor.White = 78;
    unsigned long count = ServiceList.size();
    MenuPtr->LiMENU.LMWin = newpad(static_cast<int>(count), WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));
    wbkgd(MenuPtr->LiMENU.LMWin, COLOR_PAIR(WinPtr->WindowColor.FeBk_Main));

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
    for (int i = 0; i < WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2); i++) {
        if ((i + start) > static_cast<int>(ServiceList.size() - 1)) {
            break;
        }
        SERVICES unit = ServiceList[static_cast<unsigned long>(start + i)];
        if (i == selected) {
            StateColor.SetSignalColor(17, 37, 27, 87);
            AktivName=ServiceList[static_cast<unsigned long>(start + selected)].Name;
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(87)|A_BOLD);
        }
        TableDraw(unit, i);
        wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(87)|A_BOLD);
        StateColor.SetSignalColor(18, 38, 28, 78);
    }
    /*    if (inputFor == INPUT_FOR_LIST) {
    //        drawInfo();
    //    } else {
    //        drawSearch();
    //    }
//    refresh();
   wrefresh(TaskPtr->ClearWindow(MenuPtr->LiMENU.LMWin));*/
    refresh();
    touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
    wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
    prefresh(MenuPtr->LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1, WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));// -2
}

void ServiceClass::TableDraw(SERVICES unit, int y) {
    if (unit.Target.compare(systemctlwahl)==0) {
        //unit.SID = unit.SID++;
        if (unit.Name.size() < static_cast<unsigned long>(WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2))) {
            unit.Name.resize(WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2), ' ');
        }else {
            unit.Name.resize(WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2));
        }
        if (unit.Status.size() <= WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4)) {
            unit.Status.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4), ' ');
        }else {
            unit.Status.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4));
        }
        if (unit.SubStatus.size() <= WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4) ) {
            unit.SubStatus.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4), ' ');
        } else {
            unit.SubStatus.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4));
        }
        if (unit.Active.size() <= WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4) ) {
            unit.Active.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4), ' ');
        }else {
            unit.Active.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4));
        }
        if (unit.Load.size() <= WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4) ) {
            unit.Load.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4), ' ');
        }else {
            unit.Load.resize(WinPtr->WinSize->WinHalfDurch(WinPtr->START.TMPWin2, 4));
        }

        std::string name(unit.Name);

        wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
        mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->RAND-1, "%s", name.c_str());
        wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);

        switch (unit.state) {
        case UNIT_STATE_ENABLED:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, "%s  ", unit.Status.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_STATE_BAD:
        case UNIT_STATE_DISABLED:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, "%s ", unit.Status.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        case UNIT_STATE_STATIC:
        case UNIT_STATE_MASKED:
        case UNIT_STATE_GENERATED:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, "%s   ", unit.Status.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            break;
        case UNIT_STATE_TMP:
        default:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, unit.Status.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+1, "%9s", unit.Status.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.load) {
        case UNIT_LOADSTATE_LOADED:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX() - 11, unit.LoadStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_LOADSTATE_NOTFOUND:
        case UNIT_LOADSTATE_UNLOAD:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX()- 11, unit.LoadStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +11, unit.Load.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX() - 11, unit.LoadStatus.c_str()); // 3 jetzt 9
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.active) {
        case UNIT_ACTIVESTATE_ACTIVE:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX()- 21, unit.ActiveStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_ACTIVESTATE_INACTIVE:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX()- 21, unit.ActiveStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +21, unit.Active.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX() - 11, unit.LoadStatus.c_str()); // 3 jetzt 9
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
        switch (unit.substate) {
        case UNIT_SUBSTATE_RUNNING:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Green)|A_BOLD);
            break;
        case UNIT_SUBSTATE_CONNECTED:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Yellow)|A_BOLD);
        case UNIT_SUBSTATE_INVALID:
        case UNIT_SUBSTATE_EXITED:
        case UNIT_SUBSTATE_DEAD:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str());
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.Red)|A_BOLD);
            break;
        default:
            wattron(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            mvwaddnstr(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2) +31, unit.SubStatus.c_str(), -1);
            //mvwprintw(MenuPtr->LiMENU.LMWin, y, WinPtr->WinSize->WCX_TmpWinCenter(WinPtr->START.TMPWin2)+11, "%10s", unit.SubStatus.c_str()); // 3 jetzt 9
            wattroff(MenuPtr->LiMENU.LMWin, COLOR_PAIR(StateColor.White)|A_BOLD);
            break;
        }
    }
}

void ServiceClass::tabledriver(std::vector<SERVICES> SRVLIST,int key){
    int ps = WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)-1;
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
            ServiceClass::tabledriver(SRVLIST,REQ_UP_ITEM);
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
            ServiceClass::tabledriver(SRVLIST,REQ_DOWN_ITEM);
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
            ServiceClass::tabledriver(SRVLIST,REQ_UP_ITEM);
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
            ServiceClass::tabledriver(SRVLIST,REQ_DOWN_ITEM);
        }
        break;}
    case REQ_FIRST_ITEM:{
        if (start > 0 && selected < ps) { // / 2
            start--;
        } else if (selected > 0) {
            selected--;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::tabledriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_LAST_ITEM:{
        int max = static_cast<int>(SRVLIST.size()-1);
        start = max - ps;
        selected = ps;
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::tabledriver(SRVLIST,REQ_UP_ITEM);
        }
        break;}
    case REQ_NEXT_ITEM:{
        if (start > 0 && selected < ps) { // / 2
            start--;
        } else if (selected > 0) {
            selected--;
        }
        if (SRVLIST[static_cast<unsigned long>(start + selected)].Name.empty()) {
            ServiceClass::tabledriver(SRVLIST,REQ_UP_ITEM);
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
            ServiceClass::tabledriver(SRVLIST,REQ_DOWN_ITEM);
        }
        break;}
    case REQ_TOGGLE_ITEM:{
        break;}
    case REQ_CLEAR_PATTERN:{
        break;}
    case REQ_BACK_PATTERN:{
        if (MenuPtr->PATTER.size()>0) {MenuPtr->PATTER.pop_back(); MenuPtr->PATTER.shrink_to_fit();};
        mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, "                      ",-1);
        mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, MenuPtr->PATTER.c_str(),-1);
        break;}
    case REQ_NEXT_MATCH:{
        int position = 0;
        for (auto unit : ServiceList) {
            if (!unit.Name.empty()) {
                if (unit.Name.rfind(MenuPtr->PATTER.c_str()) != std::string::npos) {
                    lastFound = position;
                    moveTo(position); }
                position++;
            } else {
                continue;
            }
        }
        if (lastFound == 0) {
            MenuPtr->PATTER.clear();
            return;
        }
        lastFound = 0;
        tabledriver(ServiceList,REQ_NEXT_MATCH);
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
            MenuPtr->PATTER.clear();
            mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, "                      ",-1);
            break;}
        //case KEY_ENTER: // Ctrl-M
        case 10: {// Enter
            tabledriver(ServiceList,REQ_NEXT_MATCH);
            break;}
        case KEY_BACKSPACE:{
            if (MenuPtr->PATTER.size()>0) {MenuPtr->PATTER.pop_back(); MenuPtr->PATTER.shrink_to_fit();};
            mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, "                      ",-1);
            mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, MenuPtr->PATTER.c_str(),-1);
            tabledriver(ServiceList,REQ_NEXT_MATCH);
            break;}
        default:{
            if (key > 10 && key < 128) {
                sprintf(searchString,"%c",key);
                MenuPtr->PATTER.append(string(searchString));
                mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, MenuPtr->PATTER.c_str(),-1);
                tabledriver(ServiceList,REQ_NEXT_MATCH);
            }
            break;}
        }
        refresh();
        touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
        touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
        prefresh(MenuPtr->LiMENU.LMWin, 0, 0, 2, 1,
                 WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1,
                 WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));
    }
}

void ServiceClass::drawSearch() {
    /*  * Lets indicate it is a search input   */
    char text[BUFSIZ] = "";
    if (lastFound == 0) {
        sprintf(searchString,"%s",text);
        MenuPtr->PATTER.append(string(searchString));
        //sprintf(text, "%s%s", text, searchString);
    }
    /*   * Draw it using any visible, light color   */
    //drawStatus(1, text, 0);
    mvwaddnstr(WinPtr->START.TMPWin4, 4, 33, MenuPtr->PATTER.c_str(),-1);
}

void ServiceClass::moveTo(int position) {
    start = selected = 0;
    for (int i = 0; i < position; i++) {
        tabledriver(ServiceList,REQ_UP_ITEM);
    }
}

ServiceClass::ServiceClass(){
    systemctlwahl = "service";
}

ServiceClass::~ServiceClass(){

}




