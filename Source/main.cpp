#include <iostream>
#include <string.h>

#include <EthernetPacketParser/EthernetPacketParser.h>

#include <EthernetFrame/EthernetFrame.h>
#include <EthernetFrame/ECPRIEthernetFrame.h>
#include <EthernetFrame/RawEthernetFrame.h>

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>


int main() {
    Logger *logger = new ConsoleLogger();
    logger->setSuccessor(new FileLogger("Simulation.log"));

    logger->log("Starting Simulation...", Severity::INFO);


    unsigned char packetInHex[] = "FB555555555555D50000000000C1ECCD655507D9AEFE1002001480680080900000000101D10000100000FFFE7E0400000000000000000000000000000000000000000000B329AA60";
    int packetInHexSize = sizeof(packetInHex)/(2 * sizeof(packetInHex[0]));

    EthernetPacketParser ethernetPacketParser;

    EthernetFrame *ethernetFrame = ethernetPacketParser.parsePacket(packetInHex, packetInHexSize);

    delete ethernetFrame;

    logger->log("Ending Simulation...", Severity::INFO);

    return 0;
}