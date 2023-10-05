#include <ValidatorEthernetFrame/ValidatorEthernetFrame.h>
#include <string.h>

ValidatorEthernetFrame::ValidatorEthernetFrame()
{
    this->consoleLogger = new ConsoleLogger();
    this->fileLogger = new FileLogger("Simulation.log");

    consoleLogger->setSuccessor(fileLogger);
}


bool ValidatorEthernetFrame::validateEthernetFrame(char* ethernetFrame)
{
    int EthernetFrameSize = (int)strlen(ethernetFrame);
    bool isValid = true;
    if(EthernetFrameSize < 144 || EthernetFrameSize > 1526)isValid = false;
    if(EthernetFrameSize % 2)isValid = false;

    if(!isValid){
        this->consoleLogger->log("INVALID INPUT FILE", Severity::ERROR);
        return false;
    }
    return true;
}

bool ValidatorEthernetFrame::validateRawEthernetFrame(char* rawEthernetFrame)
{
    return true;
}

bool ValidatorEthernetFrame::validateECPRIEthernetFrame(char* ecpriEthernetFrame)
{
    int EthernetFrameSize = (int)strlen(ecpriEthernetFrame);
    int startPayloadData = 44, endPayloadData = EthernetFrameSize - 9;
    startPayloadData += 16;

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