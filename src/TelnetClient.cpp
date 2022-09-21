#include "TelnetClient.h"
#include <iostream>
#include <Windows.h>

auto t_log = spdlog::basic_logger_mt("Telnet client", "logs/TLog.txt");

TelnetClient::TelnetClient(std::string ip, int port, std::string &init_response, Feedback &ref_feed)
    : m_ip_address(ip), m_port(port)
{
    t_log->flush_on(spdlog::level::debug);
    t_log->info("logger for new instance initialized");

    ref_feed = OpenConnection();
    if (ref_feed.Ok())
    {
        ref_feed = ReceiveMsgFromServer(init_response);
        // ref_feed = SendMsgToServer("initialize");
        // init_response = m_last_data_dump;
        m_last_data_dump = init_response;
    }
}

TelnetClient::~TelnetClient() { CloseConnection(); }

std::string ReceiveMsgAsync(TelnetClient *tc)
{
    std::string retVal;



    tc->ReceiveMsgFromServer(retVal);

    return retVal;
}

Feedback TelnetClient::SendMsgToServer(std::string msg)
{

    // auto f1 = std::async(ReceiveMsgAsync, this);

    // std::cout << "TelnetClient: sending: " << msg << std::endl;
    t_log->info("Sending:\n" + msg);
    t_log->flush_on(spdlog::level::debug);

    int sendResult = send(m_sock, msg.c_str(), msg.size(), 0);

    // std::sleep(1);


    // m_last_data_dump = f1.get();
    ReceiveMsgFromServer(m_last_data_dump);

    // feed.Set_Feedback(0, "Message sent:\n" + msg);

    return feed;
}

// Feedback TelnetClient::SendMsgToServerWithResponse(std::string msg, std::string &response) {
//     int sendResult = send(m_sock, msg.c_str(), msg.size(), 0);
//     ReceiveMsgFromServer(response);

//     feed.Set_Feedback(0, "Message sent:\n" + msg);

//     return feed;
// }

Feedback TelnetClient::ReceiveMsgFromServer(std::string &response)
{
    Sleep(100);
    ZeroMemory(m_buf, 4096);
    int bytesReceived = recv(m_sock, m_buf, 4096, 0);
    std::string s_result = std::string(m_buf, 0, bytesReceived);
    // t_log->flush_on(spdlog::level::debug);
    // t_log->info("Received:\n" + s_result);
    // t_log->flush_on(spdlog::level::debug);

    if (s_result.size() != std::string::npos)
    {
        response = s_result;
        // m_last_data_dump = s_result;
    }
    else
    {
        response.clear();
    }


    t_log->info("Received:\n" + response);
    t_log->flush_on(spdlog::level::debug);

    feed.Set_Result(0);
    feed.Set_Message("Bytes received: " + bytesReceived);

    return feed;
}

Feedback TelnetClient::ChangeIpAddress(std::string newAddress, std::string &init_response)
{

    if (newAddress.empty())
    {
        feed.Set_Feedback(-1, "Ip string was empty. abort.");
        return feed;
    }

    sockaddr_in newIp;
    newIp.sin_family = AF_INET;
    int ipResult = inet_pton(AF_INET, newAddress.c_str(), &newIp.sin_addr);

    if (ipResult != 1)
    {
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

std::string TelnetClient::GetLastDataDump() { return m_last_data_dump; }

Feedback TelnetClient::OpenConnection()
{
    WSAData data;

    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        feed.Set_Feedback(-1, "Can't start Winsock, err #" + WSAGetLastError());
        return feed;
    }

    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET)
    {
        WSACleanup();
        feed.Set_Feedback(-1, "Can't Create socket, ERR #" + WSAGetLastError());
        return feed;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    int ipresult = inet_pton(AF_INET, m_ip_address.c_str(), &hint.sin_addr);
    if (ipresult == 0)
    {
        feed.Set_Feedback(-1, "Format of Ip Wrong! Err #: " + WSAGetLastError());
        return feed;
    }

    int connResult = connect(m_sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        closesocket(m_sock);
        WSACleanup();
        feed.Set_Feedback(-1, "Can't connect to server. Wrong IP? Err #" + WSAGetLastError());
        return feed;
    }

    feed.Set_Result(0);
    feed.Set_Message("Everything is quiet, Commander");

    return feed;
}

Feedback TelnetClient::CloseConnection()
{
    closesocket(m_sock);
    WSACleanup();

    feed.Set_Message("Connection closed");
    feed.Set_Result(0);
    return feed;
}
