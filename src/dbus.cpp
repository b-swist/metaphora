#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>

#include "dbus.h"
#include "device.h"

using DeviceProperties = std::map<sdbus::PropertyName, sdbus::Variant>;

class DbusBackend : public IBackend {
public:
	DbusBackend();

	bool isDaemonRunning() override;
	std::vector<Device> devices() override;
	std::optional<Device> device(std::string_view id) override;

private:
	std::unique_ptr<sdbus::IProxy> kProxy;
};

DbusBackend::DbusBackend() {
	sdbus::ServiceName destination{"org.kde.kdeconnect"};
	sdbus::ObjectPath objectPath{"/modules/kdeconnect"};

	this->kProxy = sdbus::createProxy(std::move(destination), std::move(objectPath));
}

std::unique_ptr<IBackend> createDbusBackend() {
	return std::make_unique<DbusBackend>();
}

bool DbusBackend::isDaemonRunning() {
	return true;
}

Device convert(DeviceProperties properties) {
	Device device;

	device.reachable = properties.at(sdbus::PropertyName{"isReachable"}).get<bool>();
	device.paired = properties.at(sdbus::PropertyName{"isPaired"}).get<bool>();
	device.name = properties.at(sdbus::PropertyName{"name"}).get<std::string>();

	auto type = properties.at(sdbus::PropertyName{"type"}).get<std::string>();
	device.type = deviceTypeFromString(type);

	auto pairState = properties.at(sdbus::PropertyName{"pairState"}).get<std::int32_t>();
	device.pairState = static_cast<PairState>(pairState);

	return device;
}

std::vector<Device> DbusBackend::devices() {
	sdbus::InterfaceName daemonInterface{"org.kde.kdeconnect.daemon"};

	std::vector<std::string> deviceIds;
	this->kProxy->callMethod("devices").onInterface(daemonInterface).storeResultsTo(deviceIds);

	std::vector<Device> devices;
	devices.reserve(deviceIds.size());

	for (const std::string &id : deviceIds) {
		auto dev = device(id);
		if (dev.has_value()) {
			devices.push_back(dev.value());
		}
	}

	devices.shrink_to_fit();

	return devices;
}

std::optional<Device> DbusBackend::device(std::string_view id) {
	sdbus::ServiceName destination{"org.kde.kdeconnect"};
	sdbus::InterfaceName deviceInterface{"org.kde.kdeconnect.device"};

	std::string path{"/modules/kdeconnect/devices/"};
	path += id;

	auto objectPath = sdbus::ObjectPath{path};
	auto proxy = sdbus::createProxy(std::move(destination), std::move(objectPath));

	auto properties = proxy->getAllProperties().onInterface(deviceInterface);
	auto device = convert(properties);
	device.id = id;

	return device;
}
