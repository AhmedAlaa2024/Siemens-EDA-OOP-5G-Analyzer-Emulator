#ifndef PRINTERETHERNETFRAMEVISITOR_H
#define PRINTERETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class PrinterEthernetFrameVisitor
{
protected:
    Logger *fileLogger;
    Logger *consoleLogger;

public:
    PrinterEthernetFrameVisitor() {};

    // virtual void visit(RawEthernetFrame ethernetframe);
    // virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

    ~PrinterEthernetFrameVisitor() {};
};

#endif // PRINTERETHERNETFRAMEVISITOR_H