![Continuous Integration](https://github.com/fredemmott/StreamDeck-CPPSDK/workflows/Continuous%20Integration/badge.svg)

# What is this?

This is re-usable library derived from the Elgato's
[CPU plugin](https://github.com/elgatosf/streamdeck-cpu).

It is currently based on [a version from 2019-05-27](https://github.com/elgatosf/streamdeck-cpu/commit/0a9c2557fbe6f829f3456a272672f810291948b3). This is:
- the latest provided by Elgato as of 2020-06-06
- targetted at the 4.3 SDK

This library has been bundled with and used by several plugins for since January 2019:
- Audio Mute/Mic Mute
- Audio Switcher
- Discord Self-Mute/Self-Deafen

# What's changed from the Elgato SDK?

- additional SDK features:
  - `ESDBasePlugin::DidReceiveGlobalSettings()`
  - `ESDBasePlugin::DidReceiveSettings()`
  - `ESDConnectionManager::GetGlobalSettings()`
  - `ESDConnectionManager::SetGlobalSettings()`
  - `ESDUtilities::GetFileName()`
- easier re-use, portability, and extensibility:
  - no use of precompiled headers
  - CMake build system that supports both MacOS and Windows
  - No longer provides a `main()` function; instead, provides
    `esd_main(int argc, char** argv, ESDBasePlugin* plugin)`; this
    gives you more flexibility, and no longer requires your plugin to be defined
    as `MyStreamDeckPlugin`
  - does not require your plugin to implement every potential `ESDBasePlugin` method
- adds `ESDLogger` class, replacing `DebugPrint()`
  - in release builds, logs to streamdeck log files
  - in debug builds, also logs to OS debug logs, e.g. dbgview.exe or MacOS
    Console.app
  - adds `ESDLog()` macro for things that should always be logged, including in
    release builds
  - adds `ESDDebug()` macro, which is an alias for `ESDLog()` in debug builds, and
    does nothing in release build
  - MacOS: disables debug log censorship in Catalina and above
  - Win32: adds option for debug log prefix; this is useful for filtering in
    dbgview.exe
- `nlohmann::json` is no longer aliased in header files
- uses more recent versions of nlohmann/json, WebSocket++, and chriskohlhoff/asio
- exposes CMake library targets for dependencies

# Adding this to a CMake project

1. Download `StreamDeckSDK.cmake` from
[the latest release](https://github.com/fredemmott/StreamDeck-CPPSDK/releases/latest)
2. `include()` it in your project
3. A `StreamDeckSDK` static library is now available in your project; depending on it
   will also make nlohmann/json, websocketpp, and asio available in your project,
   including header files.

For example:

```cmake
include("StreamDeckSDK.cmake")
add_executable(
  myplugin
  MyStreamDeckPlugin.cpp
  main.cpp
)
target_link_libraries(myplugin StreamDeckSDK)
```

For a more involved example, see
[StreamDeck-Discord](https://github.com/fredemmott/StreamDeck-Discord).

To update, replace `StreamDeckSDK.cmake` with the newer version and address any
incompatibilities.

# Porting from Elgato's code

First, you need to add a main function; this is usually very short, and looks
something like:

```c++
#include "MyStreamDeckPlugin.h"

#include <StreamDeckSDK/ESDMain.h>
#include <StreamDeckSDK/ESDLogger.h>

int main(int argc, const char** argv) {
  // Makes it easy to filter in dbgview.exe
  ESDLogger::Get()->SetWin32DebugPrefix("[MyPluginName] ");
  return esd_main(argc, argv, new MyStreamDeckPlugin());
}
```

You will then need to do several smaller changes:
- replace `#include "../Common/Foo.h"` with `#include <StreamDeckSDK/Foo.h>`
- remove references to `pch.h`
  - if you're using `DebugPrint()`, replace with `#include <StreamDeckSDK/ESDDebug.h>`
    and call `ESDDebug()` instead - or `ESDLog()` if you want it in the log files
    in release builds
  - otherwise, directly include the header files you want
- add `#include <nlohmann/json.hpp>` when needed
- either add `using json = nlohmann::json;`, or replace `json` with `nlohmann::json`
