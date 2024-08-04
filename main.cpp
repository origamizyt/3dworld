#include "Views/CLI/MainConsoleView.hpp"
#include "Controllers/CLI/ConsoleController.hpp"
using namespace c3w::controllers::cli;
using namespace c3w::views::cli;

int main() {
    auto controller = ConsoleController::GetInstance();
    MainConsoleView view(controller);
    view.Display();
    return 0;
}