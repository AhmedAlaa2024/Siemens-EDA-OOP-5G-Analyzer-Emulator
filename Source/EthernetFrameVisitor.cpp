#include <EthernetFrameVisitor/EthernetFrameVisitor.h>

EthernetFrameVisitor::EthernetFrameVisitor()
{
    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");
    this->consoleLogger->setSuccessor(this->fileLogger);
}
EthernetFrameVisitor::~EthernetFrameVisitor() {}