#include "VideohubRouter.h"

// #include <algorithm>
#include <iostream>
#include <sstream>

VideohubRouter::VideohubRouter(std::string ip, Feedback &ref_feed) :
    m_ipAdress(ip) {
    tClient = new TelnetClient(m_ipAdress, m_port, m_init_data_dump, ref_feed);
    if (ref_feed.Ok()) {
        ref_feed = SetDeviceData();
    }
    else {
        is_zombie = true;
    }
}

VideohubRouter::~VideohubRouter() {
    delete tClient;
    tClient = nullptr;

    for (auto item : m_sources) {
        delete item;
        item = nullptr;
    }

    for (auto item : m_destinations) {
        delete item;
        item = nullptr;
    }
}

bool VideohubRouter::Get_Zombie_State() {
    return is_zombie;
}

Feedback VideohubRouter::SetIpAddress(std::string newAddress) {
    feed = tClient->ChangeIpAddress(newAddress, m_init_data_dump);

    return feed;
}

std::string VideohubRouter::GetIp() { return tClient->GetIp(); }

std::string VideohubRouter::GetName() { return m_name; }

Feedback VideohubRouter::SetDeviceInformation() {
    if (m_device_dump == "") {
        feed.Set_Feedback(-1, "no device data available");
        return feed;
    }

    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;

    std::stringstream dataStream(m_device_dump);
    while (std::getline(dataStream, line, '\n')) {
        std::stringstream lineStream(line);
        while (std::getline(lineStream, lineSubString, ' ')) {
            lineList.push_back(lineSubString);
        }

        // skip step, if line doesn't contain information
        if ((line.find("VIDEOHUB DEVICE:") != std::string::npos) || line == "") {
            continue;
        }

        //Set Name of Device
        if (line.find("Friendly name: ") != std::string::npos) {
            m_name.clear();
            for (size_t i = 2; i < lineList.size(); i++)
            {
                m_name += lineList[i];
            }
        }

        // Create Input and Output Structs
        if (line.find("Video inputs: ") != std::string::npos) {
            sourceCount = std::stoi(lineList[2]);

            for (size_t j = 0; j < sourceCount; j++) {
                m_sources.push_back(new ChannelStruct);
            }
        }
        else if (line.find("Video outputs: ") != std::string::npos) {
            destinationCount = std::stoi(lineList[2]);

            for (size_t j = 0; j < destinationCount; j++) {
                m_destinations.push_back(new ChannelStruct);
            }
        }

        lineList.clear();
    }

    feed.Set_Feedback(0, "device data set");
    return feed;
}

Feedback VideohubRouter::SetInputLabelsData() {
    if (m_source_labels_dump == "") {
        feed.Set_Feedback(-1, "no input label data available");
        return feed;
    }

    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;

    std::stringstream dataStream(m_source_labels_dump);
    while (std::getline(dataStream, line, '\n')) {
        std::stringstream lineStream(line);
        while (std::getline(lineStream, lineSubString, ' ')) {
            lineList.push_back(lineSubString);
        }

        // skip step, if line doesn't contain channel information
        if ((line.find("INPUT LABELS:") != std::string::npos) || line == "") {
            continue;
        }

        // Get Channelnumber
        int currentChannelNumber = std::stoi(lineList[0]);

        // Set Number
        m_sources[currentChannelNumber]->channelNum = currentChannelNumber;

        // Set Name
        for (unsigned int j = 1; j < lineList.size(); ++j) {
            m_sources[currentChannelNumber]->name += lineList[j];
            if (j < lineList.size() - 1) {
                m_sources[currentChannelNumber]->name += ' ';
            }
        }
        lineList.clear();
    }

    feed.Set_Feedback(0, "input labels data set");
    return feed;
}

Feedback VideohubRouter::SetOutputLabelsData() {
    if (m_dest_labels_dump == "") {
        feed.Set_Feedback(-1, "no output data available");
        return feed;
    }

    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;

    std::stringstream dataStream(m_dest_labels_dump);
    while (std::getline(dataStream, line, '\n')) {
        std::stringstream lineStream(line);
        while (std::getline(lineStream, lineSubString, ' ')) {
            lineList.push_back(lineSubString);
        }

        // skip step, if line doesn't contain channel information
        if ((line.find("OUTPUT LABELS:") != std::string::npos) || line == "") {
            continue;
        }

        // Get Channelnumber
        int currentChannelNumber = std::stoi(lineList[0]);

        // Set Number
        m_destinations[currentChannelNumber]->channelNum = currentChannelNumber;

        // Set Name
        for (unsigned int j = 1; j < lineList.size(); ++j) {
            m_destinations[currentChannelNumber]->name += lineList[j];
            if (j < lineList.size() - 1) {
                m_destinations[currentChannelNumber]->name += ' ';
            }
        }
        lineList.clear();
    }

    feed.Set_Feedback(0, "outputlabels data set");
    return feed;
}

Feedback VideohubRouter::SetRoutingData() {
    if (m_routes_dump == "") {
        feed.Set_Feedback(-1, "no routing data available");
        return feed;
    }

    std::string line;
    std::string lineSubString;
    std::vector<std::string> lineList;

    std::stringstream dataStream(m_routes_dump);
    while (std::getline(dataStream, line, '\n')) {
        std::stringstream lineStream(line);
        while (std::getline(lineStream, lineSubString, ' ')) {
            lineList.push_back(lineSubString);
        }

        // skip step, if line doesn't contain information
        if ((line.find("VIDEO OUTPUT ROUTING:") != std::string::npos) || line == "") {
            continue;
        }

        // set inputs in outputs
        int current_output_number = std::stoi(lineList[0]);
        int current_input_number = std::stoi(lineList[1]);
        m_destinations[current_output_number]->source = m_sources[current_input_number];
        lineList.clear();
    }

    feed.Set_Feedback(0, "Routingdata set");
    return feed;
}


Feedback VideohubRouter::SetDeviceData() {
    if (m_init_data_dump == "") {
        feed.Set_Feedback(-1, "no data available");

        return feed;
    }

    std::string line;

    std::string block;
    std::string device_info = "VIDEOHUB DEVICE:";
    std::string inputLabels = "input labels";
    std::string outputLabels = "output labels";
    std::string routing = "routing";
    std::string other = "other";

    std::stringstream dataStream(m_init_data_dump);
    while (std::getline(dataStream, line, '\n')) {
        if (!line.empty()) {

            // Look for Specific Blocks in Dataset and set mode
            if (line.find("PROTOCOL PREAMBLE:") != std::string::npos) {
                block = other;
                continue;
            }
            else if (line.find("VIDEOHUB DEVICE:") != std::string::npos) {
                block = device_info;
                continue;
            }
            else if (line.find("INPUT LABELS:") != std::string::npos) {
                // std::cout << "Inputs:" << std::endl;
                block = inputLabels;
                continue;
            }
            else if (line.find("OUTPUT LABELS:") != std::string::npos) {
                // std::cout << "Outputs:" << std::endl;
                block = outputLabels;
                continue;
            }
            else if (line.find("VIDEO OUTPUT LOCKS:") != std::string::npos) {
                block = other;
                continue;
            }
            else if (line.find("VIDEO OUTPUT ROUTING:") !=
                std::string::npos) {
                // std::cout << "Routing:" << std::endl;
                block = routing;
                continue;
            }
            else if (line.find("CONFIGURATION:") != std::string::npos) {
                block = other;
                continue;
            }
            if (block == other)
            {
                continue;
            }

            if (block == device_info) {
                m_device_dump += line;
                m_device_dump += '\n';
            }
            else if (block == inputLabels) {
                m_source_labels_dump += line;
                m_source_labels_dump += '\n';
            }
            else if (block == outputLabels) {
                m_dest_labels_dump += line;
                m_dest_labels_dump += '\n';
            }
            else if (block == routing) {
                m_routes_dump += line;
                m_routes_dump += '\n';
            }
        }  // if line.empty()

    }  // for loop

    //Todo Getting Information only when something has changed

    feed = SetDeviceInformation();
    if (!feed.Ok()) return feed;

    feed = SetInputLabelsData();
    if (!feed.Ok()) return feed;

    feed = SetOutputLabelsData();
    if (!feed.Ok()) return feed;

    feed = SetRoutingData();
    if (!feed.Ok()) return feed;

    feed.Set_Feedback(0, "Device data set.");
    return feed;
}

// Todo get information from device on Command sent

Feedback VideohubRouter::ChangeSourceName(unsigned int channel,
    std::string new_name) {
    if (channel >= sourceCount) {
        feed.Set_Feedback(-1, "Channelnumber of source higher than channelcount");
        return feed;
    }

    m_sources[channel]->name = new_name;

    std::string channel_name_command;
    std::string response;

    channel_name_command = "INPUT LABELS:\n" + std::to_string(channel) + " " + new_name + "\n\n";

    feed = tClient->SendMsgToServer(channel_name_command);
    if (feed.Get_Result() != 0)
    {
        return feed;
    }

    feed.Set_Feedback(0, "Source Name changed to " + new_name);
    return feed;
}

Feedback VideohubRouter::ChangeDestinationName(unsigned int channel,
    std::string new_name) {
    if (channel >= destinationCount) {
        feed.Set_Feedback(-1, "Channelnumber of destination higher than channelcount");
        return feed;
    }

    m_destinations[channel]->name = new_name;

    std::string channel_name_command;
    std::string response;
    channel_name_command = "OUTPUT LABELS:\n" + std::to_string(channel) + " " + new_name + "\n\n";

    feed = tClient->SendMsgToServer(channel_name_command);
    if (feed.Get_Result() != 0)
    {
        return feed;
    }

    feed.Set_Feedback(0, "Destination Name changed to " + new_name);
    return feed;
}

Feedback VideohubRouter::SetRoute(int destination, int source) {
    if (destination >= destinationCount) {
        feed.Set_Feedback(-1, "Destination Number too high");
        return feed;
    }
    else if (source >= sourceCount) {
        feed.Set_Feedback(-1, "Source Number too high");
        return feed;
    }

    ChannelStruct *currentDest = m_destinations[destination];
    ChannelStruct *currentSrc = m_sources[source];

    currentDest->source = currentSrc;
    currentDest->changedRoute = true;

    feed.Set_Feedback(0, "new route prepared");
    return feed;
}

Feedback VideohubRouter::TakeRoutes() {
    std::string route_command = "VIDEO OUTPUT ROUTING:\n";
    std::string currentRoute;
    std::string response;

    for (auto destination : m_destinations) {
        if (destination->changedRoute) {
            currentRoute = std::to_string(destination->channelNum) + " " +
                std::to_string(destination->source->channelNum) +
                '\n';
            route_command += currentRoute;
            destination->changedRoute = false;
        }
    }
    route_command += '\n';

    feed = tClient->SendMsgToServer(route_command);
    if (feed.Get_Result() != 0)
    {
        return feed;
    }

    feed = tClient->ReceiveMsgFromServer(response);
    if (!feed.Ok()) return feed;

    feed.Set_Feedback(0, "New routes taken");
    return feed;
}

std::string VideohubRouter::GetDataString() {

    return "Device information" + m_device_dump + "\n" +
        "Input labels:" + m_source_labels_dump + "\n" +
        "Output labels:" + m_dest_labels_dump + "\n" +
        "Routing:" + m_routes_dump;
}