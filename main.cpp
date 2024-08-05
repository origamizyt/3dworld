#include "Views/CLI/MainConsoleView.hpp"
#include "Controllers/CLI/ConsoleController.hpp"
using namespace C3w::Controllers::Cli;
using namespace C3w::Views::Cli;

int main() {
    auto controller = ConsoleController::GetInstance();
    MainConsoleView view(controller);
    view.Display();
    return 0;
}