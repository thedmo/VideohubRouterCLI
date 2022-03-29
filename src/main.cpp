#include "VideohubRouter.h"
#include <map>
#include <iostream>
#include <functional>

struct MenuOption {
    int number;
    std::string name;
    std::string description;

    std::function<int()> function;
};

using Menu = std::vector<MenuOption>;

int QuitApplication() {
    std::cout << "Quitting Application" << std::endl;
    return 1;
}

int AddNewRouter() {
    std::cout << "Please enter Ip Adress (IPv4): " << std::endl;
    return 0;
}

MenuOption AddMenuOptionToMenuVector(int number, std::string name, std::string description, std::function<int()> &&function) {
    MenuOption newOption{
        .number = number,
        .name = name,
        .description = description,
        .function = function
    };

    return newOption;
}

void ConfigureMainMenu(Menu &menu) {

    menu.push_back(AddMenuOptionToMenuVector(0, "quit", "Quit application.", &QuitApplication));
    menu.push_back(AddMenuOptionToMenuVector(1, "Add Router", "Add a new router to list of Routers.", &AddNewRouter));
}

void PrintMenu(Menu &menu) {
    std::cout << "What do you want to do?" << std::endl;
    for (auto item : menu) {
        std::cout << item.number << ": " << item.description << "\n";
    }
    std::cout << std::endl;
}

bool EvaluateUserInput(std::string input, Menu &menu) {
    int inputChoice;

    try
    {
        inputChoice = std::stoi(input);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Not a number, please choose a number from the given options:" << '\n';
        return 0;
    }

    for (auto item : menu) {
        if (item.number == inputChoice)
        {
            return item.function();
        }
    }
    std::cout << "No valid choice. Please choose a number from the given options." << std::endl;
    return 0;
}

int main()
{
    Menu menu;

    bool quit = false;

    std::string userInput;
    ConfigureMainMenu(menu);

    std::cout << "VideohubRouter Commandline Interface\nVideohubRouter Commandline Interface\n\n" << std::endl;

    while (!quit) {
        PrintMenu(menu);
        std::cin >> userInput;

        quit = EvaluateUserInput(userInput, menu);
    }
    return 0;
}
