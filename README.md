![Continuous Integration](https://github.com/fredemmott/StreamDeck-CPPSDK/workflows/Continuous%20Integration/badge.svg)

# What is this?

This is re-usable library derived from Elgato's
[CPU plugin](https://github.com/elgatosf/streamdeck-cpu), targetting MacOS and Windows. Linux is also tested in case Elgato expand support in the future.

It is currently based on [a version from 2019-05-27](https://github.com/elgatosf/streamdeck-cpu/commit/0a9c2557fbe6f829f3456a272672f810291948b3). This is:
- the latest provided by Elgato as of 2020-06-06
- targetted at the 4.3 SDK - however, StreamDeck-CPPSDK extends this to support the 4.7 SDK

This library has been bundled with and used by several plugins for since January 2019:
- Audio Mute
- Audio Switcher
- Discord
- Streaming Remote

# What's changed from the Elgato SDK?

- additional SDK features:
  - `ESDBasePlugin::DidReceiveGlobalSettings()`
  - `ESDBasePlugin::DidReceiveSettings()`
  - `ESDConnectionManager::GetGlobalSettings()`
  - `ESDConnectionManager::SetGlobalSettings()`
  - `ESDUtilities::GetFileName()`
  - Abstractions for multi-action plugins:
    - `ESDAction`, representing an individual kind of action
    - `ESDPlugin`, an `ESDBasePlugin` subclass for managing instances of
      `ESDAction`
    - `ESDActionWithExternalState`, representing kinds of actions that
      reflect external state, such as hardware state, or state of other
      applications like OBS.
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
- exposes the asio::io_context used for the streamdeck connection, allowing additional sockets/websockets/named pipes to be used in the same event loop
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

For a complete example, there is
[a fork](https://github.com/fredemmott/streamdeck-cpu) of Elgato's CPU plugin.

To update, replace `StreamDeckSDK.cmake` with the newer version and address any
incompatibilities.

## Copying

This is **strongly** discouraged; however if it seems necessary:

1. Copy into a subdirectory of your project
2. `add_subdirectory('StreamDeckCPPSDK/Vendor')`
3. `add_subdirectory('StreamDeckCPPSDK/StreamDeckSDK')`
4. You are now able to directly refer to the `StreamDeckSDK`, `asio`, `json`, and
  `websocketpp` targets.

# Creating new plugins

A [small example](example/) is included.

To build, open Windows Terminal, cmd.exe, Apple Terminal, or iTerm, then:

```
mkdir example/build
cd example/build
cmake ..
cmake --build . --parallel --config Debug
cmake --install . --config Debug
```

When creating your

- update `manifest.json`, `CMakeLists.txt`, and all .cpp and .h files to include your new plugin name and IDs. Your plugin should not contain `com.fredemmott` in any file.
- replace the `StreamDeckSDK.cmake` file with the one from
  [the latest release](https://github.com/fredemmott/StreamDeck-CPPSDK/releases/latest)

# Porting from Elgato's code

First, you need to add a main function; this is usually very short, and looks
something like:

```c++
#include "MyStreamDeckPlugin.h"

#include <StreamDeckSDK/ESDMain.h>
#include <StreamDeckSDK/ESDLogger.h>

int main(int argc, const char** argv) {
  return esd_main(argc, argv, new MyStreamDeckPlugin());
}
```

You will then need to do several smaller changes:
- replace `#include "../Common/Foo.h"` with `#include <StreamDeckSDK/Foo.h>`
- remove references to `pch.h`
  - if you're using `DebugPrint()`, replace with `#include <StreamDeckSDK/ESDDebug.h>`
    and call `ESDDebugf()` instead - or `ESDLogf()` if you want it in the log files
    in release builds
  - consider migrating to `ESDDebug()` andd `ESDLog()` instead, using `fmt::format`, e.g. `ESDDebug("Foo {}", bar)`
  - otherwise, directly include the header files you want
- add `#include <nlohmann/json.hpp>` when needed
- either add `using json = nlohmann::json;`, or replace `json` with `nlohmann::json`

For example, the CPU plugin was ported by:

1. [Deleting all common code and build artifacts](https://github.com/fredemmott/streamdeck-cpu/commit/fa8dd6f56bca64d168735d0314fc90c1fe93b4e3)
2. [Adding CMake and main.cpp](https://github.com/fredemmott/streamdeck-cpu/commit/c3ddaa0b7e53cc3ec38619ab9cc61e32e67a5512)
3. [Manually fixing some compatibility issues](https://github.com/fredemmott/streamdeck-cpu/commit/5ea8900eec8b07bd2d0428281326c66a0ca36737)

Additionally, using CMake makes it easy to automatically build on both platforms
[using GitHub actions](https://github.com/fredemmott/streamdeck-cpu/commit/8ad6e1c35868965651b583011c63b264b049f841).
