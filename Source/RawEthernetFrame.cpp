#include <string.h>

#include <EthernetFrame/RawEthernetFrame.h>
#include <EthernetFrameVisitor/PrinterEthernetFrameVisitor.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

RawEthernetFrame::RawEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
                                   unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char *payload) : EthernetFrame(preamble, destinationAddress, sourceAddress, type, fcs, payloadSize)
{

    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));
    this->logger->log("Creating new RawEthernetFrame", Severity::INFO);

    this->payload = new unsigned char[payloadSize];
    strcpy((char *)this->payload, (const char *)payload);
}

unsigned char *RawEthernetFrame::getPayload()
{
    unsigned char *payload = new unsigned char[payloadSize];
    strcpy((char *)payload, (const char *)this->payload);

    return payload;
}

// bool RawEthernetFrame::validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor) {
//     validatorEthernetFrameVisitor->validate(this);

//     return true;
// }

void RawEthernetFrame::accept(PrinterEthernetFrameVisitor &printerEthernetFrameVisitor)
{
    printerEthernetFrameVisitor.visit(this);
    return;
}

RawEthernetFrame::~RawEthernetFrame()
{
    if (this->payload == NULL)
    {
        this->logger->log("payload in RawEthernetFrame is NULL", Severity::ERROR);
    }
    else
    {
        delete payload;
    }

    if (this->logger != NULL)
    {
        delete logger;
    }
}