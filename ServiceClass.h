#ifndef SERVICECLASS_H
#define SERVICECLASS_H

#include <TaskClass.h>
#include <MenuWinClass.h>
#include <Info.h>

//enum _INPUT_FOR {
//    INPUT_FOR_LIST,
//    INPUT_FOR_SEARCH
//};

#define ERR_PREFIX "Failed: "
#define SYSV_INSTALL_EXEC "/lib/systemd/systemd-sysv-install"

enum SeaReq { REQ_RIGHT, REQ_LEFT, REQ_DEL_DC, REQ_DEL_BACKSPACE, REQ_INS_DEFAULT};
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
    void SetSignalColor(int RED = 18, int YELLOW = 38, int GREEN = 28, int WHITE = 78) {Red = RED; Yellow = YELLOW; Green = GREEN; White = WHITE;};
};

//typedef struct SERVICES SERVICES;
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
};

class ServiceClass {
public:
    /*#####################################################*/
    vector<SERVICES> ServiceList;
    WINDOW *STATUSWIN;
    WINDOW *STATUSINFO;
    string  systemctlwahl;
    /*#####################################################*/
    SignalColor StateColor;
    char searchString[BUFSIZ] = "";
    unsigned char inputFor = 0;
    int lastFound = 0;
    int selected  = 0;
    int start     = 0;
    string AktivName {""};
    /*#####################################################*/
    void ServiceListFill();
    void ServiceListe();
    void INFOWINDOW(string Name);
    void Statusabfrage(string ausgabestatus);
    void ENDE();
    /*#####################################################*/
    void SetStateOption(); /*SERVICES unit*/
    void BuildWin();
    void TableMoveRow();
    void TableDraw(SERVICES unit, int y);
    void TableDriver(vector<SERVICES> SRVLIST, int key);
    void moveTo(int position);
    void searchInput();
    void drawSearch();
    string SearchDriver(SeaReq drv, WINDOW *Win, int Key, string Search, int Posi);
    /*#####################################################*/
    ServiceClass();
    ~ServiceClass();
};



#endif // SERVICECLASS_H
