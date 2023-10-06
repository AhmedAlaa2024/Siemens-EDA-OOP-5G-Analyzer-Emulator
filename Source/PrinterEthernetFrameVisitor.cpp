#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include <EthernetFrameVisitor/PrinterEthernetFrameVisitor.h>
#include <EthernetFrame/RawEthernetFrame.h>
#include <EthernetFrame/ECPRIEthernetFrame.h>

PrinterEthernetFrameVisitor::PrinterEthernetFrameVisitor(std::string fileName = "output_packets")
{
    this->fileStream = new std::fstream(fileName, std::ios::out);
}

int PrinterEthernetFrameVisitor::frameNum = 0;

void PrinterEthernetFrameVisitor::visit(RawEthernetFrame *ethernetframe)
{
    this->printHex(ethernetframe->getPreamble(), 8, "Packet # " + std::to_string(frameNum) + ":\n");
    this->printHex(ethernetframe->getDestinationAddress(), 6);
    this->printHex(ethernetframe->getSourceAddress(), 6);
    this->printHex(ethernetframe->getType(), 2);
    this->printHex(ethernetframe->getPayload(), ethernetframe->getPayloadSize());
    this->printHex(ethernetframe->getFcs(), 4, "", true);

    this->printHex(ethernetframe->getFcs(), 4, "CRC: ", true);
    this->printHex(ethernetframe->getDestinationAddress(), 6, "Destination Address: ", true);
    this->printHex(ethernetframe->getSourceAddress(), 6, "Source Address: ", true);
    this->printHex(ethernetframe->getType(), 2, "Type: ", true);

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::visit(ECPRIEthernetFrame *ethernetframe)
{
    this->printHex(ethernetframe->getPreamble(), 8, "Packet # " + std::to_string(frameNum) + ":\n");
    this->printHex(ethernetframe->getDestinationAddress(), 6);
    this->printHex(ethernetframe->getSourceAddress(), 6);
    this->printHex(ethernetframe->getType(), 2);

    unsigned char *protocolVersion = new unsigned char[1];
    protocolVersion[0] = ethernetframe->getProtocolVersion();
    this->printHex(protocolVersion, 1);

    unsigned char *messageTypeFormatted = new unsigned char[1];
    messageTypeFormatted[0] = ethernetframe->getMessageType();
    this->printHex(messageTypeFormatted, 1);

    unsigned char *ecpriPayloadLengthFormatted = new unsigned char[2];
    int ecpriPayloadLength = ethernetframe->getECPRIPayloadLength();
    ecpriPayloadLengthFormatted[0] = (ecpriPayloadLength >> 8) & 0xFF;
    ecpriPayloadLengthFormatted[1] = ecpriPayloadLength & 0xFF;
    this->printHex(ecpriPayloadLengthFormatted, 2);

    this->printHex(ethernetframe->getRtcId(), 2);
    this->printHex(ethernetframe->getSeqId(), 2);
    this->printHex(ethernetframe->getRtcData(), ecpriPayloadLength - 4, "", true);
    this->printHex(ethernetframe->getFcs(), 4, "", true);

    this->printHex(ethernetframe->getFcs(), 4, "CRC: ", true);

    unsigned char *concatinationIndicatorFormatted = new unsigned char[1];
    concatinationIndicatorFormatted[0] = ethernetframe->getConcatenationIndicator();

    this->printHex(concatinationIndicatorFormatted, 1, "Concatenation Indicator: ", true);
    this->printHex(ethernetframe->getDestinationAddress(), 6, "Destination Address: ", true);
    this->printHex(messageTypeFormatted, 1, "Message Type: ", true);
    this->printHex(ecpriPayloadLengthFormatted, 2, "Payload Size: ", true);
    this->printHex(protocolVersion, 1, "Protocol Version: ", true);
    this->printHex(ethernetframe->getRtcId(), 2, "RTC ID: ", true);
    this->printHex(ethernetframe->getSeqId(), 2, "Sequence ID: ", true);
    this->printHex(ethernetframe->getSourceAddress(), 6, "Source Address: ", true);
    this->printHex(ethernetframe->getType(), 2, "Type: ", true);

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::printHex(unsigned char *data, size_t size, std::string prefix, bool addNewLine)
{
    *(this->fileStream) << prefix;

    for (size_t i = 0; i < size; i++)
    {
        *(this->fileStream) << std::hex << std::setfill('0') << std::setw(2) << +data[i];
    }

    if (addNewLine)
    {
        *(this->fileStream) << "\n";
    }
}

PrinterEthernetFrameVisitor::~PrinterEthernetFrameVisitor()
{
    if (this->fileStream != nullptr)
    {
        delete this->fileStream;
    }
}