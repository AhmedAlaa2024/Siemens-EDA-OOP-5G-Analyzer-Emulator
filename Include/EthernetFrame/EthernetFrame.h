#ifndef ETHERNETFRAME_H_
#define ETHERNETFRAME_H_

#include <ValidatorEthernetFrameVisitor/ValidatorEthernetFrameVisitor.h>
#include <PrinterEthernetFrameVisitor/PrinterEthernetFrameVisitor.h>

#include <Logger/Logger.h>

class EthernetFrame
{
    protected:
        unsigned char preamble[8];
        unsigned char destinationAddress[6];
        unsigned char sourceAddress[6];
        unsigned char type[2];
        unsigned char fcs[4];
        int payloadSize;
        
        Logger *logger;

    public:

        EthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
            unsigned char *type, unsigned char *fcs, int payloadSize);

        /* Take care that the following functions allocate a string dynamically and you need to free it manually after use */
        unsigned char* getPreamble();
        unsigned char* getDestinationAddress();
        unsigned char* getSourceAddress();
        unsigned char* getType();
        unsigned char* getFcs();

        int getPayloadSize();

        virtual bool validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor) = 0;
        virtual bool print(PrinterEthernetFrameVisitor* validatorEthernetFrameVisitor) = 0;

        ~EthernetFrame();
};

#endif