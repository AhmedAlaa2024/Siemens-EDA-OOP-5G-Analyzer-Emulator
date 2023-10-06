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

	/**
	 * @brief Fetches the next line from the input file
	 *
	 * @param line Fetched line
	 * @param lineLength Fetched line length
	 * @return true if fetched successfully
	 * @return false if the fetching failed
	 */
	bool nextLine(unsigned char *line, int *lineLength);

	~EthernetPacketReader();
};

#endif