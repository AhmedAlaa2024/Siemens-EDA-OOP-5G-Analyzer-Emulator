#include <iostream>
#include <cstdio>

#include <EthernetPacketParser/EthernetPacketParser.h>
#include <EthernetFrame/EthernetFrame.h>
#include <Simulator/Simulator.h>
#include <ValidatorEthernetFrame/ValidatorEthernetFrame.h>

#define MAX_PACKET_SIZE 1526

Simulator::Simulator()
{
    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));
}

void Simulator::simulate()
{
    this->logger->log("Simulation starts now!", Severity::INFO);

    EthernetPacketReader reader("input_packets");
    unsigned char *line = new unsigned char[MAX_PACKET_SIZE];
    unsigned char *hexLine;
    int *lineLength = new int(0);

    EthernetPacketParser ethernetPacketParser;
    EthernetFrame *ethernetFrame;
    
    ValidatorEthernetFrame* ValidatorEthernetFrame = ValidatorEthernetFrame::getInstance();
    while (reader.nextLine(line, lineLength)) {
        hexLine = new unsigned char[(*lineLength * 3) + 1]; // Room for "00 " for each character
        int offset = 0; // Offset for writing into hexLine

        for (size_t i = 0; i < *lineLength; i++) 
        {
            offset += snprintf(reinterpret_cast<char*>(hexLine) + offset, (*lineLength * 3) - offset, "%02X", line[i]);
        }
        hexLine[offset] = '\0'; // Add null terminator

        this->logger->log("Packet: " + std::string(reinterpret_cast<char*>(hexLine)), Severity::INFO);
        
        ethernetFrame = ethernetPacketParser.parsePacket(line, *lineLength);

        delete ethernetFrame;
        delete[] hexLine; // Use delete[] for dynamic arrays
    }
}

Simulator::~Simulator()
{
    if (this->logger != nullptr) {
        delete this->logger;
    }
}