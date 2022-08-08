#ifndef VideoRouterCli
#define VideoRouterCli


#include <VideohubRouter.h>
#include <Menu.h>
#include <Feedback.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

void PrintFeedback();

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

void ConfigureMenu();
void SelectRouterFromList(unsigned int num);
void RemoveRouterAt(int index);

static Feedback feed;

namespace vhr {
void StartCli();
}

#endif  // VideoRouterCli