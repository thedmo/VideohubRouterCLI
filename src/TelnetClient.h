#pragma once

#include <ws2tcpip.h>
#include <iostream>
#include <string>

class TelnetClient {
public:
    TelnetClient() = delete;
    TelnetClient(std::string ip, int port, std::string &init_response);
    ~TelnetClient();

    int SendMsgToServer(std::string msg);
    int ReceiveMsgFromServer(std::string &response);

    int ChangeIpAddress(std::string newAddress, std::string &init_response);

    std::string GetIp();

private:
    std::string m_ip_address;
    int m_port;

    char m_buf[4096];
    SOCKET m_sock;

    int OpenConnection();
    int CloseConnection();
};