
#include "VideohubRouterCli.h"

void AddNewRouter() {
    VideohubRouter *newRouter = new VideohubRouter();

    std::string newIp;
    std::cout << "Please enter Ip Adress (IPv4): ";
    std::cin >> newIp;

    int result = newRouter->SetIpAddress(newIp);

    if (result != 0) {
        std::cout << "invalid ip.. aborting" << std::endl;
    }
    else {
        std::cout << "adding new Router to List" << std::endl;
        AddRouterToList(newRouter);
    }
}

void RemoveRouter() {
    std::cout << "Not implemented yet." << std::endl;
}

void SelectRouter() {
    std::cout << "Available Devices: " << std::endl;
    for (size_t i = 0; i < m_routers.size(); i++) {
        std::cout << i << ": " << m_routers[i]->GetIp() << std::endl;
    }
}

void PrintData() {
    std::cout << "Not implemented yet." << std::endl;
}

void SetNewRoute() {
    std::cout << "Not implemented yet." << std::endl;
}

void TakeRoutes() {
    std::cout << "Not implemented yet." << std::endl;
}

void SetSourceName() {
    std::cout << "Not implemented yet." << std::endl;
}

void SetDestinationName() {
    std::cout << "Not implemented yet." << std::endl;
}

void ChangeIpAddress() {
    std::cout << "Not implemented yet." << std::endl;
}

void AddRouterToList(VideohubRouter *newRouter) {
    m_routers.push_back(newRouter);
}

void ConfigureMenu(Menu *menu) {

    menu->AddEntry("ar", "Add a new router to list of Routers.", AddNewRouter);
    menu->AddEntry("sr", "select a Router from list of added devices.", SelectRouter);
    menu->AddEntry("ip", "Set new Ip Address on selected device", ChangeIpAddress);
    menu->AddEntry("print", "print all data of selected device.", PrintData);
    menu->AddEntry("Set new route", "set new route on selected device.", SetNewRoute);
    menu->AddEntry("take", "Take all set routes at once", SetNewRoute);
    menu->AddEntry("ns", "set a new name on a source of selected device.", SetSourceName);
    menu->AddEntry("nd", "Set a new name on a destination of selected device.", SetDestinationName);
    menu->AddEntry("rr", "Remove a Router from the routers list.", RemoveRouter);
}

namespace vhr {
void StartCli() {
    std::cout << "~~~~VideohubRouter Commandline Interface\nVideohubRouter "
        "Commandline Interface~~~~\n\n";


    Menu *mainMenu = new Menu("Cli");
    ConfigureMenu(mainMenu);
    mainMenu->EnterMenu();
}
}  // namespace vhr
