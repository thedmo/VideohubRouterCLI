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
    VideohubRouter() = delete;
    VideohubRouter(std::string ip);
    ~VideohubRouter();

    int SetIpAddress(std::string newAddress);
    
    std::string GetDataString();

    int ChangeSourceName(unsigned int channel, std::string new_name);
    int ChangeDestinationName(unsigned int channel, std::string new_name);

    int SetRoute(int destination, int source);
    int TakeRoutes();

    std::string GetName();

    std::string GetIp();

private:
    std::string m_ipAdress = "127.0.0.1";
    int m_port = 9990;

    std::string m_init_data_dump;
    std::string m_routes_dump, m_dest_labels_dump, m_source_labels_dump, m_device_dump;

    std::string m_name = "name not set";
    u_int sourceCount;
    std::vector<ChannelStruct *> m_sources;
    u_int destinationCount;
    std::vector<ChannelStruct *> m_destinations;

    TelnetClient *tClient;

    int SetDeviceData();
    int SetDeviceInformation();
    int SetInputLabelsData();
    int SetOutputLabelsData();
    int SetRoutingData();

    std::string SetName();
    int SetChannelCount();
};

#endif  // VideoRouter