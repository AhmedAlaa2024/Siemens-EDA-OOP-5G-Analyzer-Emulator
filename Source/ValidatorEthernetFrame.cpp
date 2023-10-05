#include <ValidatorEthernetFrame/ValidatorEthernetFrame.h>
#include <string>

ValidatorEthernetFrame* ValidatorEthernetFrame::validator = nullptr;   

ValidatorEthernetFrame::ValidatorEthernetFrame()
{
    this->logger = new ConsoleLogger();
    this->logger->setSuccessor(new FileLogger("Simulation.log"));

    this->logger->log("Creating new Validator for Ethernert Frame", Severity::INFO);

}
ValidatorEthernetFrame *ValidatorEthernetFrame::getInstance()
{
    if(validator == nullptr){
        validator = new ValidatorEthernetFrame();
    }
    return validator;
}

bool ValidatorEthernetFrame::validateEthernetFrame(int ethernetFrameSize)
{
    bool isValid = true;
    if(ethernetFrameSize < 144 || ethernetFrameSize > 1526)isValid = false;
    if(ethernetFrameSize % 2)isValid = false;

    if(!isValid){
        this->logger->log("INVALID INPUT FILE", Severity::ERROR);
        return false;
    }
    this->logger->log("VALID INPUT FILE", Severity::INFO);
    return true;
}

bool ValidatorEthernetFrame::validateRawEthernetFrame(int rawEthernetFrameSize)
{
    this->logger->log("VALID RAW ETHERNET FRAME", Severity::INFO);
    return true;
}

bool ValidatorEthernetFrame::validateECPRIEthernetFrame(int ecpriEthernetFrameSize)
{
    int startPayloadData = 22, endPayloadData = ecpriEthernetFrameSize - 5;
    startPayloadData += 8;

    if(startPayloadData <= endPayloadData){
        this->logger->log("VALID ECPRI ETHERNET FRAME", Severity::INFO);
        return true;
    }
    else{
        this->logger->log("INVALID ECPRI ETHERNET FRAME", Severity::ERROR);
        return false;
    }
}

ValidatorEthernetFrame::~ValidatorEthernetFrame()
{
    delete this->logger;
}