#include <src/ServiceClass.h>
#include <src/MenuClass.h>
#include <src/WinClass.h>
#include <src/TaskClass.h>
#include <src/Info.h>

using namespace std;

//extern class TaskClass * TaskPtr;
extern class MenuClass * MenuPtr;
extern class ServiceClass * ServicePtr;
extern class WinClass * WinPtr;
extern class ServiceTableClass * TablePtr;
volatile int signal_flag;

//####################################################################
//eigenes zählwerk um von forn an fangen zu können
//aktuelle zahl, string ob + oder -, maximale höchste zahl
int TaskClass::ZahlenWerk(int zahlen, string i, int max) {
    int tmp = 0;
    if (strcmp(i.c_str(),"++")==0){
        if(zahlen>=max){
            tmp = 1;
        }else if(zahlen==0){
            tmp = 1;
        }else if (zahlen>0){
            tmp = ++zahlen;
        }else if (zahlen<max){
            tmp = ++zahlen;
        }
    }else if(strcmp(i.c_str(),"--")==0){
        if(zahlen<=0){
            tmp = max;
        }else if (zahlen==1){
            tmp = max;
        }else if (zahlen>1){
            tmp = --zahlen;
        }else if(zahlen<=max){
            tmp = --zahlen;
        }
    }else{
        tmp = 1;
    }
    return tmp;
}

int TaskClass::ZahlenBerechnen(int posa, RANGE range, string wahl) {
    int tmp;
    if (wahl.compare("+") == 0){
        posa++;
    }else if (wahl.compare("-") == 0){
        posa--;
    }

    if (posa >= range.min && posa <= range.max){
        tmp = ((posa - range.min) + range.min);
    }else if (posa >= range.min && posa > range.max){
        tmp = (posa - range.max);// + range.min;
        while(tmp > range.max){
            tmp = (tmp - range.max);// + range.min;
        }
    }else if (posa < range.min && posa <= range.max){
        tmp = range.max + posa;
        while(tmp < range.min){
            if(tmp == 0){tmp = range.max;}
            else{tmp = range.max + tmp;}
        }
    }else if (posa == 0){
        tmp = range.max;
    }else{tmp = posa;}

    return tmp;
}

int TaskClass::RangeZahlenWerk(int mina, int posa, int maxa, string wahl){
    vector<RANGE> list;
    int included;
    RANGE range;

    range.min = mina;
    range.max = maxa;
    range.count();
    range.range = 1;
    list.push_back(range);

    do {
        included = TaskClass::ZahlenBerechnen(posa, range, wahl);
    }while (included > range.max);
    return included;
}

int TaskClass::Zeilen(string data, int maxbreite){
    int rownr = 0;
    double zeiBr = (data.length() / static_cast<double>(maxbreite));
    int zeiBr2;
    stringstream datast(data);
    string line;
    for (rownr = 0; std::getline(datast, line); ++rownr){}
    zeiBr2 = static_cast<int>(ceil(zeiBr));
    return (rownr + zeiBr2);
}

std::vector<std::string> TaskClass::StringTeiler(const std::string& str, char delimiter) {
    std::istringstream is(str);
    std::vector<std::string> result;
    for(std::string cur; std::getline(is, cur, delimiter); result.push_back(cur));
    return result;
}
//##########################################################################
//void TaskClass::centerplace(int hoehe, int weite) {
//    //    WinPtr->halb_XC = static_cast<int>(roundf(WinPtr->WinSize.WCX/2));
//    //    WinPtr->halb_YR = static_cast<int>(roundf(WinPtr->WinSize.HRY/2));
//    WinPtr->WinSize->Center_HRY = static_cast<int>(roundf(WinPtr->WinSize->halb_HRY() - (hoehe/2)));
//    WinPtr->WinSize->Center_WCX = static_cast<int>(roundf(WinPtr->WinSize->halb_WCX() - (weite/2)));
//}

string TaskClass::TERM_AUSGABE(string cmd) {
    //cmd = "systemctl list-unit-files -t service | grep '.service' | awk '{$1=$1};1' | sort";
    string data;
    FILE * stream;
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

WINDOW *TaskClass::ClearWindow(WINDOW *TEMPWINDOW) {
    clearok(TEMPWINDOW,true);
    return TEMPWINDOW;
}

void TaskClass::ClearScreen() {
    if (!cur_term) {
        int result;
        setupterm( nullptr, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }
    putp(tigetstr("clear"));
}

//NO_RETURN
void TaskClass::TermQuit(int sig) {
    UNUSED(sig);
    TaskClass::ConfigDateiList.clear();
    vector<string>().swap(TaskClass::ConfigDateiList);
    TaskClass::DeletAllWin("Ende");
    clear();
    raise(SIGTERM);
    exit(EXIT_SUCCESS);
}

void TaskClass::DeletAllWin(const char *name) {
    try {
        if (strcmp(name,"Ende")==0){
            if (WinPtr->START.TMPWin1){
                werase(WinPtr->START.TMPWin1);
                delwin(WinPtr->START.TMPWin1);
                endwin();
            }
            if (WinPtr->START.TMPWin2){
                werase(WinPtr->START.TMPWin2);
                delwin(WinPtr->START.TMPWin2);
                endwin();
            }
            if (WinPtr->START.TMPWin3){
                werase(WinPtr->START.TMPWin3);
                delwin(WinPtr->START.TMPWin3);
                endwin();
            }
            if (WinPtr->START.TMPWin4){
                werase(WinPtr->START.TMPWin4);
                delwin(WinPtr->START.TMPWin4);
                endwin();
            }
            if (WinPtr->START.TMPWin5){
                werase(WinPtr->START.TMPWin5);
                delwin(WinPtr->START.TMPWin5);
                endwin();
            }
            endwin();
        }
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

//#############################################################################
int TaskClass::WinFullSize(WINDOW * TmpWin, int WHCRXY, string WorH){
    if (WorH.compare("W")==0) {
        if (WinPtr->WinSize->WCX_TmpWinReal(TmpWin) <= WHCRXY) {
            return WHCRXY;
        } else {
            return WinPtr->WinSize->WCX_TmpWinReal(TmpWin);
        }
    } else if (WorH.compare("H")==0) {
        if (WinPtr->WinSize->HRY_TmpWinReal(TmpWin) <= WHCRXY) {
            return WHCRXY;
        } else {
            return WinPtr->WinSize->HRY_TmpWinReal(TmpWin);
        }
    }
}


void TaskClass::set_flag(int signal) {
    signal_flag = signal;
}

void TaskClass::process_signal(std::string command) {
    try {
        while (signal_flag != SIGTERM) {
            //MenuPtr->MENEU.HMWin
            DateTime.TIMEFIELD(WinPtr->START.TimeWin,20); //WinPtr->WinSize->WCX_TmpWin(WinPtr->START.TimeWin));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        cout << EXIT_FAILURE;
    }
}

void TaskClass::Resize_Handler(int sig) {
    try {
        while (signal_flag != SIGTERM) {
            WinPtr->ChangeSize();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        cout << EXIT_FAILURE;
    }
}

TaskClass::TaskClass(){
    //TaskClass::DateTime.TIMEFIELD(MenuPtr->MENEU.HMWin,WinPtr->WinSize.WCX);
}

TaskClass::~TaskClass(){

}
