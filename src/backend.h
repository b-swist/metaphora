#ifndef METAPHORA_BACKEND_H
#define METAPHORA_BACKEND_H

#include <optional>
#include <string_view>
#include <vector>

#include "device.h"

class IBackend {
public:
	virtual ~IBackend() {}
	virtual bool isDaemonRunning() = 0;
	virtual std::vector<Device> devices() = 0;
	virtual std::optional<Device> device(std::string_view id) = 0;
};

#endif // METAPHORA_BACKEND_H
