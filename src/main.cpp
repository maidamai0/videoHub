#include "logger.h"
#include "main_window.h"

int main(int, char**) {
    //  make sure logger is created at the first time.
    Logger::GetInstance();
    auto& main_window = MainWindow::GetInstance();
    main_window.Run();
}

#ifdef _WIN32

// clang-format off
#include <Windows.h>
#include <WinBase.h>
// clang-format on

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main(__argc, __argv);
}
#endif