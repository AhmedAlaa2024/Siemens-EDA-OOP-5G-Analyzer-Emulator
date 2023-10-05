#ifndef VALIDATORETHERNETFRAME_H
#define VALIDATORETHERNETFRAME_H

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <string>

class ValidatorEthernetFrame{
    protected:
        Logger *logger;
        static ValidatorEthernetFrame* validator;
        ValidatorEthernetFrame();

    public:

        static ValidatorEthernetFrame *getInstance();

        bool validateEthernetFrame(int ethernetFrameSize);
        bool validateRawEthernetFrame(int rawEthernetFrameSize);
        bool validateECPRIEthernetFrame(int ecpriEthernetFrameSize);

        ~ValidatorEthernetFrame();
};

#endif