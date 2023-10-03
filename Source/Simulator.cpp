#include <iostream>

#include <Simulator/Simulator.h>

Simulator::Simulator()
{
    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");

    consoleLogger->setSuccessor(fileLogger);
}

void Simulator::simulate()
{
    this->consoleLogger->log("Simulation starts now!", Severity::INFO);
}

Simulator::~Simulator() {
    delete this->consoleLogger;
    delete this->fileLogger;
}