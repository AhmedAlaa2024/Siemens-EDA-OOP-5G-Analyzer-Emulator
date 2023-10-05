#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

#include <Simulator/Simulator.h>

int main()
{
    Logger *logger = new ConsoleLogger();
    logger->setSuccessor(new FileLogger("Simulation.log"));

    logger->log("Starting Simulation...", Severity::INFO);

    Simulator *simulator = new Simulator();
    simulator->simulate();

    logger->log("Ending Simulation...", Severity::INFO);

    return 0;
}