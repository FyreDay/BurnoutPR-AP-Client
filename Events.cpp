#include "pch.h"
#include "Events.h"



void Events::OnGameEvent(const uint8_t* eventData, int32_t eventID, uint32_t eventSize)
{
    if (eventID == 131 || eventID == 135 || eventID == 138) return;
    std::stringstream ss;
	ss << eventID << ", [" << eventSize << "]\n";
    for (uint32_t i = 0; i < eventSize; ++i)
    {
        ss << " " << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(eventData[i]);
    }
    //Logger::Get().Log(ss.str());
}

void Events::OnBreak(const uint32_t* type, const uint32_t gateId, uint32_t mod)
{
    std::stringstream ss;
    if (*type == 0x0004E413) {
        ss << "Gate Destoryed: ";
    }else if (*type == 0x000712C2) {
        ss << "BillBoard Destroyed: ";
    }
    else if (*type == 0x0004E412) {
        ss << "Super Jump!: ";
    } else {
        ss << "Unknown Increment id " << std::hex << *type << " : " ;
    }
    
    ss << gateId << " : " << mod;
    Logger::Get().Log(ss.str());
}


