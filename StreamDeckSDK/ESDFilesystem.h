// @copyright  (c) 2022, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

/* Use std::filesystem where available, ghc::filesystem otherwise. */

#ifdef ESD_HAS_STD_FILESYSTEM
#include <filesystem>
namespace ESD {
  namespace filesystem {
    using namespace std::filesystem;
  }
  using ifstream = std::ifstream;
  using ofstream = std::ofstream;
  using fstream = std::fstream;
}
#else
#include <ghc/fs_fwd.hpp>
namespace ESD {
  namespace filesystem {
    using namespace ghc::filesystem;
  }
  using ifstream = ghc::filesystem::ifstream;
  using ofstream = ghc::filesystem::ofstream;
  using fstream = ghc::filesystem::fstream;
}
#endif
