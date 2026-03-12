#pragma once
#include <cstdint>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <iomanip>

class Events
{
public:
    static void OnGameEvent(const uint8_t* eventData, int32_t eventID, uint32_t eventSize);
    static void OnBreak(const uint32_t* type, const uint32_t gateId, uint32_t mod);

private:
   

};