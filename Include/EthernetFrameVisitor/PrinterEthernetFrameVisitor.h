#ifndef PRINTERETHERNETFRAMEVISITOR_H
#define PRINTERETHERNETFRAMEVISITOR_H

#include <fstream>

#include <Logger/ConsoleLogger.h>
#include <Logger/FileLogger.h>
#include <EthernetFrameVisitor/EthernetFrameVisitor.h>

class PrinterEthernetFrameVisitor : EthernetFrameVisitor
{
    private:
        std::fstream *fileStream;

    public:
        PrinterEthernetFrameVisitor(std::string fileName);

        void visit(RawEthernetFrame *ethernetframe);
        void visit(ECPRIEthernetFrame *ecpriEthernetFrame);

        ~PrinterEthernetFrameVisitor();

    private:
        static int frameNum;

        void printHex(unsigned char *data, size_t size, std::string prefix = "", bool addNewLine = false);
};

#endif // PRINTERETHERNETFRAMEVISITOR_H