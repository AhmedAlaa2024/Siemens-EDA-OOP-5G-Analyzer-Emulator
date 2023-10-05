#ifndef VALIDATORETHERNETFRAME_H
#define VALIDATORETHERNETFRAME_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

class ValidatorEthernetFrame{
    private:
        Logger *fileLogger;
        Logger *consoleLogger;

    public:
        ValidatorEthernetFrame();

        bool validateEthernetFrame(unsigned char* ethernetFrame, int ethernetFrameSize);
        bool validateRawEthernetFrame(unsigned char* rawEthernetFrame, int rawEthernetFrameSize);
        bool validateECPRIEthernetFrame(unsigned char* ecpriEthernetFrame, int ecpriEthernetFrameSize);

        ~ValidatorEthernetFrame();
};

#endif