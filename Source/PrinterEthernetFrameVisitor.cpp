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
    unsigned char *tempPtr;

    // Print full frame first
    tempPtr = ethernetframe->getFullFrame();
    this->printHex(tempPtr, ethernetframe->getFrameLength(), "Packet # " + std::to_string(frameNum) + ":\n", true);
    delete[] tempPtr;

    // Print each field
    tempPtr = ethernetframe->getFcs();
    this->printHex(tempPtr, 4, "CRC: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(tempPtr, 6, "Destination Address: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getSourceAddress();
    this->printHex(tempPtr, 6, "Source Address: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getType();
    this->printHex(tempPtr, 2, "Type: ", true);
    delete[] tempPtr;

    *(this->fileStream) << std::endl
                        << "**************************************************************************************************************************************************************************************************************************************" << std::endl
                        << std::endl;

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::visit(ECPRIEthernetFrame *ethernetframe)
{
    /* Carry the output of each getter in pointers to be able to delete it */
    unsigned char *tempPtr;

    unsigned char *protocolVersion = new unsigned char[1];
    protocolVersion[0] = ethernetframe->getProtocolVersion();

    unsigned char *messageTypeFormatted = new unsigned char[1];
    messageTypeFormatted[0] = ethernetframe->getMessageType();

    unsigned char *concatinationIndicatorFormatted = new unsigned char[1];
    concatinationIndicatorFormatted[0] = ethernetframe->getConcatenationIndicator();

    unsigned char *ecpriPayloadLengthFormatted = new unsigned char[2];
    unsigned int ecpriPayloadLength = ethernetframe->getECPRIPayloadLength();
    ecpriPayloadLengthFormatted[0] = (ecpriPayloadLength >> 8) & 0xFF;
    ecpriPayloadLengthFormatted[1] = ecpriPayloadLength & 0xFF;

    // Print full frame first
    tempPtr = ethernetframe->getFullFrame();
    this->printHex(tempPtr, ethernetframe->getFrameLength(), "Packet # " + std::to_string(frameNum) + ":\n", true);
    delete[] tempPtr;

    // Print each field
    tempPtr = ethernetframe->getFcs();
    this->printHex(tempPtr, 4, "CRC: ", true);
    delete[] tempPtr;

    this->printHex(concatinationIndicatorFormatted, 1, "Concatenation Indicator: ", true);
    delete[] concatinationIndicatorFormatted;

    tempPtr = ethernetframe->getDestinationAddress();
    this->printHex(tempPtr, 6, "Destination Address: ", true);
    delete[] tempPtr;

    this->printHex(messageTypeFormatted, 1, "Message Type: ", true);
    delete[] messageTypeFormatted;

    this->printHex(ecpriPayloadLengthFormatted, 2, "Payload Size: ", true);
    delete[] ecpriPayloadLengthFormatted;

    this->printHex(protocolVersion, 1, "Protocol Version: ", true);
    delete[] protocolVersion;

    tempPtr = ethernetframe->getRtcId();
    this->printHex(tempPtr, 2, "RTC ID: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getSeqId();
    this->printHex(tempPtr, 2, "Sequence ID: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getSourceAddress();
    this->printHex(tempPtr, 6, "Source Address: ", true);
    delete[] tempPtr;

    tempPtr = ethernetframe->getType();
    this->printHex(tempPtr, 2, "Type: ", true);
    delete[] tempPtr;

    *(this->fileStream) << std::endl
                        << "**************************************************************************************************************************************************************************************************************************************" << std::endl
                        << std::endl;

    frameNum++;

    return;
}

void PrinterEthernetFrameVisitor::printHex(unsigned char *data, size_t size, std::string prefix, bool addNewLine)
{
    *(this->fileStream) << prefix;

    unsigned int totalData = 0;

    for (int i = 0; i < size; i++)
    {
        totalData += data[i];
    }

    for (size_t i = 0; i < size; i++)
    {
        if (totalData < 0x2 && strcmp(prefix.c_str(), "") != 0)
        {
            *(this->fileStream) << std::uppercase << std::hex << std::setfill('0') << std::setw(1) << +data[i];
        }
        else
        {
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