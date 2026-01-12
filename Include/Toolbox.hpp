#pragma once
#include <string_view>
#include <concepts>
#include <vector>
#include "print.hpp"

namespace toolbox {
[[nodiscard]] inline std::string_view _default_split_caller(std::string_view s) { return s; }

inline size_t find_unquoted(std::string_view str, std::string_view delim, size_t start)
{
	size_t first = str.find(delim, start);
	size_t second = str.find("\"", start);
	// size_t third = str.find("'", start);
	if (first < second || second == str.npos)
		return first;
	return str.find('"', second + 1) + 1;
}

template<std::invocable<std::string_view> F = decltype(_default_split_caller)>
[[nodiscard]] constexpr std::vector<decltype(std::declval<F>()(std::string_view{""}))> split(std::string_view str, std::string_view delim = " ", F call = [](auto s) { return s; })
{
   std::vector<decltype(call(str))> ret;
   size_t start = 0, end = find_unquoted(str, delim, start);
   for (; start < str.size(); start = end + delim.size(), end = find_unquoted(str, delim, start)) {
       if (start == end) continue;
       if (end == str.npos) end = str.size();
       ret.emplace_back(call(str.substr(start, end - start)));
   }
   return ret;
}
}
