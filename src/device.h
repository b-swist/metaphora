#ifndef METAPHORA_DEVICE_H
#define METAPHORA_DEVICE_H

#include <string>
#include <vector>

enum class DeviceType {
	Unknown,
	Desktop,
	Laptop,
	Phone,
	Tablet,
	TV,
};

DeviceType deviceTypeFromString(std::string);
std::string toString(DeviceType);

enum class PairState {
	Unpaired,
	Requested,
	RequestedByPeer,
	Paired,
};

std::string toString(PairState);

struct Device {
	std::vector<std::string> loadedPlugins;
	std::string id;
	std::string name;
	DeviceType type;
	PairState pairState;
	bool reachable;
	bool paired;
};

#endif // METAPHORA_DEVICE_H
