#ifndef VideoRouterCli
#define VideoRouterCli

#include <functional>
#include <iostream>

#include "VideohubRouter.h"


using MenuFunction = std::function<int()>;

struct MenuOption {
    int number;
    std::string name;
    std::string description;
    MenuFunction method;
};

using Menu = std::vector<MenuOption>;
static Menu m_menu;

//Menu Methods
int QuitApplication();
int AddNewRouter();
int RemoveRouter();
int SelectRouter();
int PrintData();
int SetNewRoute();
int SetSourceName();
int SetDestinationName();
int ChangeIpAddress();

static std::vector<VideohubRouter> m_routers;
int AddRouterToList(VideohubRouter &newRouter);
int GetRouterList();

MenuOption AddMenuEntry(int number, std::string name,
    std::string description, MenuFunction method);


void ConfigureMenu();
void PrintMenu();
bool EvaluateUserInput(std::string input);

#endif //VideoRouterCli