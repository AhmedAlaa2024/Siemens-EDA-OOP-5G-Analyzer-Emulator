#ifndef VALIDATORETHERNETFRAMEVISITOR_H
#define VALIDATORETHERNETFRAMEVISITOR_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class ValidatorEthernetFrameVisitor
{
protected:
    Logger *fileLogger;
    Logger *consoleLogger;

public:
    ValidatorEthernetFrameVisitor();

    // virtual void visit(RawEthernetFrame ethernetframe);
    // virtual void visit(ECPRIEthernetFrame ecpriEthernetFrame);

    ~ValidatorEthernetFrameVisitor();
};

#endif // VALIDATORETHERNETFRAMEVISITOR_H