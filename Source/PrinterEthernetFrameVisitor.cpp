#include <sstream>
#include <string.h>
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
    /* Carry the output of each getter in a pointer to be able to delete it */
    unsigned char* tempPtr;

    tempPtr = ethernetframe->getPreamble();
    this->printHex(ethernetframe->getPreamble(), 8, "Packet # " + std::to_string(frameNum) + ":\n");
    delete tempPtr;
    
    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(ethernetframe->getDestinationAddress(), 6);
    delete tempPtr;
    
    tempPtr = ethernetframe->getSourceAddress();
    this->printHex(ethernetframe->getSourceAddress(), 6);
    delete tempPtr;
    
    tempPtr = ethernetframe->getType();
    this->printHex(ethernetframe->getType(), 2);
    delete tempPtr;
    
    tempPtr = ethernetframe->getPayload();
    this->printHex(ethernetframe->getPayload(), ethernetframe->getPayloadSize());
    delete tempPtr;
    
    tempPtr = ethernetframe->getFcs();
    this->printHex(ethernetframe->getFcs(), 4, "", true);
    delete tempPtr;

    tempPtr = ethernetframe->getFcs();
    this->printHex(ethernetframe->getFcs(), 4, "CRC: ", true);
    delete tempPtr;
    
    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(ethernetframe->getDestinationAddress(), 6, "Destination Address: ", true);
    delete tempPtr;
    
    tempPtr = ethernetframe->getSourceAddress();
    this->printHex(ethernetframe->getSourceAddress(), 6, "Source Address: ", true);
    delete tempPtr;
    
    tempPtr = ethernetframe->getType();
    this->printHex(ethernetframe->getType(), 2, "Type: ", true);
    delete tempPtr;

    *(this->fileStream) << std::endl << "**************************************************************************************************************************************************************************************************************************************" << std::endl << std::endl;

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::visit(ECPRIEthernetFrame *ethernetframe)
{
    /* Carry the output of each getter in a pointer to be able to delete it */
    unsigned char* tempPtr;

    tempPtr = ethernetframe->getPreamble();
    this->printHex(tempPtr, 8, "Packet # " + std::to_string(frameNum) + ":\n");
    delete tempPtr;

    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(ethernetframe->getDestinationAddress(), 6);
    delete tempPtr;

    tempPtr = ethernetframe->getSourceAddress();
    this->printHex(ethernetframe->getSourceAddress(), 6);
    delete tempPtr;

    tempPtr = ethernetframe->getType();
    this->printHex(ethernetframe->getType(), 2);
    delete tempPtr;

    unsigned char *protocolVersion = new unsigned char[1];
    protocolVersion[0] = ethernetframe->getProtocolVersion();
    this->printHex(protocolVersion, 1);

    unsigned char *messageTypeFormatted = new unsigned char[1];
    messageTypeFormatted[0] = ethernetframe->getMessageType();
    this->printHex(messageTypeFormatted, 1);

    unsigned char *ecpriPayloadLengthFormatted = new unsigned char[2];
    unsigned int ecpriPayloadLength = ethernetframe->getECPRIPayloadLength();

    ecpriPayloadLengthFormatted[0] = (ecpriPayloadLength >> 8) & 0xFF;
    ecpriPayloadLengthFormatted[1] = ecpriPayloadLength & 0xFF;
    this->printHex(ecpriPayloadLengthFormatted, 2);

    tempPtr = ethernetframe->getRtcId();
    this->printHex(ethernetframe->getRtcId(), 2);
    delete tempPtr;

    tempPtr = ethernetframe->getSeqId();
    this->printHex(ethernetframe->getSeqId(), 2);
    delete tempPtr;

    tempPtr = ethernetframe->getRtcData();
    this->printHex(ethernetframe->getRtcData(), ecpriPayloadLength, "");
    delete tempPtr;

    tempPtr = ethernetframe->getFcs();
    this->printHex(ethernetframe->getFcs(), 4, "", true);
    delete tempPtr;

    tempPtr = ethernetframe->getFcs();
    this->printHex(ethernetframe->getFcs(), 4, "CRC: ", true);
    delete tempPtr;


    unsigned char *concatinationIndicatorFormatted = new unsigned char[1];
    concatinationIndicatorFormatted[0] = ethernetframe->getConcatenationIndicator();

    this->printHex(concatinationIndicatorFormatted, 1, "Concatenation Indicator: ", true);
    
    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(ethernetframe->getDestinationAddress(), 6, "Destination Address: ", true);
    delete tempPtr;
    
    this->printHex(messageTypeFormatted, 1, "Message Type: ", true);
    this->printHex(ecpriPayloadLengthFormatted, 2, "Payload Size: ", true);

    this->printHex(protocolVersion, 1, "Protocol Version: ", true);
    
    tempPtr = ethernetframe->getRtcId();
    this->printHex(ethernetframe->getRtcId(), 2, "RTC ID: ", true);
    delete tempPtr;

    tempPtr = ethernetframe->getSeqId();
    this->printHex(ethernetframe->getSeqId(), 2, "Sequence ID: ", true);
    delete tempPtr;
    
    tempPtr = ethernetframe->getRtcData();
    this->printHex(ethernetframe->getSourceAddress(), 6, "Source Address: ", true);
    delete tempPtr;

    tempPtr = ethernetframe->getRtcData();
    this->printHex(ethernetframe->getType(), 2, "Type: ", true);
    delete tempPtr;

    *(this->fileStream) << std::endl << "**************************************************************************************************************************************************************************************************************************************" << std::endl << std::endl;

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::printHex(unsigned char *data, size_t size, std::string prefix, bool addNewLine)
{
    *(this->fileStream) << prefix;

    unsigned int totalData = 0;

    for (int i = 0; i < size; i++) {
        totalData += data[i];
    }

    for (size_t i = 0; i < size; i++) {
        if (totalData < 0x2 && strcmp(prefix.c_str(), "") != 0) {
            *(this->fileStream) << std::uppercase << std::hex << std::setfill('0') << std::setw(1) << +data[i];
        } else {
            *(this->fileStream) << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << +data[i];
        }
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