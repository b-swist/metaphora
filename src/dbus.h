#ifndef METAPHORA_DBUS_H
#define METAPHORA_DBUS_H

#include <memory>

#include "backend.h"

std::unique_ptr<IBackend> createDbusBackend();

#endif // METAPHORA_DBUS_H
