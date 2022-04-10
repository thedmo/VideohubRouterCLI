#include "VideohubRouter.h"

// #include <algorithm>
#include <iostream>
// #include <iterator>
#include <sstream>

VideohubRouter::VideohubRouter() {
    tClient = new TelnetClient(m_ipAdress, m_port);
    m_dataDump = new std::string;
    m_dataSet = new std::vector<std::string>;
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

    GetStatus();

    return 0;
}

int VideohubRouter::GetStatus() {
    int cResult = tClient->SendMsgToServer("", m_dataDump);

    if (cResult != 0) {
        std::cerr << "could not connect to server. No status data obtained"
                  << std::endl;
        return -1;
    }

    FillDataSet();

    return 0;
}

std::string VideohubRouter::GetIp() { return tClient->GetIp(); }

std::string VideohubRouter::GetName() { return m_name; }

int VideohubRouter::FillDataSet() {
    if (*m_dataDump == "") {
        std::cerr << "no data available" << std::endl;
        return -1;
    }

    FillSources();
    FillDestination();

    std::stringstream stringStream(*m_dataDump);
    std::string line;

    while (std::getline(stringStream, line, '\n')) {
        m_dataSet->push_back(line);
    };

    return 0;
}

int VideohubRouter::FillSources() {
    std::string target = "VIDEOHUB DEVICE:";

    std::string s_result;

    // TODO: Fix finding sources in Vector.

    //     std::find(*m_dataSet->begin(), *m_dataSet->end(), &target);

    // std::cout << s_result << std::endl;

    if (target != s_result) {
        std::cerr << "could not find sources in data" << std::endl;
        return -1;
    }

    // Toto actual create Structs and populate Sources

    return 0;
}

int VideohubRouter::FillDestination() {
    // Toto actual create Structs and populate Destinations

    return 0;
}

int VideohubRouter::PrintData() {
    if (m_dataSet->empty()) {
        std::cerr << "no data to be printed available." << std::endl;
        return -1;
    }

    for (auto line : *m_dataSet) {
        std::cout << line << std::endl;
    }

    return 0;
}