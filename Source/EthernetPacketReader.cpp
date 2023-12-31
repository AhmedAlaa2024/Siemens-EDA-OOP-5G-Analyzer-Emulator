#include <sstream>
#include <string>
#include <iostream>

#include <EthernetPacketReader/EthernetPacketReader.h>
#include <ValidatorEthernetFrame/ValidatorEthernetFrame.h>

EthernetPacketReader::EthernetPacketReader(std::string inputFilePath)
{
    this->inputFileStream.open(inputFilePath);

    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");
    this->consoleLogger->setSuccessor(this->fileLogger);
}

bool EthernetPacketReader::nextLine(unsigned char *line, int *lineLength)
{
    if (!this->inputFileStream.is_open())
    {
        this->consoleLogger->log("FILE IS NOT OPENED", Severity::ERROR);
        return false;
    }

    std::string hexLine;
    if (!std::getline(this->inputFileStream, hexLine))
    {
        return false;
    }

    ValidatorEthernetFrame *ValidatorEthernetFrame = ValidatorEthernetFrame::getInstance();

    if (!ValidatorEthernetFrame->validateEthernetFrame(hexLine.length()))
    {
        return false;
    }

    // Convert every two consecutive characters to an integer base 16
    *lineLength = hexLine.length() / 2;
    for (size_t i = 0; i < hexLine.length(); i += 2)
    {
        line[i / 2] = std::stoi(hexLine.substr(i, 2), nullptr, 16);
    }

    return true;
}

EthernetPacketReader::~EthernetPacketReader()
{
    this->inputFileStream.close();
}