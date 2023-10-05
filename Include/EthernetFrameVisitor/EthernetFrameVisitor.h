#ifndef ETHERNETFRAMEVISITOR_H
#define ETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <EthernetFrame/ECPRIEthernetFrame.h>
#include <EthernetFrame/RawEthernetFrame.h>

class EthernetFrameVisitor{
    EthernetFrameVisitor();
    protected:
        Logger *fileLogger;
        Logger *consoleLogger;

    public:
        virtual void visit(RawEthernetFrame ethernetframe);
        virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

    ~EthernetFrameVisitor();
};

#endif //ETHERNETFRAMEVISITOR_H