#include <ServiceClass.h>
//#include <MenuClass.h>
//#include <WinClass.h>
#include <MenuWinClass.h>
#include <TaskClass.h>
#include <Info.h>

using namespace std;

TaskClass *TaskClass_TC = new TaskClass();
//MenuClass *MenuPtr_TC = new MenuClass();
ServiceClass *ServiceClass_TC = new ServiceClass();
//WinClass *WinPtr_TC = new WinClass();
MenuWinClass *MenuWinClass_TC = new MenuWinClass();

volatile int signal_flag;
/*##########################################################################*/
int TaskClass::ZahlenWerk(int zahlen, string i, int max) {
    int tmp = 0;
    if (strcmp(i.c_str(), "++") == 0) {
        if (zahlen >= max) {
            tmp = 1;
        } else if (zahlen == 0) {
            tmp = 1;
        } else if (zahlen > 0) {
            tmp = ++zahlen;
        } else if (zahlen < max) {
            tmp = ++zahlen;
        }
    } else if (strcmp(i.c_str(), "--") == 0) {
        if (zahlen <= 0) {
            tmp = max;
        } else if (zahlen == 1) {
            tmp = max;
        } else if (zahlen > 1) {
            tmp = --zahlen;
        } else if (zahlen <= max) {
            tmp = --zahlen;
        }
    } else {
        tmp = 1;
    }
    return tmp;
}
int TaskClass::Zeilen(string data, int maxbreite) {
    int rownr = 0;
    double zeiBr = (data.length() / static_cast<double>(maxbreite));
    int zeiBr2;
    stringstream datast(data);
    string line;
    for (rownr = 0; std::getline(datast, line); ++rownr) {}
    zeiBr2 = static_cast<int>(ceil(zeiBr));
    return (rownr + zeiBr2);
}
std::vector<std::string> TaskClass::StringTeiler(const std::string& str, char delimiter) {
    std::istringstream is(str);
    std::vector<std::string> result;
    for (std::string cur; std::getline(is, cur, delimiter); result.push_back(cur));
    return result;
}
string TaskClass::TERM_AUSGABE(string cmd) {
    //cmd = "systemctl list-unit-files -t service | grep '.service' | awk '{$1=$1};1' | sort";
    string data;
    FILE* stream;
    char buffer[BUFSIZE];
    cmd.append(" 2>/dev/null"); //2>&1
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, BUFSIZE, stream) != nullptr) {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    memset(buffer, 0, BUFSIZE);
    return data;
}
WINDOW* TaskClass::ClearWindow(WINDOW* TEMPWINDOW) {
    clearok(TEMPWINDOW, true);
    return TEMPWINDOW;
}
int TaskClass::WinFullSize(WINDOW* TmpWin, int WHCRXY, string WorH) {
    if (WorH.compare("W") == 0) {
        if (MenuWinClass_TC->START.WinSize.WCX_TmpWinReal(TmpWin) <= WHCRXY) {
            return WHCRXY;
        } else {
            return MenuWinClass_TC->START.WinSize.WCX_TmpWinReal(TmpWin);
        }
    } else if (WorH.compare("H") == 0) {
        if (MenuWinClass_TC->START.WinSize.HRY_TmpWinReal(TmpWin) <= WHCRXY) {
            return WHCRXY;
        } else {
            return MenuWinClass_TC->START.WinSize.HRY_TmpWinReal(TmpWin);
        }
    }
}

/*##########################################################################*/
TaskClass::TaskClass() {
    //TaskClass::DateTime.TIMEFIELD(MenuPtr->MENEU.HMWin,MenuWinClass_TC->WinSize.WCX);
}
TaskClass::~TaskClass() {

}
/*##########################################################################*/
