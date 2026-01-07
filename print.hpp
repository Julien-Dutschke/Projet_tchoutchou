#pragma once
// sadly, this pollutes every single file we include this in.
#include <iostream>
#include <sstream>

// unix only. used for colour.
// could be replaced by a noop if not on a unix system
#include <unistd.h>

namespace print
{

	namespace raw
	{
		template <typename... Args>
		void print(std::ostream& out, Args&&... args)
		{
			(out << ... << std::forward<Args>(args));
		}

		template<typename... Args>
		void println(std::ostream& out, Args&&... args)
		{
			print(out, std::forward<Args>(args)..., '\n');
		}
	}

	template <typename... Args>
	void print(Args&&... args)
	{
		raw::print(std::cout, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void println(Args&&... args)
	{
		raw::println(std::cout, std::forward<Args>(args)...);
	}

	using AnsiColour = std::string_view;

	static constexpr AnsiColour reset   { "\033[0m" };
	static constexpr AnsiColour red     { "\033[0;31m" };
	static constexpr AnsiColour green   { "\033[0;32m" };
	static constexpr AnsiColour yellow  { "\033[0;33m" };
	static constexpr AnsiColour blue    { "\033[0;34m" };
	static constexpr AnsiColour purple  { "\033[0;35m" };
	static constexpr AnsiColour white   { "\033[0;36m" };

	struct Colour {
		std::string_view start;
		std::stringstream stream;

		template<typename... Args>
		Colour(AnsiColour colour, Args&&... args) : start(colour)
		{
			raw::print(stream, std::forward<Args>(args)...);
		}

		std::string compute() const
		{
			if (isatty(1) && isatty(2))
				return std::string(start) + stream.str() + std::string(reset);
			return stream.str();
		}
	};

	inline std::ostream& operator<<(std::ostream& o, const Colour& colour)
	{
		return o << colour.compute();
	}

	// TODO: allow color on logs (green -> info, yellow -> warning, red -> errors)
	// using ANSI codes. do NOT allow them when stdout / stderr is in tty
	template<typename... Args>
	void info(Args&&... args)
	{
		println(Colour(green, " *  "), std::forward<Args>(args)...);
	}

	template<typename... Args>
	void warn(Args&&... args)
	{
		raw::println(std::cerr, Colour(yellow, "?? "), std::forward<Args>(args)...);
	}

	template<typename... Args>
	void err(Args&&... args)
	{
		raw::println(std::cerr, Colour(red, "?! "), std::forward<Args>(args)...);
	}
}
