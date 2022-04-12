#ifndef VideoRouter
#define VideoRouter

#include <vector>

#include "TelnetClient.h"

struct Source {
    std::string name;
    unsigned int channelNum;
};

struct Destination {
    std::string name;
    unsigned int channelNum;
    Source *source;
};

struct ChannelStruct {
    std::string name;
    unsigned int channelNum;
    ChannelStruct *source = nullptr;
};

class VideohubRouter {
   public:
    VideohubRouter();
    // VideohubRouter(std::string ip);
    ~VideohubRouter();

    int SetIpAddress(std::string newAddress);

    int GetData();

    int PrintData();

    int ChangeSourceName(int channel, std::string name);
    int ChangeDestinationName(int channel, std::string name);

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
    int FillDataSet();

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