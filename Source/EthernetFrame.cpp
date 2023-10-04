#include <string.h>

#include <EthernetFrame/EthernetFrame.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

EthernetFrame::EthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
    unsigned char *type, unsigned char *fcs, int payloadSize) {

    this->logger = new ConsoleLogger();
    this->logger = new FileLogger("Simulation.txt");
    this->logger.log("Creating new ECPRIEthernetFrame", Severity::INFO);

    strcpy(this->preamble, preamble);
    strcpy(this->destinationAddress, destinationAddress);
    strcpy(this->sourceAddress, sourceAddress);
    strcpy(this->type, type);
    strcpy(this->fcs, fcs);
    this->payloadSize = payloadSize;
    
    logger = new Logger("EthernetFrame");
}

EthernetFrame::unsigned char* getPreamble() {
    char *preamble = new char[8];
    strcpy(preamble, this->preamble);

    return preamble;
}

EthernetFrame::unsigned char* getDestinationAddress(){
    char *destinationAddress = new char[6];
    strcpy(destinationAddress, this->destinationAddress);

    return destinationAddress;
}

EthernetFrame::unsigned char* getSourceAddress() {
    char *sourceAddress = new char[6];
    strcpy(sourceAddress, this->sourceAddress);

    return sourceAddress;
}

EthernetFrame::unsigned char* getType() {
    char *type = new char[2];
    strcpy(type, this->type);

    return type;
}

EthernetFrame::unsigned char* getFcs() {
    char *fcs = new char[4];
    strcpy(fcs, this->fcs);

    return fcs;
}

EthernetFrame::int getPayloadSize() {
    return this->payloadSize;
}

EthernetFrame::~EthernetFrame() {
    if (this->logger != NULL) {
        delete logger;
    }
}