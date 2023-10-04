#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <EthernetPacketReader/EthernetPacketReader.h>

class Simulator
{
private:
    Logger *consoleLogger;
    Logger *fileLogger;

public:
    Simulator();

    void simulate();

    ~Simulator();
};

#endif // SIMULATOR_H