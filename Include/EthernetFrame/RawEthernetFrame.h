#ifndef RAWETHERNETFRAME_H_
#define RAWETHERNETFRAME_H_

#include <EthernetFrame/EthernetFrame.h>

class RawEthernetFrame : public EthernetFrame
{
    private:
        unsigned char *payload;

    public:
        RawEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
            unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char *payload, int payloadSize);

        unsigned char* getPayload();
        
        bool validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor);
        bool print(PrinterEthernetFrameVisitor* printerEthernetFrameVisitor);

        ~RawEthernetFrame();
};

#enfif