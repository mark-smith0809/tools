#pragma once
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef FOREGROUND_RED
#define FOREGROUND_RED 0x0004
#endif

#ifndef FOREGROUND_BLUE
#define FOREGROUND_BLUE 0x0001
#endif

#ifndef FOREGROUND_GREEN
#define FOREGROUND_GREEN 0x0002
#endif

#ifndef FOREGROUND_INTENSITY
#define FOREGROUND_INTENSITY 0x0080
#endif

namespace Color {
	struct ColorUnit {
		int value_window{ 0 };
		std::string value_linux{ "\033[0m" };
		explicit ColorUnit(int i, std::string str):value_window(i), value_linux(str) {};
	};

	class ColorControl {
	public:
		ColorControl(ColorUnit u) :colorUnit(u) {};
		friend std::ostream& operator<<(std::ostream& os, ColorControl color) {
#ifdef _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color.colorUnit.value_window);
#else
			os << color.colorUnit.value_linux;
#endif // _WIN32
			return os;
		}
	private:
		ColorUnit colorUnit;
	};
	const ColorControl Normal(ColorUnit(0x07, std::string("\033[0m"))); // normal
	const ColorControl HighLight(ColorUnit(FOREGROUND_INTENSITY, std::string("\033[0m"))); //highlight

	const ColorControl Red(ColorUnit(FOREGROUND_RED, std::string("\033[31m"))); // red
	const ColorControl Green(ColorUnit(FOREGROUND_GREEN, std::string("\033[32m"))); // green
	const ColorControl Yellow(ColorUnit(FOREGROUND_RED | FOREGROUND_GREEN, std::string("\033[33m"))); // yellow
	const ColorControl Blue(ColorUnit(FOREGROUND_BLUE, std::string("\033[34m"))); // blue
	const ColorControl Magenta(ColorUnit(FOREGROUND_RED | FOREGROUND_BLUE, std::string("\033[35m"))); // magenta
	const ColorControl White(ColorUnit(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN, std::string("\033[37m"))); // white // 
}

void TestColor_window();