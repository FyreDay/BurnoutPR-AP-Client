#pragma once
#include <cstdint>
#include "Logger.h"
#include <sstream>
#include <vector>

class ItemHandler
{
public:
    static bool HasEvent(const uint32_t* eventId);

private:
    static std::vector<int> foundIds;

};