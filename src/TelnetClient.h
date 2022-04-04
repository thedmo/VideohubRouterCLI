#ifndef TelClient
#define TelClient

#include <iostream>
#include <string>
#include <ws2tcpip.h>

class TelnetClient{
    public:
    TelnetClient();
    TelnetClient(std::string ip, int port);
    ~TelnetClient();

    int SendMsgToServer(std::string, std::string &response);
    int ChangeIpAddress(std::string newAddress);

    std::string GetIp();

    private:
    std::string m_ipAddress;
    int portNum;

    std::string m_response;
    char buf[4096];
    SOCKET sock;

    int OpenConnection();
    int CloseConnection();
};
#endif //TelClient