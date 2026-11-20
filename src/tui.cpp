#include <algorithm>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

#include "device.h"
#include "tui.h"

ftxui::Element DeviceInfo(Device &device) {
	auto info = {ftxui::text(std::format("Name:       {}", device.name)),
	             ftxui::text(std::format("ID:         {}", device.id)),
	             ftxui::text(std::format("Type:       {}", toString(device.type))),
	             ftxui::text(std::format("Pair State: {}", toString(device.pairState))),
	             ftxui::text(std::format("Reachable:  {}", device.reachable ? "True" : "False"))};
	return ftxui::vbox(info) | ftxui::border | ftxui::flex;
}

ftxui::Element DeviceList(ftxui::Component menu) {
	return menu->Render() | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 24);
}

void runApp(std::vector<Device> &devices) {
	std::vector<std::string> names{devices.size()};
	std::transform(devices.begin(), devices.end(), names.begin(), [](Device &d) { return d.name; });

	int selected = 0;

	auto menu = ftxui::Menu(&names, &selected);

	auto root = ftxui::Renderer(menu, [&] {
		auto left = DeviceList(menu);

		auto right = DeviceInfo(devices[selected]);

		return ftxui::window(ftxui::text("metaphora"), ftxui::hbox({left, right}) | ftxui::flex);
	});

	auto screen = ftxui::App::Fullscreen();
	screen.Loop(root);
}
