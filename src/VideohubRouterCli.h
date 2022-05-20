#ifndef VideoRouterCli
#define VideoRouterCli


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
static VideohubRouter *selected_router;

void AddRouterToList(VideohubRouter *newRouter);
int GetRouterList();

void ConfigureMenu();
void SelectRouterFromList(unsigned int num);

namespace vhr {
void StartCli();
}

#endif  // VideoRouterCli