#include <VideohubRouterCli.h>

// METHODS
void AddNewRouter() {
    std::string newIp;
    std::cout << "Please enter Ip Adress (IPv4): ";
    std::cin >> newIp;



    VideohubRouter *newRouter = new VideohubRouter(newIp, feed);
    if (!feed.Ok()) {
        PrintFeedback();

        std::cout << "Could not add new device" << std::endl;

        if (newRouter->Get_Zombie_State())
        {
            delete newRouter;
            std::cout << "Removed faulty device" << std::endl;
        }
    }
    else {
        AddRouterToList(newRouter);
        selected_router = newRouter;
        std::cout << "Added and selected new router." << std::endl;
    }
}

void RemoveRouterAt(int index) {
    delete m_routers[index];
    m_routers.erase(m_routers.begin() + index);
}

void RemoveRouter() {
    if (m_routers.empty()) {
        feed.Set_Feedback(-1, "no routers in list to remove");
        PrintFeedback();
        return;
    }

    for (size_t i = 0; i < m_routers.size(); i++)
    {

        if (m_routers[i] == selected_router) {
            RemoveRouterAt(i);


            selected_router = nullptr;
            feed.Set_Feedback(0, "removed selected router.");
            PrintFeedback();
        }

    }

    SelectRouterFromList(0);
}

void SelectRouter() {
    if (m_routers.size() <= 0) {
        feed.Set_Feedback(-1, "No Router to be selected in Routers list. Add one first.");
        PrintFeedback();
        return;
    }

    std::cout << "Available Devices: " << std::endl;
    for (size_t i = 0; i < m_routers.size(); i++) {
        std::cout << i << ": " << m_routers[i]->GetIp() << ", "
            << m_routers[i]->GetName() << std::endl;
    }

    std::cout << "Type in number of router to select: ";
    std::string input;
    std::cin >> input;
    int inputChoice;

    try {
        inputChoice = std::stoi(input);
    }
    catch (const std::exception &e) {
        feed.Set_Feedback(-1, "No valid input." + std::string(e.what()));
        PrintFeedback();
        return;
    }

    if (m_routers.size() - 1 < inputChoice)
    {
        feed.Set_Feedback(-1, "Number too high. try one less");
        PrintFeedback();
        return;
    }


    SelectRouterFromList(inputChoice);
}

void SelectRouterFromList(unsigned int num) {
    if (m_routers.empty()) {
        selected_router = nullptr;
        feed.Set_Feedback(-1, "No Router to be selected in Routers list. Add one first.");
        PrintFeedback();
        return;
    }

    selected_router = m_routers.at(num);
    std::cout << "Selected: " << selected_router->GetIp() << ", "
        << selected_router->GetName() << std::endl;
}

void PrintData() {
    if (selected_router == nullptr) {
        std::cerr << "no router selected. please select a device first."
            << std::endl;
        return;
    }

    std::cout << selected_router->GetDataString() << std::endl;
}

void SetNewRoute() {
    std::string destination, source;

    int destinationNum, sourceNum;

    std::cout << "Please Type destination: " << std::endl;
    std::cin >> destination;
    try {
        destinationNum = std::stoi(destination);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Type sourcenumber: " << std::endl;
    std::cin >> source;
    try {
        sourceNum = std::stoi(source);
    }
    catch (const std::exception &e) {
        std::cerr << std::string(e.what()) << std::endl;
    }

    ;
    feed = selected_router->SetRoute(sourceNum, destinationNum);
    PrintFeedback();
}

void TakeRoutes() {
    feed = selected_router->TakeRoutes();
    PrintFeedback();
}

void SetSourceName() {
    std::cout << "type number of source to be renamed: " << std::endl;
    std::string user_input;
    unsigned int channel;
    std::cin >> user_input;
    try {
        channel = std::stoi(user_input);
    }
    catch (const std::exception &e) {
        std::cerr << "Not a Number: " << e.what() << '\n';
        return;
    }
    user_input.clear();
    std::cout << "Type in new name for this channel: ";
    std::cin.ignore();
    std::getline(std::cin, user_input);

    feed = selected_router->ChangeSourceName(channel, user_input);
    PrintFeedback();
}

void SetDestinationName() {
    std::cout << "type number of Destination to be renamed: " << std::endl;
    std::string user_input;
    unsigned int channel;
    std::cin >> user_input;
    try {
        channel = std::stoi(user_input);
    }
    catch (const std::exception &e) {
        std::cerr << "Not a Number: " << e.what() << '\n';
        return;
    }
    std::cout << "Type in new name for this channel: ";
    std::cin.ignore();
    std::getline(std::cin, user_input);

    feed = selected_router->ChangeDestinationName(channel, user_input);
    PrintFeedback();
}

void ChangeIpAddress() {
    std::string newIp;
    std::cout << "Please enter Ip Adress (IPv4): ";
    std::cin >> newIp;

    feed = selected_router->SetIpAddress(newIp);
    PrintFeedback();
}

void AddRouterToList(VideohubRouter *newRouter) {
    m_routers.push_back(newRouter);
}

// SET UP MENU
void ConfigureMenu(Menu *menu) {
    menu->AddEntry("a", "Add a new router to list of Routers.", AddNewRouter);
    menu->AddEntry("s", "select a Router from list of added devices.",
        SelectRouter);
    menu->AddEntry("ip", "Set new Ip Address on selected device",
        ChangeIpAddress);
    menu->AddEntry("p", "print all data of selected device.", PrintData);
    menu->AddEntry("r", "set new route on selected device.", SetNewRoute);
    menu->AddEntry("t", "Take all set routes at once", TakeRoutes);
    menu->AddEntry("ns", "set a new name on a source of selected device.",
        SetSourceName);
    menu->AddEntry("nd", "Set a new name on a destination of selected device.",
        SetDestinationName);
    menu->AddEntry("rm", "Remove a Router from the routers list.",
        RemoveRouter);
}

void PrintFeedback() {
    std::cout << feed.Get_Result() << ": " << feed.Get_Message() << std::endl;
}

// ENTER APPLICATION
namespace vhr {
void StartCli() {
    std::cout << "~~~~VideohubRouter Commandline Interface\nVideohubRouter "
        "Commandline Interface~~~~\n\n";

    Menu *mainMenu = new Menu("Cli");
    ConfigureMenu(mainMenu);
    mainMenu->EnterMenu();
}
}  // namespace vhr
