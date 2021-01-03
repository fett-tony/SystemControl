#ifndef SERVICECLASS_H
#define SERVICECLASS_H

#include <src/TaskClass.h>

//enum _INPUT_FOR {
//    INPUT_FOR_LIST,
//    INPUT_FOR_SEARCH
//};

#define ERR_PREFIX "Failed: "
#define SYSV_INSTALL_EXEC "/lib/systemd/systemd-sysv-install"

enum {
    UNIT_STATE_DISABLED = 0x01,
    UNIT_STATE_ENABLED = 0x02,
    UNIT_STATE_STATIC = 0x03,
    UNIT_STATE_BAD = 0x04,
    UNIT_STATE_MASKED = 0x05,
    UNIT_STATE_TMP = 0x06,
    UNIT_STATE_GENERATED = 0x07,
    UNIT_SUBSTATE_RUNNING = 0x08,
    UNIT_SUBSTATE_CONNECTED = 0x09,
    UNIT_SUBSTATE_INVALID = 0x0a,
    UNIT_SUBSTATE_TMP = 0x0b,
    UNIT_SUBSTATE_DEAD = 0x0c,
    UNIT_SUBSTATE_EXITED = 0x0d,
    UNIT_LOADSTATE_LOADED = 0x0e,
    UNIT_LOADSTATE_NOTFOUND = 0x0f,
    UNIT_LOADSTATE_UNLOAD = 0x10,
    UNIT_ACTIVESTATE_ACTIVE = 0x11,
    UNIT_ACTIVESTATE_INACTIVE = 0x12
};

enum STATE_FLAGS {
    STATE_FLAGS_ENABLE,
    STATE_FLAGS_DISABLE,
    STATE_FLAGS_DISABLE_ISO
};

struct SignalColor {
    int Red     {18}; //Error or inaktive
    int Yellow  {38}; //Warn or fails
    int Green   {28}; //infoS
    int White   {78}; //all all right
    void SetSignalColor(int RED = 18, int YELLOW = 38, int GREEN = 28, int WHITE = 78){Red = RED; Yellow = YELLOW; Green = GREEN; White = WHITE;};
};

typedef struct SERVICES SERVICES;
struct SERVICES {
    int SID;
    std::string Name;
    std::string Target; //(){return Name.substr(Name.find(".")+1,Name.length());};
    std::string Path;
    std::string Description;
    int state;
    std::string Status;
    int load;
    std::string Load;
    int active;
    std::string Active;
    int substate;
    std::string SubStatus;
    SERVICES* next;
};


class ServiceClass
{
public:
    ServiceClass();
    ~ServiceClass();
    WINDOW                  *STATUSWIN;
    WINDOW                 *STATUSINFO;
    WINDOW                *ServiceInfo;
    std::string          systemctlwahl;
    void        ServiceFensterDesign();
    void             ServiceListFill();
    void                ServiceListe();
    void  INFOWINDOW(std::string Name);
    void Statusabfrage(std::string ausgabestatus);
    void                    ENDE_NEW();
    int         StartServiceControll();
    //##########MENÜ################################
    std::vector<SERVICES>  ServiceList;
    WINDOW              *ListMenuPanel;
    MENU                     *ListMenu;
    ITEM                **ListMenuItem;
    //#####################################################
    SignalColor StateColor;
    char searchString[BUFSIZ] = "";
    unsigned char inputFor = 0;
    int lastFound = 0;
    int selected = 0;
    int start = 0;
    //unsigned long selected = 0;
    //unsigned long start = 0;
    std::string AktivName {""};
    void tabledriver(std::vector<SERVICES> SRVLIST,int key);
    void SetStateOption(); //SERVICES unit
    void TableDraw(SERVICES unit, int y);
    void TableMoveRow();
    void BuildWin();
    void searchInput();
    void drawSearch();
    void moveTo(int position);

};



#endif // SERVICECLASS_H
