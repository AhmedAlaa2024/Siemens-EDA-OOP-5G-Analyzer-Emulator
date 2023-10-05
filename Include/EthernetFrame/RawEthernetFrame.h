#ifndef RAWETHERNETFRAME_H_
#define RAWETHERNETFRAME_H_

#include <EthernetFrame/EthernetFrame.h>

// #include <PrinterEthernetFrameVisitor/PrinterEthernetFrameVisitor.h>
// #include <ValidatorEthernetFrameVisitor/ValidatorEthernetFrameVisitor.h>

class RawEthernetFrame : public EthernetFrame
{
    private:
        unsigned char *payload;

    public:
        RawEthernetFrame(unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
            unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char *payload);

        unsigned char* getPayload();
        
        // bool validate(ValidatorEthernetFrameVisitor* validatorEthernetFrameVisitor);
        // bool print(PrinterEthernetFrameVisitor* printerEthernetFrameVisitor);

        ~RawEthernetFrame();
};

#endif /* RAWETHERNETFRAME_H_ */