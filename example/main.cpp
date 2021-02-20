#include "MyPlugin.h"

#include <StreamDeckSDK/ESDMain.h>

int main(int argc, const char** argv) {
  auto plugin = std::make_unique<MyPlugin>();
  return esd_main(argc, argv, plugin.get());
}
