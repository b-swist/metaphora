#include "dbus.h"
#include "tui.h"

int main() {
	auto backend = createDbusBackend();
	auto devices = backend->devices();

	runApp(devices);

	return 0;
}
