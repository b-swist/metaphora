ftxui = dependency('ftxui', version : '7.0.3')
sdbus = dependency('sdbus-c++')

dependencies = [
  ftxui,
  sdbus,
]

sources = [
  'main.cpp',
  'dbus.cpp',
  'device.cpp',
  'tui.cpp',
]

exe = executable(
  'metaphora',
  sources,
  install : true,
  dependencies : dependencies,
)
