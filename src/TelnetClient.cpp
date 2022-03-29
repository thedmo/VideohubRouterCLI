#include "TelnetClient.h"

TelnetClient::TelnetClient(std::string ip, int port)
    : ipAddress(ip), portNum(port) {}

TelnetClient::~TelnetClient() { CloseConnection(); }

int TelnetClient::SendMsgToServer(std::string msg, std::string &response) {
    int cResult;

    cResult = OpenConnection();

    if (cResult != 0) {
        std::cerr << "could not open Connection to Server: " << ipAddress
                  << std::endl;
        return -1;
    }

    int sendResult = send(sock, msg.c_str(), msg.size() + 1, 0);

    if (sendResult != SOCKET_ERROR) {
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        response = std::string(buf, 0, bytesReceived);

        if (bytesReceived > 0) {
            std::cout << "SERVER> " << response << std::endl;
        }
    }

    return 0;
}

int TelnetClient::OpenConnection() {
    WSAData data;

    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
        std::cerr << "Can't start Winsock, err #" << wsResult << std::endl;
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Can't Create socket, ERR #" << WSAGetLastError()
                  << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(portNum);
    int ipresult = inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    if (ipresult == 0) {
        std::cerr << "Format of Ip Wrong! Aborting. Err #: "
                  << WSAGetLastError() << std::endl;
        return -1;
    }

    int connResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        std::cerr << "Can't connect to server,m Err #" << WSAGetLastError()
                  << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    return 0;
}

int TelnetClient::CloseConnection() {
    closesocket(sock);
    WSACleanup();
    return 0;
}
