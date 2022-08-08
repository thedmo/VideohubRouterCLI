#include "TelnetClient.h"

TelnetClient::TelnetClient(std::string ip, int port, std::string &init_response, Feedback &ref_feed)
    : m_ip_address(ip), m_port(port) {

    ref_feed = OpenConnection();
    if (ref_feed.Ok()) {
        ref_feed = ReceiveMsgFromServer(init_response);
    }
}

TelnetClient::~TelnetClient() { CloseConnection(); }

Feedback TelnetClient::SendMsgToServer(std::string msg) {
    int sendResult = send(m_sock, msg.c_str(), msg.size(), 0);

    feed.Set_Feedback(0, "Message sent:\n" + msg);
    return feed;
}

Feedback TelnetClient::ReceiveMsgFromServer(std::string &response) {
    ZeroMemory(m_buf, 4096);
    int bytesReceived = recv(m_sock, m_buf, 4096, 0);
    std::string s_result = std::string(m_buf, 0, bytesReceived);
    if (s_result.size() != std::string::npos)
    {
        response = s_result;
    }
    else {
        response.clear();
    }

    feed.Set_Result(0);
    feed.Set_Message("Bytes received: " + bytesReceived);

    return feed;
}

Feedback TelnetClient::ChangeIpAddress(std::string newAddress, std::string &init_response) {
    sockaddr_in newIp;
    newIp.sin_family = AF_INET;
    int ipResult = inet_pton(AF_INET, newAddress.c_str(), &newIp.sin_addr);

    if (ipResult != 1) {
        feed.Set_Feedback(-1, "not a valid IPv4 Adress");
        return feed;
    }

    m_ip_address = newAddress;

    OpenConnection();
    if (!feed.Ok())
    {
        return feed;
    }

    ReceiveMsgFromServer(init_response);
    if (!feed.Ok())
    {
        return feed;
    }

    feed.Set_Feedback(0, ("New Ip: " + newAddress));

    return feed;
}

std::string TelnetClient::GetIp() { return m_ip_address; }

Feedback TelnetClient::OpenConnection() {
    WSAData data;

    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
        feed.Set_Feedback(-1, "Can't start Winsock, err #" + WSAGetLastError());
        return feed;
    }

    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET) {
        WSACleanup();
        feed.Set_Feedback(-1, "Can't Create socket, ERR #" + WSAGetLastError());
        return feed;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    int ipresult = inet_pton(AF_INET, m_ip_address.c_str(), &hint.sin_addr);
    if (ipresult == 0) {
        feed.Set_Feedback(-1, "Format of Ip Wrong! Err #: " + WSAGetLastError());
        return feed;
    }

    int connResult = connect(m_sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        closesocket(m_sock);
        WSACleanup();
        feed.Set_Feedback(-1, "Can't connect to server. Wrong IP? Err #" + WSAGetLastError());
        return feed;
    }

    feed.Set_Result(0);
    feed.Set_Message("Everything is quiet, Commander");

    return feed;
}

Feedback TelnetClient::CloseConnection() {
    closesocket(m_sock);
    WSACleanup();

    feed.Set_Message("Connection closed");
    feed.Set_Result(0);
    return feed;
}
