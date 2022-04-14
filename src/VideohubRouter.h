#ifndef VideoRouter
#define VideoRouter

#include <vector>

#include "TelnetClient.h"

struct ChannelStruct {
    std::string name;
    unsigned int channelNum;
    ChannelStruct *source = nullptr;

    bool changedRoute = false;
};

class VideohubRouter {
   public:
    VideohubRouter();
    // VideohubRouter(std::string ip);
    ~VideohubRouter();

    int SetIpAddress(std::string newAddress);

    int GetData();

    int PrintData();

    int ChangeSourceName(unsigned int channel, std::string new_name);
    int ChangeDestinationName(unsigned int channel, std::string new_name);

    int SetRoute(int destination, int source);
    int TakeRoutes();

    std::string GetName();
    int SetNewIpAddress(std::string ip);
    std::string GetIp();

   private:
    std::string m_ipAdress = "127.0.0.1";
    int m_port = 9990;

    std::string *m_dataDump;
    std::vector<std::string> m_dataSet;

    std::string m_name = "name not set";
    u_int sourceCount;
    std::vector<ChannelStruct*> sources;
    u_int destinationCount;
    std::vector<ChannelStruct*> destinations;

    TelnetClient *tClient;

    int SetChannelData();
    std::string SetName();
    int SetChannelCount();
};

#endif  // VideoRouter