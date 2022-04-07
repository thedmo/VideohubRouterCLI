#ifndef VideoRouter
#define VideoRouter

#include <vector>

#include "TelnetClient.h"

struct Source{
    std::string name;
    unsigned int channelNum;
};

struct Destination{
    std::string name;
    unsigned int channelNum;
    Source* source;
};

class VideohubRouter {

public:
    VideohubRouter();
    VideohubRouter(std::string ip);
    ~VideohubRouter();

    int SetIpAddress(std::string newAddress);

    int GetStatus(std::string &dataDump);
    
    void PrintData();

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

    std::string * m_dataDump;
    std::vector<std::string> * m_dataSet;
    void FillDataSet(const std::string &dataString);

    std::string m_name = "not set";
    u_int channelCount;
    std::vector<Source> sources;
    std::vector<Destination> destinations;

    TelnetClient *tClient;

    void FillSources();
    void FillDestination();
    std::string SetName();
    int SetChannelCount();
} ;

#endif //VideoRouter