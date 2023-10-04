#ifndef ETHERNETPACKETREADER_H
#define ETHERNETPACKETREADER_H

#include <fstream>
#include <string>

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class EthernetPacketReader
{
private:
	std::ifstream inputFileStream;

	Logger *fileLogger;
	Logger *consoleLogger;

public:
	EthernetPacketReader(std::string inputFilePath);
	bool nextLine(unsigned char *line, int *lineLength);
	~EthernetPacketReader();
};

#endif