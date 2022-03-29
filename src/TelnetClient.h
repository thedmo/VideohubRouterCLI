#include <WS2tcpip.h>
#include <iostream>
#include <string>

class TelnetClient{
    public:
    TelnetClient();
    TelnetClient(std::string ip, int port);
    ~TelnetClient();

    int SendMsgToServer(std::string, std::string &response);


    private:
    std::string ipAddress;
    int portNum;

    std::string response;
    char buf[4096];
    SOCKET sock;

    int OpenConnection();
    int CloseConnection();
};
