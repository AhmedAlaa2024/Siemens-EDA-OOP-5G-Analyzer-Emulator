#include <sstream>
#include <string>
#include <iostream>

#include <EthernetPacketReader/EthernetPacketReader.h>

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

    *lineLength = hexLine.length() / 2;

    for (size_t i = 0; i < hexLine.length(); i += 2)
    {
        line[i] = std::stoi(hexLine.substr(i, 2), nullptr, 16);
    }

    return true;
}

EthernetPacketReader::~EthernetPacketReader()
{
    this->inputFileStream.close();
}