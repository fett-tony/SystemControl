#ifndef MENUCLASS_H
#define MENUCLASS_H

#include <src/TaskClass.h>

//-------Color-Hauptmenue------------------------
struct MenuColor {
    int HaMeFe_HG {78}; //Fenster_Background
    int HaMe_FG {78};   //Hauptmenue_Foreground
    int HaMe_HG {78};   //Hauptmenue_Background
    int HaMe_grey {04}; //Hauptmenue_inaktive
    int UMeFe_HG {87};  //Fenster_Untermenue
    int UMeFe_FG {87};  //Fenster_Untermenue
};
//-------Color-InApp-Menues----------------------
struct InAppColor {
    int IlMeFe_HG = 78; //Fenster_Background
    int IlMe_FG = 71;   //InnLineMenue_Foreground
    int IlMe_HG = 18;   //InnLineMenue_Background
    int IlMe_grey = 18; //InnLineMenue_inaktive
    int IlUMeFe_HG = 87;//Fenster_Untermenue
};

struct HAUPTMENU {
    int            HMID;
    std::string  HMName;
    WINDOW  *HMWin {nullptr};
    MENU   *HMMenu {nullptr};
    ITEM  **HMItem {nullptr};
    //###############################################
    struct UNTERMENU {
        int            UMID;
        std::string UMEName;
        WINDOW *UMEWin {nullptr};
        MENU  *UMEMenu {nullptr};
        ITEM **UMEItem {nullptr};
    }UME;
    void LoescheUME(){
        int E = item_count(UME.UMEMenu);
        unpost_menu(UME.UMEMenu);
        SAFE_DELETE(UME.UMEMenu)
        SAFE_DELETE_ARRAY(UME.UMEItem)
        wborder(UME.UMEWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(UME.UMEWin,0,E+1);
        delwin(UME.UMEWin);
        endwin();
        refresh();
    }
};

struct LISTMENU {
    int                   LMID;
    std::string         LMName;
    WINDOW    *LMWin {nullptr};
    MENU      *LMenu {nullptr};
    ITEM    **LMItem {nullptr};
};

struct APPMENU {
    WINDOW   *AppWin1 {nullptr};
    MENU    *AppMenu1 {nullptr};
    ITEM   **AppItem1 {nullptr};
    WINDOW   *AppWin2 {nullptr};
    MENU    *AppMenu2 {nullptr};
    ITEM   **AppItem2 {nullptr};
};

class MenuClass
{
public:
    //############################variablen#########
    HAUPTMENU                    MENEU;
    int                         MeInAl;
    WINDOW                   *HMTMPWIN;
    MENU                    *HMTMPMENU;
    //##########MENÜ################################
    LISTMENU                    LiMENU;
    int                       LiMeInAl;
    WINDOW                   *LiTMPWIN;
    MENU                    *LiTMPMENU;
    //##############################################
    LISTMENU             NEW_UNIT_MENU;
    int                NEW_UNIT_MeInAl;
    WINDOW            *NEW_UNIT_TMPWIN;
    MENU             *NEW_UNIT_TMPMENU;
    //##############################################
    APPMENU                  InAppMenu;
    MenuColor                  HMcolor;
    InAppColor                 IAcolor;
    std::string PATTER = "";
    void               Hauptmenu(void);
    void              Datei_menu(void);
    void         DaemonType_menu(void);
    void          Systemctl_menu(void);
    void               Info_menu(void);
    MENU   *tmpMe(std::string name, int id);
    WINDOW *tmpWi(std::string name, int id);
    void      fensterwahl(std::string wahl);
    void                    QUIT(void);
    void               MenuStart(void);
    void resize();
    MenuClass();
    ~MenuClass();
};

#endif // MENUCLASS_H
