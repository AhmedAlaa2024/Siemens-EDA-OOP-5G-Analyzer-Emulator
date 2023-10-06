#include <EthernetPacketParser/EthernetPacketParser.h>

#include <EthernetFrame/EthernetFrame.h>
#include <EthernetFrame/ECPRIEthernetFrame.h>
#include <EthernetFrame/RawEthernetFrame.h>

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>

#include <string.h>

struct EthernetFrameHeaders
{
    unsigned char preamble[9];
    unsigned char destination[7];
    unsigned char source[7];
    unsigned char type[3];
    unsigned char payload[1501];
    unsigned char crc[5];
};

struct ECPRIEthernetFrameHeaders
{
    unsigned char protocolVersion;
    unsigned char concatenationIndicator;
    unsigned char messageType;
    unsigned char rtcId[3];
    unsigned char seqId[3];
    int eCPRIpayloadLength;
    unsigned char rtcData[1501];
};

EthernetPacketParser::EthernetPacketParser()
{
    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));

    this->logger->log("Creating new EthernetPacketParser", Severity::INFO);
}

EthernetFrame *EthernetPacketParser::parsePacket(const unsigned char *packet, int packetSize)
{
    this->logger->log("Parsing packet...", Severity::INFO);

    struct EthernetFrameHeaders headers;

    /* First, Copy all the headers of the packet from the beginning of the string */
    memcpy(headers.preamble, packet, 8);
    headers.preamble[8] = '\0';

    memcpy(headers.destination, packet + 8, 6);
    headers.destination[6] = '\0';

    memcpy(headers.source, packet + 14, 6);
    headers.source[6] = '\0';

    memcpy(headers.type, packet + 20, 2);
    headers.type[2] = '\0';

    /* Second, Copy the payload (data) itself from the right boundries of the packet string */
    memcpy(headers.payload, packet + 22, packetSize - 26);
    headers.payload[packetSize - 26] = '\0';

    /* Finaly, Copy the last 4 bytes as FCS (CRC) */
    memcpy(headers.crc, packet + packetSize - 4, 4);
    headers.crc[4] = '\0';

    this->logger->log("Packet parsed successfully", Severity::INFO);

    /* Check if the headers.type (in hex) == "AEFE" (in hex) [which is equivalent to 44798 (in decimal)] */
    if (headers.type[0] == 0xAE && headers.type[1] == 0xFE)
    {
        struct ECPRIEthernetFrameHeaders ecpriHeaders;

        /* First, Copy all the headers of the packet from the beginning of the string */
        ecpriHeaders.protocolVersion = (headers.payload[0] >> 4) & 0x0F;
        ecpriHeaders.concatenationIndicator = (headers.payload[0] & 0x0F);

        ecpriHeaders.messageType = headers.payload[1];

        memcpy(&(ecpriHeaders.eCPRIpayloadLength), headers.payload + 2, 2);

        memcpy(ecpriHeaders.rtcId, headers.payload + 4, 2);
        ecpriHeaders.rtcId[2] = '\0';

        memcpy(ecpriHeaders.seqId, headers.payload + 6, 2);
        ecpriHeaders.seqId[2] = '\0';

        /* Second, Copy the payload (data) itself from the right boundries of the packet string */
        memcpy(ecpriHeaders.rtcData, headers.payload + 8, packetSize - 34);
        ecpriHeaders.rtcData[packetSize - 34] = '\0';

        this->logger->log("ECPRI packet parsed successfully", Severity::INFO);

        return new ECPRIEthernetFrame(headers.preamble, headers.destination, headers.source, headers.type, headers.crc, packetSize - 26,
                                      ecpriHeaders.protocolVersion, ecpriHeaders.concatenationIndicator, ecpriHeaders.messageType, ecpriHeaders.rtcId,
                                      ecpriHeaders.seqId, ecpriHeaders.eCPRIpayloadLength, ecpriHeaders.rtcData);
    }
    else
    {
        this->logger->log("Raw packet parsed successfully", Severity::INFO);

        return new RawEthernetFrame(headers.preamble, headers.destination, headers.source, headers.type, headers.crc, packetSize - 26, headers.payload);
    }
}

EthernetPacketParser::~EthernetPacketParser()
{
    this->logger->log("Destroying EthernetPacketParser", Severity::INFO);

    if (this->logger != NULL)
    {
        delete this->logger;
    }
}