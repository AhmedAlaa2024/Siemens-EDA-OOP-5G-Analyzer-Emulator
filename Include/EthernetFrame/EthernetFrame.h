#ifndef ETHERNETFRAME_H_
#define ETHERNETFRAME_H_

#include <Logger/Logger.h>

class PrinterEthernetFrameVisitor;

class EthernetFrame
{
protected:
    unsigned char preamble[9];
    unsigned char destinationAddress[7];
    unsigned char sourceAddress[7];
    unsigned char type[3];
    unsigned char fcs[5];
    int payloadSize;

    Logger *logger;

public:
    EthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
                  unsigned char *type, unsigned char *fcs, int payloadSize);

    /* Take care that the following functions allocate a string dynamically and you need to free it manually after use */
    unsigned char *getPreamble();
    unsigned char *getDestinationAddress();
    unsigned char *getSourceAddress();
    unsigned char *getType();
    unsigned char *getFcs();

    int getPayloadSize();

    virtual void accept(PrinterEthernetFrameVisitor &validatorEthernetFrameVisitor) = 0;

    ~EthernetFrame();
};

#endif