
#include "VideohubRouterCli.h"

// Static Methods
int QuitApplication() {
    std::cout << "Quitting Application" << std::endl;
    return 1;  // returns true to quit
}

int AddNewRouter() {
    VideohubRouter * newRouter = new VideohubRouter();

    std::string newIp;
    std::cout << "Please enter Ip Adress (IPv4): ";
    std::cin >> newIp;

    int result = newRouter->SetIpAddress(newIp);

    if (result != 0) {
        std::cout << "invalid ip.. aborting" << std::endl;
        return 0;
    } else {
        std::cout << "adding new Router to List" << std::endl;
        AddRouterToList(newRouter);
    }
    return 0;
}

int RemoveRouter() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int SelectRouter() {
    // std::cout << "Not implemented yet." << std::endl;

    std::cout << "Available Devices: " << std::endl;
    for (size_t i = 0; i < m_routers.size(); i++) {
        std::cout << i << ": " << m_routers[i]->GetIp() << std::endl;
    }


    return 0;
}

int PrintData() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int SetNewRoute() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int TakeRoutes() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int SetSourceName() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int SetDestinationName() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int ChangeIpAddress() {
    std::cout << "Not implemented yet." << std::endl;
    return 0;
}

int AddRouterToList(VideohubRouter * newRouter) {
    m_routers.push_back(newRouter);
    return 0;
}

// Menu
MenuOption AddMenuEntry(int number, std::string name, std::string description,
                        MenuFunction method) {
    MenuOption newOption{.number = number,
                         .name = name,
                         .description = description,
                         .method = method};

    return newOption;
}

// Add Menuentries to List of options
void ConfigureMenu() {
    m_menu.push_back(
        AddMenuEntry(0, "quit", "Quit application.", QuitApplication));
    m_menu.push_back(AddMenuEntry(
        1, "Add Router", "Add a new router to list of Routers.", AddNewRouter));
    m_menu.push_back(AddMenuEntry(2, "Select Router",
                                  "select a Router from list of added devices.",
                                  SelectRouter));
    m_menu.push_back(AddMenuEntry(3, "Set Ip Address",
                                  "Set new Ip Address on selected device",
                                  ChangeIpAddress));
    m_menu.push_back(AddMenuEntry(
        4, "Print data", "print all data of selected device.", PrintData));
    m_menu.push_back(AddMenuEntry(
        5, "Set new route", "set new route on selected device.", SetNewRoute));
    m_menu.push_back(AddMenuEntry(6, "Take set routes.",
                                  "Take all set routes at once", SetNewRoute));
    m_menu.push_back(AddMenuEntry(
        7, "Set Source Name", "set a new name on a source of selected device.",
        SetSourceName));
    m_menu.push_back(
        AddMenuEntry(8, "Set Destination name",
                     "Set a new name on a destination of selected device.",
                     SetDestinationName));
    m_menu.push_back(AddMenuEntry(9, "Remove Router",
                                  "Remove a Router from the routers list.",
                                  RemoveRouter));
}

// present possible options to user
void PrintMenu() {
    std::cout << "\nWhat do you want to do?" << std::endl;
    for (auto item : m_menu) {
        std::cout << item.number << ": " << item.description << "\n";
    }
    std::cout << std::endl;
}

bool EvaluateUserInput(std::string input) {
    // std::system("cls");

    int inputChoice;

    try {
        inputChoice = std::stoi(input);
    } catch (const std::exception &e) {
        std::cerr << "Not a number, please choose a number from "
                     "the given options:"
                  << '\n';
        return 0;
    }

    for (auto item : m_menu) {
        if (item.number == inputChoice) {
            std::cout << item.description << std::endl;
            return item.method();
        }
    }

    std::cout << "No valid choice. Please choose a number from the given "
                 "options."
              << std::endl;
    return 0;
}

namespace vhr {
void MainLoop() {
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
}
}  // namespace vhr
