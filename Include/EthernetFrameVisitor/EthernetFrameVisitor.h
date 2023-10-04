#ifndef ETHERNETFRAMEVISITOR_H
#define ETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class EthernetFrameVisitor
{
protected:
    Logger *fileLogger;
    Logger *consoleLogger;

public:
    EthernetFrameVisitor();

    // virtual void visit(RawEthernetFrame ethernetframe);
    // virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

    ~EthernetFrameVisitor();
};

#endif // ETHERNETFRAMEVISITOR_H