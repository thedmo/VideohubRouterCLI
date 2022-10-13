#ifndef VideoRouter
#define VideoRouter

#include <vector>
#include <Feedback.h>
#include "TelnetClient.h"

struct ChannelStruct {
    std::string name;
    unsigned int channelNum;
    ChannelStruct *source = nullptr;
    bool locked = false;

    bool changedRoute = false;
};

class VideohubRouter {
public:
    VideohubRouter() = delete;
    VideohubRouter(std::string ip, Feedback &ref_feed);
    ~VideohubRouter();

    Feedback SetIpAddress(std::string newAddress);
    
    std::string GetDataString();

    Feedback ChangeSourceName(unsigned int channel, std::string new_name);
    Feedback ChangeDestinationName(unsigned int channel, std::string new_name);

    Feedback SetRoute(int destination, int source);
    Feedback TakeRoutes();

    Feedback SendMsg(std::string msg);

    std::string GetName();
    std::string GetIp();
    std::string GetLastMsg();

    bool Get_Zombie_State();

    Feedback feed;

private:
    std::string m_ipAdress = "127.0.0.1";
    int m_port = 9990;

    std::string m_data_dump;
    std::string m_routes_dump, m_dest_labels_dump, m_source_labels_dump, m_device_dump;

    std::string m_name = "name not set";
    u_int sourceCount;
    std::vector<ChannelStruct *> m_sources;
    u_int destinationCount;
    std::vector<ChannelStruct *> m_destinations;

    TelnetClient *tClient;

    Feedback SetDeviceData();
    Feedback SetDeviceInformation();
    Feedback SetInputLabelsData();
    Feedback SetOutputLabelsData();
    Feedback SetRoutingData();

    std::string SetName();

    bool is_zombie = false;
};

#endif  // VideoRouter