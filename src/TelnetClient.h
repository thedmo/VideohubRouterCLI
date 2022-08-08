#ifndef TELNETCLIENT
#define TELNETCLIENT

#include <ws2tcpip.h>
#include <string>
#include <Feedback.h>

class TelnetClient {
public:
    TelnetClient() = delete;
    TelnetClient(std::string ip, int port, std::string &, Feedback &ref_feed);
    ~TelnetClient();

    Feedback SendMsgToServer(std::string msg);
    Feedback ReceiveMsgFromServer(std::string &response);

    Feedback ChangeIpAddress(std::string newAddress, std::string &init_response);

    std::string GetIp();
    Feedback feed;

private:
    std::string m_ip_address;
    int m_port;

    char m_buf[4096];
    SOCKET m_sock;


    Feedback OpenConnection();
    Feedback CloseConnection();
};

#endif // TELNETCLIENT