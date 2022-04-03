#include "VideohubRouter.h"

#include <iostream>
#include <sstream>

VideohubRouter::VideohubRouter() {

    tClient = new TelnetClient(m_ipAdress, m_port);
}

VideohubRouter::VideohubRouter(std::string ip) : m_ipAdress(ip) {
    tClient = new TelnetClient(m_ipAdress, m_port);
    GetStatus(*m_dataDump);
}

VideohubRouter::~VideohubRouter() {
    delete (tClient);
    tClient = nullptr;
    m_dataDump == nullptr;
}

int VideohubRouter::SetIpAddress(std::string newAddress) {
    int result = tClient->ChangeIpAddress(newAddress);

    if (result != 0) {
        return -1;
    }

    return 0;
}


int VideohubRouter::GetStatus(std::string &dataDump) {
    int cResult = tClient->SendMsgToServer("", dataDump);

    if (cResult != 0) {
        std::cerr << "could not connect to server. Aborting. Wrong Ip?" << std::endl;
        return -1;
    }
    return 0;
}

void VideohubRouter::FillDataSet(const std::string &dataString) {
    m_dataSet = new std::vector<std::string>();
    std::string line = "";

    while (std::getline(std::istringstream(dataString), line, '\n')) {
        int i = 0;
        m_dataSet->push_back("const line");
    }
}

void VideohubRouter::PrintData() {

    std::cout << "PrintData not properly functional" << std::endl;

    // for (auto line : *m_dataSet){
    //     std::cout << line << std::endl;
    // }
}