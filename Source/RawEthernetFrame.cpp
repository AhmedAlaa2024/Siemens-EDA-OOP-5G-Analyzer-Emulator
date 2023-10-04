#include <string.h>

#include <EthernetFrame/RawEthernetFrame.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

RawEthernetFrame::RRawEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
    unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char *payload, int payloadSize) : EthernetFrame(preamble, destinationAddress, sourceAddress, type, fcs, payloadSize) {
    
    this->logger = new ConsoleLogger();
    this->logger = new FileLogger("Simulation.txt");
    this->logger.log("Creating new RawEthernetFrame", Severity::INFO);

    this->payload = new unsigned char[payloadSize];
    strcpy(this->payload, payload);
}

RawEthernetFrame::unsigned char* getPayload() {
    unsigned char *payload = new unsigned char[payloadSize];
    strcpy(payload, this->payload);

    return payload;
}

RawEthernetFrame::bool validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor) {
    return validatorEthernetFrameVisitor->validate(this);

}
RawEthernetFrame::bool print(PrinterEthernetFrameVisitor* printerEthernetFrameVisitor) {
    return printerEthernetFrameVisitor->print(this);
}

RawEthernetFrame::~RawEthernetFrame() {
    if (this->rtcData == NULL) {
        this->logger.log("payload in RawEthernetFrame is NULL", Severity::ERROR);
    } else {
        delete payload;
    }

    if (this->logger != NULL) {
        delete logger;
    }
}