#ifndef TelClient
#define TelClient

#include <iostream>
#include <string>
#include <ws2tcpip.h>

class TelnetClient {
public:
    TelnetClient() = delete;
    TelnetClient(std::string ip, int port, std::string &initMsg);
    ~TelnetClient();

    int SendMsgToServer(std::string msg);
    int ReceiveMsgFromServer(std::string &dump);

    int ChangeIpAddress(std::string newAddress, std::string &initMsg);

    std::string GetIp();

private:
    std::string m_ipAddress;
    int portNum;

    char buf[4096];
    SOCKET sock;

    int OpenConnection();
    int CloseConnection();
};
#endif //TelClient