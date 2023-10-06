#include <iostream>
#include <string.h>
#include <iomanip>

#include <EthernetFrame/EthernetFrame.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

EthernetFrame::EthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
                             unsigned char *type, unsigned char *fcs, int payloadSize)
{

    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));
    this->logger->log("Creating new EthernetFrame", Severity::INFO);

    memcpy(this->preamble, preamble, 9);
    memcpy(this->destinationAddress, destinationAddress, 7);
    memcpy(this->sourceAddress, sourceAddress, 7);
    memcpy(this->type, type, 3);
    memcpy(this->fcs, fcs, 5);

    std::cout << "CRC: ";
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << +this->fcs[i];
    }
    std::cout << std::endl;

    this->payloadSize = payloadSize;
}

unsigned char *EthernetFrame::getPreamble()
{
    unsigned char *preamble = new unsigned char[9];
    strcpy((char *)preamble, (const char *)this->preamble);

    return preamble;
}

unsigned char *EthernetFrame::getDestinationAddress()
{
    unsigned char *destinationAddress = new unsigned char[7];
    strcpy((char *)destinationAddress, (const char *)this->destinationAddress);

    return destinationAddress;
}

unsigned char *EthernetFrame::getSourceAddress()
{
    unsigned char *sourceAddress = new unsigned char[7];
    strcpy((char *)sourceAddress, (const char *)this->sourceAddress);

    return sourceAddress;
}

unsigned char *EthernetFrame::getType()
{
    unsigned char *type = new unsigned char[3];
    strcpy((char *)type, (const char *)this->type);

    return type;
}

unsigned char *EthernetFrame::getFcs()
{
    unsigned char *fcs = new unsigned char[5];
    strcpy((char *)fcs, (const char *)this->fcs);

    return fcs;
}

int EthernetFrame::getPayloadSize()
{
    return this->payloadSize;
}

EthernetFrame::~EthernetFrame()
{
    if (this->logger != NULL)
    {
        delete logger;
    }
}