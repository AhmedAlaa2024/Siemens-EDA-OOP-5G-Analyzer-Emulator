#include <string.h>

#include <EthernetFrame/ECPRIEthernetFrame.h>
#include <EthernetFrameVisitor/PrinterEthernetFrameVisitor.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

ECPRIEthernetFrame::ECPRIEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
                                       unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char protocolVersion, unsigned char concatenationIndicator,
                                       unsigned char messageType, unsigned char *rtcId, unsigned char *seqId, int eCPRIpayloadLength, unsigned char *rtcData)
    : EthernetFrame(preamble, destinationAddress, sourceAddress, type, fcs, payloadSize)
{

    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));
    this->logger->log("Creating new ECPRIEthernetFrame", Severity::INFO);

    this->protocolVersion = protocolVersion;
    this->concatenationIndicator = concatenationIndicator;
    this->messageType = messageType;
    strcpy((char *)this->rtcId, (const char *)rtcId);
    strcpy((char *)this->seqId, (const char *)seqId);

    this->eCPRIPayloadLength = eCPRIpayloadLength;
    this->rtcData = new unsigned char[eCPRIpayloadLength];
    strcpy((char *)this->rtcData, (const char *)rtcData);
}

unsigned char ECPRIEthernetFrame::getProtocolVersion()
{
    return protocolVersion;
}

unsigned char ECPRIEthernetFrame::getConcatenationIndicator()
{
    return concatenationIndicator;
}

unsigned char ECPRIEthernetFrame::getMessageType()
{
    return messageType;
}

unsigned char *ECPRIEthernetFrame::getRtcId()
{
    unsigned char *rtcId = new unsigned char[3];
    memcpy((char *)rtcId, (const char *)this->rtcId, 3);

    return rtcId;
}

unsigned char *ECPRIEthernetFrame::getSeqId()
{
    unsigned char *seqId = new unsigned char[3];
    memcpy((char *)seqId, (const char *)this->seqId, 3);

    return seqId;
}

int ECPRIEthernetFrame::getECPRIPayloadLength()
{
    return eCPRIPayloadLength;
}

unsigned char *ECPRIEthernetFrame::getRtcData()
{
    unsigned char *rtcData = new unsigned char[eCPRIPayloadLength + 1];
    memcpy((char *)rtcData, (const char *)this->rtcData, eCPRIPayloadLength + 1);

    return rtcData;
}

void ECPRIEthernetFrame::accept(PrinterEthernetFrameVisitor &printerEthernetFrameVisitor)
{
    printerEthernetFrameVisitor.visit(this);
    return;
}

ECPRIEthernetFrame::~ECPRIEthernetFrame()
{
    if (this->rtcData == NULL)
    {
        this->logger->log("rtcData in ECPRIEthernetFrame is NULL", Severity::ERROR);
    }
    else
    {
        delete rtcData;
    }

    if (this->logger != NULL)
    {
        delete logger;
    }
}