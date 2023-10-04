#ifndef Validator_H
#define Validator_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class EthernetFrameVisitor
{
    protected:
        Logger* fileLogger;
        Logger* consoleLogger;
        
    public:
        EthernetFrameVisitor();

        // virtual void visit(RawEthernetFrame ethernetframe);
        // virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

        ~EthernetFrameVisitor();
};



#endif // Validator_H