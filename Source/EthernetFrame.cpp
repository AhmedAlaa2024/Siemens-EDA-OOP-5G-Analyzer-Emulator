#include <string.h>

#include <EthernetFrame/EthernetFrame.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

EthernetFrame::EthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
    unsigned char *type, unsigned char *fcs, int payloadSize) {

    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));
    this->logger->log("Creating new EthernetFrame", Severity::INFO);

    strcpy((char*)this->preamble, (const char*)preamble);
    strcpy((char*)this->destinationAddress, (const char*)destinationAddress);
    strcpy((char*)this->sourceAddress, (const char*)sourceAddress);
    strcpy((char*)this->type, (const char*)type);
    strcpy((char*)this->fcs, (const char*)fcs);
    this->payloadSize = payloadSize;
}

unsigned char* EthernetFrame::getPreamble() {
    unsigned char *preamble = new unsigned char[8];
    strcpy((char*)preamble, (const char*)this->preamble);

    return preamble;
}

unsigned char* EthernetFrame::getDestinationAddress(){
    unsigned char *destinationAddress = new unsigned char[6];
    strcpy((char*)destinationAddress, (const char*)this->destinationAddress);

    return destinationAddress;
}

unsigned char* EthernetFrame::getSourceAddress() {
    unsigned char *sourceAddress = new unsigned char[6];
    strcpy((char*)sourceAddress, (const char*)this->sourceAddress);

    return sourceAddress;
}

unsigned char* EthernetFrame::getType() {
    unsigned char *type = new unsigned char[2];
    strcpy((char*)type, (const char*)this->type);

    return type;
}

unsigned char* EthernetFrame::getFcs() {
    unsigned char *fcs = new unsigned char[4];
    strcpy((char*)fcs, (const char*)this->fcs);

    return fcs;
}

int EthernetFrame::getPayloadSize() {
    return this->payloadSize;
}

EthernetFrame::~EthernetFrame() {
    if (this->logger != NULL) {
        delete logger;
    }
}