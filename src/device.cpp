#include <algorithm>
#include <unordered_map>

#include "device.h"

DeviceType deviceTypeFromString(std::string device) {
	std::transform(device.begin(), device.end(), device.begin(), [](unsigned char c) {
		return static_cast<char>(std::tolower(c));
	});

	static const std::unordered_map<std::string_view, DeviceType> types{
	    {"desktop", DeviceType::Desktop},
	    {"laptop",  DeviceType::Laptop },
	    {"phone",   DeviceType::Phone  },
	    {"tablet",  DeviceType::Tablet },
	    {"tv",      DeviceType::TV     },
	};

	const auto it = types.find(device);
	if (it == types.end()) {
		return DeviceType::Unknown;
	}

	return it->second;
}

std::string toString(DeviceType device) {
	static const std::unordered_map<DeviceType, std::string> types{
	    {DeviceType::Unknown, "Unknown"},
	    {DeviceType::Desktop, "Desktop"},
	    {DeviceType::Laptop,  "Laptop" },
	    {DeviceType::Phone,   "Phone"  },
	    {DeviceType::Tablet,  "Tablet" },
	    {DeviceType::TV,      "TV"     },
	};

	return types.at(device);
};

std::string toString(PairState state) {
	static const std::unordered_map<PairState, std::string> states{
	    {PairState::Unpaired,        "Unpaired"         },
	    {PairState::Requested,       "Requested"        },
	    {PairState::RequestedByPeer, "Requested by peer"},
	    {PairState::Paired,          "Paired"           },
	};

	return states.at(state);
};
