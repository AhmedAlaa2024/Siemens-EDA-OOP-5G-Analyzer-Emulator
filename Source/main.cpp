#ifndef TESTING

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <Simulator/Simulator.h>

int main()
{
    Logger* consoleLogger = new ConsoleLogger();
    Logger* fileLogger = new FileLogger("Simulation.log");

    consoleLogger->setSuccessor(fileLogger);
    
    consoleLogger->log("Hello, world!", Severity::INFO);

    Simulator* simulator = new Simulator();
    simulator->simulate();

    delete consoleLogger;
    delete fileLogger;
    delete simulator;

    return 0;
}
#elif

#include "Suites/EthernetFrameTest.cpp"

int main() {
    EthernetFrameTest EthernetFrameTest();

    ethernetFrameTest->setUp_test1();
    ethernetFrameTest->test1();
    return 0;
}

#endif