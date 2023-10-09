#pragma once
#include<chrono>
#include<iostream>
#include <iomanip>
#include<string>
#include<bitset>

#define PI 3.14159265359f
#define uint uint32_t
#define ushort uint16_t
#define uchar uint8_t

class Logger
{
	static Logger s_Log;
	void settings();
	bool m_shouldstayopen = false;
	int m_time_start;
	std::string::size_type findToken(const std::string& s) const;
	template<typename T>
	void processTocken(char c, const T& arg) const
	{
		if (c == '0') std::cout << arg;
		else if (c == 'x') std::cout << std::uppercase << std::hex << arg;
		else if (c == '8') std::cout << std::oct << arg;
		else if (c == 'i') std::cout << (int)arg;
		else if (c == 'f') std::cout << std::showpoint << (double)arg;
		else if (c == 's') std::cout << std::scientific << arg;
		else if (c == '2') std::cout << std::bitset<sizeof(arg) * 8>(arg);
		else return;
	}
	void output(const std::string& text);
	template<typename T>
	void output(const std::string& text, T&& arg)
	{
		auto a = findToken(text);
		if (a == std::string::npos) { std::cout << text << "\n"; }
		else 
		{
			std::cout << text.substr(0, a);
			processTocken(text[a + 1], arg);
			std::cout << text.substr(a + 3) << '\n';
		}
	}
	template<typename T, typename ...Types>
	void output(const std::string& text, T&& arg, Types&& ...args)
	{
		auto a = findToken(text);
		std::cout << text.substr(0, a);
		processTocken(text[a + 1], arg);
		output(text.substr(a + 3), std::forward<Types>(args)...);
	}
	void erroutput(const std::string& text);
	template<typename T>
	void erroutput(const std::string& text, T&& arg)
	{
		auto a = findToken(text);
		if (a == std::string::npos) { std::cerr << text << "\n"; }
		else { std::cerr << text.substr(0, a) << arg << text.substr(a + 3) << '\n'; }
	}
	template<typename T, typename ...Types>
	void erroutput(const std::string& text, T&& arg, Types&& ...args)
	{
		auto a = findToken(text);
		std::cerr << text.substr(0, a) << arg;
		erroutput(text.substr(a + 3), std::forward<Types>(args)...);
	}
	void showtime();
	Logger();
public:
	Logger(const Logger&) = delete;
	~Logger();
	static Logger& GetInstance();
	template<typename ...Types>
	void entry(std::string message, Types&& ... args)
	{
		std::cout << "\033[0m";
		showtime();
		std::cout << "[ENT] ";
		output(message, std::forward<Types>(args)...);
		std::cout << "\033[0m";
	}
	template<typename ...Types>
	void error(std::string message, Types&& ... args)
	{
		std::cerr << "\033[31m";
		showtime();
		std::cerr << "[ERR] ";
		erroutput(message, std::forward<Types>(args)...);
		std::cerr << "\033[0m";
	}
	template<typename ...Types>
	void info(std::string message, Types&& ... args)
	{
		std::cout << "\033[32m";
		showtime();
		std::cout << "[INF] ";
		output(message, std::forward<Types>(args)...);
		std::cout << "\033[0m";
	}
	template<typename ...Types>
	void warning(std::string message, Types&& ... args)
	{
		std::cout << "\033[35m";
		showtime();
		std::cout << "[WAR] ";
		output(message, std::forward<Types>(args)...);
		std::cout << "\033[0m";
	}
};

extern Logger& Log;

namespace dtl
{
	class Timer
	{
		std::chrono::high_resolution_clock::time_point m_begin;
	public:
		Timer(const Timer&) = delete;
		Timer();
		~Timer();
		void Start();
		double Get();
	};

	float round(float number);
	double round(double number);
	long double round(long double number);

}
