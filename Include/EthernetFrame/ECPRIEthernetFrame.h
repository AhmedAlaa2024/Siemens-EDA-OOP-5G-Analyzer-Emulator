#ifndef ECPRIETHERNETFRAME_H_
#define ECPRIETHERNETFRAME_H_

#include <EthernetFrame/EthernetFrame.h>

class ECPRIEthernetFrame : public EthernetFrame
{
private:
    unsigned char protocolVersion;
    unsigned char concatenationIndicator;
    unsigned char messageType;
    unsigned char rtcId[3];
    unsigned char seqId[3];
    int eCPRIPayloadLength;
    unsigned char *rtcData;

public:
    ECPRIEthernetFrame(unsigned char *fullFrame, int frameLength, unsigned char *preamble, unsigned char *destinationAddress, unsigned char *sourceAddress,
                       unsigned char *type, unsigned char *fcs, int payloadSize, unsigned char protocolVersion, unsigned char concatenationIndicator,
                       unsigned char messageType, unsigned char *rtcId, unsigned char *seqId, int eCPRIpayloadLength, unsigned char *rtcData);

    unsigned char getProtocolVersion();
    unsigned char getConcatenationIndicator();
    unsigned char getMessageType();
    unsigned char *getRtcId();
    unsigned char *getSeqId();
    int getECPRIPayloadLength();
    unsigned char *getRtcData();

    void accept(PrinterEthernetFrameVisitor &printerEthernetFrameVisitor);

    ~ECPRIEthernetFrame();
};

#endif