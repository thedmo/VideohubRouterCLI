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

    // Todo call SetChannelData directly

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

    // Todo call SetChannelData directly
    SetChannelData();

    return 0;
}

int VideohubRouter::SetChannelData() {
    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;

    std::string block;
    std::string inputLabels = "input labels";
    std::string outputLabels = "output labels";
    std::string routing = "routing";
    std::string other = "other";

    bool foundChannelCount = false;

    unsigned int currentChannelNumber;
    ChannelStruct *currentStruct;
    int currentStructNumber;

    // std::string line;
    std::stringstream dataStream(*m_dataDump);
    while (std::getline(dataStream, line, '\n')) {

        if (!line.empty()) {
            m_dataSet.push_back(line);
                // Get Line Contents
            std::stringstream lineStream(line);
            while (std::getline(lineStream, lineSubString, ' ')) {
                lineList.push_back(lineSubString);
            }

            // Look for Specific Blocks in Dataset
            if (line.find("INPUT LABELS:") != std::string::npos) {
                std::cout << "Inputs:" << std::endl;
                block = inputLabels;
                continue;
            }
            else if (line.find("OUTPUT LABELS:") != std::string::npos) {
                std::cout << "Outputs:" << std::endl;
                block = outputLabels;
                continue;
            }
            else if (line.find("VIDEO OUTPUT ROUTING:") != std::string::npos) {
                std::cout << "Routing:" << std::endl;
                block = routing;
                continue;
            }
            else if (line.find("VIDEO OUTPUT LOCKS:") != std::string::npos) {
                block = other;
            }
            else if (line.find("PROTOCOL PREAMBLE:") != std::string::npos) {
                block = other;
            }
            else if (line.find("VIDEOHUB DEVICE:") != std::string::npos) {
                block = other;
            }
            else if (line.find("CONFIGURATION:") != std::string::npos) {
                block = other;
            }

            // Create Structs
            if (!foundChannelCount) {
                if (line.find("Video inputs: ") != std::string::npos) {
                    sourceCount = std::stoi(lineList[2]);
                    std::cout << "Device has " << sourceCount << " input channels."
                        << std::endl;

                    for (size_t j = 0; j < sourceCount; j++)
                    {
                        currentStruct = new ChannelStruct;
                        sources.push_back(currentStruct);
                    }
                }
                else if (line.find("Video outputs: ") != std::string::npos) {
                    destinationCount = std::stoi(lineList[2]);
                    std::cout << "Device has " << destinationCount << " output channels."
                        << std::endl;

                    for (size_t j = 0; j < destinationCount; j++)
                    {
                        currentStruct = new ChannelStruct;
                        destinations.push_back(currentStruct);
                    }
                    foundChannelCount = true;
                }
            }

            // Set Labels
            if (block == inputLabels || block == outputLabels) {
                // Get Channelnumber
                currentChannelNumber = std::stoi(lineList[0]);

                if (block == inputLabels) {
                    currentStruct = sources[currentChannelNumber];
                }
                else {
                    currentStruct = destinations[currentChannelNumber];
                }

                // Set Number
                currentStruct->channelNum = currentChannelNumber;
                // Set Name
                for (unsigned int j = 1; j < lineList.size(); ++j) {
                    currentStruct->name += lineList[j];
                    if (j < lineList.size() - 1) {
                        currentStruct->name += ' ';
                    }
                }

                std::cout << "Channel Label: " << currentStruct->name << std::endl;
            }

            //Set routing
            if (block == routing) {
                // Get Channelnumber
                currentChannelNumber = std::stoi(lineList[0]);
                currentStruct = destinations[currentChannelNumber];
                currentStructNumber = std::stoi(lineList[1]);
                currentStruct->source = sources[currentStructNumber];
                std::cout << currentStruct->channelNum << " " << currentStruct->name << " <-- " << currentStruct->source->channelNum << " " << currentStruct->source->name << std::endl;
            }
        } // if line.empty()

        lineList.clear();
        currentStruct = nullptr;
    } //for loop
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