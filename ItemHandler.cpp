#include "pch.h"
#include "ItemHandler.h"

std::vector<int> ItemHandler::foundIds = {};

bool ItemHandler::HasEvent(const uint32_t* eventId)
{

	auto it = std::find(foundIds.begin(), foundIds.end(), static_cast<int>(*eventId));
	if (it == foundIds.end()) {
		foundIds.push_back(*eventId);
		std::stringstream ss;
		ss << "Found an Event!! :" << *eventId;
		Logger::Get().Log(ss.str());
	}
	
	return 0;
}
