#ifndef ETHERNETFRAMEVISITOR_H
#define ETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class RawEthernetFrame;
class ECPRIEthernetFrame;

class EthernetFrameVisitor
{
protected:
    Logger *fileLogger;
    Logger *consoleLogger;

public:
    EthernetFrameVisitor();

    virtual void visit(RawEthernetFrame *ethernetframe) = 0;
    virtual void visit(ECPRIEthernetFrame *ecpriEthernetFrame) = 0;

    ~EthernetFrameVisitor();
};

#endif // ETHERNETFRAMEVISITOR_H