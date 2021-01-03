#include <src/ServiceClass.h>
#include <src/MenuClass.h>
#include <src/WinClass.h>
#include <src/TaskClass.h>
#include <src/Info.h>

using namespace std;

WinClass * WinPtr = new WinClass();
TaskClass * TaskPtr = new TaskClass();
MenuClass * MenuPtr = new MenuClass();
ServiceClass * ServicePtr = new ServiceClass();

void WinClass::StartWin() {
    setlocale(LC_CTYPE,"de_DE.UTF-8");
    setlocale(LC_ALL,"de_DE.UTF-8");
    initscr();
    if (has_colors()==FALSE) { endwin(); printf("Your terminal does not support color\n"); exit(1);}
    start_color();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    //raw();
    //(void) nonl();
    //clear();
    //syncok(stdscr,true);
    //getmaxyx(stdscr,WinSize->HRY,WinSize->WCX);
    WinPtr->AppColor();
    //WinPtr->SetSize();
}

void WinClass::StopWin() {
    delete TaskPtr;
    delete MenuPtr;
    delete ServicePtr;
    delete WinPtr;
    endwin();
    //exit(EXIT_SUCCESS);
}

void WinClass::printInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color, char *sp) {
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

int main (int ac, char **av) {
    try {
        if (ac > 1) {
            fprintf(stdout, ABOUT_INFO, VERSION);
            return 0;
        }
        werase(stdscr);
        WinPtr->StartWin();
        WinPtr->FensterDraw();

        //-------------_DatumUhrZeit_datumuhrzeit_-----------------------------------------------
        std::thread worker(&TaskClass::process_signal, std::ref(TaskPtr), "DateTime");
        worker.detach();

        refresh();
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin1));
        touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin1));
        redrawwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin2));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
        touchwin(TaskPtr->ClearWindow(WinPtr->START.TMPWin4));
        wrefresh(TaskPtr->ClearWindow(WinPtr->START.TMPWin5));
        prefresh(MenuPtr->LiMENU.LMWin, 0, 0, 2, 1, WinPtr->WinSize->HRY_TmpWinReal(WinPtr->START.TMPWin2)+1, WinPtr->WinSize->WCX_TmpWinReal(WinPtr->START.TMPWin2));
        redrawwin(TaskPtr->ClearWindow(MenuPtr->MENEU.HMWin));
        wrefresh(TaskPtr->ClearWindow(MenuPtr->MENEU.HMWin));

        MenuPtr->MenuStart();
        WinPtr->StopWin();

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



