#ifndef ETHERNETPACKETPARSER_H
#define ETHERNETPACKETPARSER_H

#include <EthernetFrame/EthernetFrame.h>
#include <Logger/Logger.h>

class EthernetPacketParser
{
    private:
        Logger* logger;

    public:
        EthernetPacketParser();

        EthernetFrame* parsePacket(const unsigned char *packet, int packetSize);
        
        ~EthernetPacketParser();

};

#endif // ETHERNETPACKETPARSER_H