#include "VideohubRouter.h"

#include <algorithm>
#include <iostream>
// #include <iterator>
#include <sstream>

VideohubRouter::VideohubRouter() {
    tClient = new TelnetClient(m_ipAdress, m_port);
    m_dataDump = new std::string;
}

VideohubRouter::~VideohubRouter() {
    delete (tClient);
    tClient = nullptr;
    m_dataDump == nullptr;

    for (auto item : sources) {
        delete (item);
        item = nullptr;
    }

    for (auto item : destinations) {
        delete (item);
        item = nullptr;
    }
}

int VideohubRouter::SetIpAddress(std::string newAddress) {
    int result = tClient->ChangeIpAddress(newAddress);

    if (result != 0) {
        return -1;
    }

    GetData();

    return 0;
}

int VideohubRouter::GetData() {
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

    std::stringstream stringStream(*m_dataDump);
    std::string line;

    bool foundChannelCount = false;
    while (std::getline(stringStream, line, '\n')) {
        m_dataSet.push_back(line);

        // Get Channelcount
        if (!foundChannelCount) {
            if (line.find("Video inputs: ") != std::string::npos) {
                std::string tempString;
                std::vector<std::string> tempStrings;
                std::stringstream ss(line);
                while (std::getline(ss, tempString, ' ')) {
                    tempStrings.push_back(tempString);
                }
                channelCount = std::stoi(tempStrings[2]);
                std::cout << "Device has " << channelCount << " channels."
                          << std::endl;
                foundChannelCount = true;
            }
        }
    }

    // std::cout << m_dataSet[7] << std::endl; // out of Range...

    FillSources();
    // FillDestination();

    return 0;
}

int VideohubRouter::FillSources() {
    // std::string target = "INPUT LABELS:";
    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;
    std::string channelName;

    bool inputLabelsBlock = false;

    for (unsigned int i; i < m_dataSet.size(); ++i) {
        // Look for Labels Block in Dataset
        line = m_dataSet[i];
        if (line.find("INPUT LABELS:") != std::string::npos) {
            inputLabelsBlock = true;
            continue;
        } else if (line.find("OUTPUT LABELS:") != std::string::npos) {
            inputLabelsBlock = false;
            break;
        }

        // Set Labels
        if (inputLabelsBlock && line != "") {
            // Create Source Struct
            Source* newSource = new Source();

            std::stringstream lineStream(line);

            // Compile Input Label
            while (std::getline(lineStream, lineSubString, ' ')) {
                lineList.push_back(lineSubString);
            }

            //Set Channelnumber
            newSource->channelNum = std::stoi(lineList[0]);

            //Set Name
            for (unsigned int j = 1; j < lineList.size(); ++j) {
                channelName += lineList[j];
                if (j < lineList.size() - 1) {
                    channelName += ' ';
                }
            }
            newSource->name = channelName;

            lineList.clear();
            channelName.clear();

            sources.push_back(newSource);

            std::cout << "added Source Struct: " << newSource->channelNum << " "
                      << newSource->name << std::endl;
        }
    }

    // if (index < m_dataSet.size()) s_result = m_dataSet.at(index);

    // if (target != s_result) {
    //     std::cerr << "could not find sources in data" << std::endl;
    //     return -1;
    // }

    // std::cout << s_result << std::endl;

    // Todo actual create Structs and populate Sources

    return 0;
}

int VideohubRouter::FillDestination() {
    // Toto actual create Structs and populate Destinations

    return 0;
}

int VideohubRouter::PrintData() {
    if (m_dataSet.empty()) {
        std::cerr << "no data to be printed available." << std::endl;
        return -1;
    }

    for (auto line : m_dataSet) {
        std::cout << line << std::endl;
    }

    return 0;
}