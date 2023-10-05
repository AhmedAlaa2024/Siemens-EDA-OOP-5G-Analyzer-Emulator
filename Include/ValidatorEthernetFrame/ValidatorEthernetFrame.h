#ifndef VALIDATORETHERNETFRAME_H
#define VALIDATORETHERNETFRAME_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class ValidatorEthernetFrame{
    private:
        Logger *fileLogger;
        Logger *consoleLogger;

    public:
        ValidatorEthernetFrame(){}

        bool validateEthernetFrame(char* ethernetFrame){}
        bool validateRawEthernetFrame(char* rawEthernetFrame){}
        bool validateECPRIEthernetFrame(char* ecpriEthernetFrame){}

        ~ValidatorEthernetFrame(){}
};

#endif