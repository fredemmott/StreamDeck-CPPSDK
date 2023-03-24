// @copyright  (c) 2022, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.
#pragma once

#include <version>

/* Use std::format where available, fmt::format otherwise.
 *
 * As of July 2022, std::format is not yet available on MacOS;
 * not just using fmt everywhere as std::format:
 * - is standard
 * - has full wchar_t support in MSVC 2022, including compile-time checking
 */

#ifdef __cpp_lib_format
#include <format>
namespace ESD {
using std::format;
#if __cpp_lib_format >= 202207L
// C++20 DR https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2508r1.html
// MSVC 2020 v17.5 and above
using std::basic_format_string;
#else
// MSVC 2020 v17.4 and below
template <class... Args>
using basic_format_string = std::_Basic_format_string<Args...>;
#endif
}// namespace ESD
#else
#include <fmt/format.h>
namespace ESD {
using fmt::format;
template <class... Args>
using basic_format_string = fmt::basic_format_string<Args...>;
};// namespace ESD
#endif

namespace ESD {
template <class... Args>
using format_string = basic_format_string<char, std::type_identity_t<Args>...>;

#ifdef _MSC_VER
template <class... Args>
using format_wstring = basic_format_string<wchar_t, std::type_identity_t<Args>...>;
#endif

}// namespace ESD
