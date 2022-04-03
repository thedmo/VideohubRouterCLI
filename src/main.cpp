#include "VideohubRouterCli.h"

int main() {
    bool quit = false;

    std::string userInput;
    ConfigureMenu();

    std::cout << "~~~~VideohubRouter Commandline Interface\nVideohubRouter "
        "Commandline Interface~~~~\n\n"
        << std::endl;

    // Main Loop
    while (!quit) {
        PrintMenu();
        std::cin >> userInput;

        quit = EvaluateUserInput(userInput);
    }
    return 0;
}
