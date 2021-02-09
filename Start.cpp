#include <ServiceClass.h>
//#include <MenuClass.h>
//#include <WinClass.h>
#include <MenuWinClass.h>
#include <TaskClass.h>
#include <Info.h>

using namespace std;

TaskClass * TaskClassS = new TaskClass();
ServiceClass * ServiceClassS = new ServiceClass();
MenuWinClass *MenuWinClassS = new MenuWinClass();

int main (int argc, char* argv[]) {
//try {
    if (argc > 1) {
        if (string(argv[1]).compare("-h")) {
            cout << ABOUT_INFO << " " << VERSION << endl;
            return 0;
            exit(EXIT_SUCCESS);
        } else {
            //fn = string(argv[1]);
            //ed = Editor(fn);
        }
    }

    int Key = 0;
    werase(stdscr);
    MenuWinClassS->StartWin();
    signal(SIGWINCH, MenuWinClass::ResizeHandler);
    //-------------_DatumUhrZeit_datumuhrzeit_-----------------------------------------------
    //std::thread worker(&TaskClass::process_signal, std::ref(TaskPtr), "DateTime");
    //worker.detach();
    MenuWinClass::SetWinSize();
    MenuWinClassS->FensterDraw();

    refresh();
    wrefresh(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin1));
    touchwin(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin1));
    redrawwin(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin2));
    wrefresh(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin2));
    touchwin(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin2));
    wrefresh(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin3));
    touchwin(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin3));
    prefresh(MenuWinClass::START.TMPWin4, 0, 0, 2, 1, MenuWinClass::START.HRYw4() + 1, MenuWinClass::START.WCXw4());
    prefresh(MenuWinClass::START.TMPWin5, 0, 0, MenuWinClass::START.HRY()-4,
             MenuWinClass::START.WCX()-46, MenuWinClass::START.HRYw5(), MenuWinClass::START.WCXw5());
    redrawwin(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin1));
    wrefresh(TaskClassS->ClearWindow(MenuWinClass::START.TMPWin1));

    do { Key = MenuWinClass::MenuStart(Key); if (Key == KEY_F(10)) { break; } } while ((Key = getch()) != KEY_F(10));

    ServiceClassS->ENDE();
    MenuWinClassS->StopWin();

//    } catch (const NCursesException *e) { endwin(); std::cerr << e->message << std::endl; cout << e->errorno;
//    } catch (const NCursesException &e) { endwin(); std::cerr << e.message << std::endl; cout << e.errorno;
//    } catch (const std::exception &e) { endwin(); std::cerr << "Exception: " << e.what() << std::endl; cout << EXIT_FAILURE; }
}
