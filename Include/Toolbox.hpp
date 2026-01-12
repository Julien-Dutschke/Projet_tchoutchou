#pragma once
#include <string_view>
#include <concepts>
#include <vector>

namespace toolbox {
[[nodiscard]] inline std::string_view _default_split_caller(std::string_view s) { return s; }

template<std::invocable<std::string_view> F = decltype(_default_split_caller)>
[[nodiscard]] constexpr std::vector<decltype(std::declval<F>()(std::string_view{""}))> split(std::string_view str, std::string_view delim = " ", F call = [](auto s) { return s; })
{
   std::vector<decltype(call(str))> ret;
   size_t start = 0, end = str.find(delim, start);
   for (; start < str.size(); start = end + delim.size(), end = str.find(delim, start)) {
       if (start == end) continue;
       if (end == str.npos) end = str.size();
       ret.emplace_back(call(str.substr(start, end - start)));
   }
   return ret;
}
}
