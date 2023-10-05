#include <ValidatorEthernetFrame/ValidatorEthernetFrame.h>
#include <string.h>

ValidatorEthernetFrame::ValidatorEthernetFrame()
{
    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");

    consoleLogger->setSuccessor(fileLogger);
}


bool ValidatorEthernetFrame::validateEthernetFrame(unsigned char* ethernetFrame, int ethernetFrameSize)
{
    bool isValid = true;
    if(ethernetFrameSize < 72 || ethernetFrameSize > 1526)isValid = false;
    if(ethernetFrameSize % 2)isValid = false;

    if(!isValid){
        this->consoleLogger->log("INVALID INPUT FILE", Severity::ERROR);
        return false;
    }
    return true;
}

bool ValidatorEthernetFrame::validateRawEthernetFrame(unsigned char* rawEthernetFrame, int rawEthernetFrameSize)
{
    return true;
}

bool ValidatorEthernetFrame::validateECPRIEthernetFrame(unsigned char* ecpriEthernetFrame, int ecpriEthernetFrameSize)
{
    int startPayloadData = 22, endPayloadData = ecpriEthernetFrameSize - 5;
    startPayloadData += 8;

    if(startPayloadData <= endPayloadData){
        return true;
    }
    else{
        this->consoleLogger->log("INVALID ECPRI ETHERNET FRAME", Severity::ERROR);
        return false;
    }
}

ValidatorEthernetFrame::~ValidatorEthernetFrame()
{
    delete this->consoleLogger;
    delete this->fileLogger;
}