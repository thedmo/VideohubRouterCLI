#ifndef VideoRouterCli
#define VideoRouterCli

#include <functional>
#include <iostream>

#include "VideohubRouter.h"
#include "Menu.h"

// Menu Methods
void QuitApplication();
void AddNewRouter();
void RemoveRouter();
void SelectRouter();
void PrintData();
void SetNewRoute();
void TakeRoutes();
void SetSourceName();
void SetDestinationName();
void ChangeIpAddress();

static std::vector<VideohubRouter *> m_routers;
static VideohubRouter* selected_router;

void AddRouterToList(VideohubRouter *newRouter);
int GetRouterList();

void ConfigureMenu();

namespace vhr {
void StartCli();
}

#endif  // VideoRouterCli