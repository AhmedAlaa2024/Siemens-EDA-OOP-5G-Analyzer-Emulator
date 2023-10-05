#ifndef PRINTERETHERNETFRAMEVISITOR_H
#define PRINTERETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <EthernetFrameVisitor/EthernetFrameVisitor.h>
class PrinterEthernetFrameVisitor : EthernetFrameVisitor
{
    public:
       PrinterEthernetFrameVisitor() {};

        virtual void visit(RawEthernetFrame ethernetframe);
        virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

        ~PrinterEthernetFrameVisitor() {};
};

#endif // PRINTERETHERNETFRAMEVISITOR_H