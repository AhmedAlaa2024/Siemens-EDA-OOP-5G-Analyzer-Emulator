#include <iostream>

#include <EthernetPacketParser/EthernetPacketParser.h>
#include <EthernetFrame/EthernetFrame.h>
#include <Simulator/Simulator.h>

#define MAX_PACKET_SIZE 1526

Simulator::Simulator()
{
    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");

    consoleLogger->setSuccessor(fileLogger);
}

void Simulator::simulate()
{
    this->consoleLogger->log("Simulation starts now!", Severity::INFO);

    EthernetPacketReader reader("input_packets");
    unsigned char *line = new unsigned char[MAX_PACKET_SIZE];
    int *lineLength = new int(0);

    EthernetPacketParser ethernetPacketParser;
    EthernetFrame *ethernetFrame;
    while (reader.nextLine(line, lineLength))
    {
        ethernetFrame = ethernetPacketParser.parsePacket(line, *lineLength);
        delete ethernetFrame;
    };
}

Simulator::~Simulator()
{
    delete this->consoleLogger;
    delete this->fileLogger;
}