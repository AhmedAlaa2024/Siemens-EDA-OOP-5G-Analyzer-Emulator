#include <string.h>

#include <EthernetFrame/ECPRIEthernetFrame.h>

#include <Logger/Logger.h>
#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

ECPRIEthernetFrame::ECPRIEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
    unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char protocolVersion, unsigned char concatenationIndicator,
    unsigned char messageType, unsigned char *rtcId, unsigned char *seqId, int eCPRIpayloadLength, unsigned char *rtcData)
    : EthernetFrame(preamble, destinationAddress, sourceAddress, type, fcs, payloadSize) {

    this->logger = new ConsoleLogger();
    this->logger = new FileLogger("Simulation.txt");
    this->logger.log("Creating new ECPRIEthernetFrame", Severity::INFO);

    this->protocolVersion = protocolVersion;
    this->concatenationIndicator = concatenationIndicator;
    this->messageType = messageType;
    strcpy(this->rtcId, rtcId);
    strcpy(this->seqId, seqId);

    this->eCPRIPayloadLength = eCPRIpayloadLength
    this->rtcData = new unsigned char[eCPRIpayloadLength];
    strcpy(this->rtcData, rtcData);
}

ECPRIEthernetFrame::unsigned char getProtocolVersion() {
    return protocolVersion;
}

ECPRIEthernetFrame::unsigned char getConcatenationIndicator() {
    return concatenationIndicator;
}

ECPRIEthernetFrame::unsigned char getMessageType() {
    return messageType;
}

ECPRIEthernetFrame::unsigned char* getRtcId() {
    unsigned char *rtcId = new unsigned char[2];
    strcpy(rtcId, this->rtcId);

    return rtcId;
}

ECPRIEthernetFrame::unsigned char* getSeqId() {
    unsigned char *seqId = new unsigned char[2];
    strcpy(seqId, this->seqId);

    return seqId;
}

ECPRIEthernetFrame::int getECPRIPayloadLength() {
    return eCPRIPayloadLength;
}

ECPRIEthernetFrame::unsigned char* getRtcData() {
    unsigned char *rtcData = new unsigned char[eCPRIPayloadLength];
    strcpy(rtcData, this->rtcData);

    return rtcData;
}

ECPRIEthernetFrame::bool validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor) {
    return validatorEthernetFrameVisitor->validate(this);
}

ECPRIEthernetFrame::bool print(PrinterEthernetFrameVisitor* printerEthernetFrameVisitor) {
    return printerEthernetFrameVisitor->print(this);
}

ECPRIEthernetFrame::~ECPRIEthernetFrame() {
    if (this->rtcData == NULL) {
        this->logger.log("rtcData in ECPRIEthernetFrame is NULL", Severity::ERROR);
    } else {
        delete rtcData;
    }

    if (this->logger != NULL) {
        delete logger;
    }
}