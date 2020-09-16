#include <thread>

#include "database.h"
#include "fmt/ostream.h"
#include "logger.h"
#include "main_window.h"

int main(int, char**) {
    Database::GetInstance().Load();
    LOG_I("main thread id is {}", std::this_thread::get_id());
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