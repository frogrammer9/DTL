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

//Logger defines
#define DTL_LOG dtl::Logger::GetInstance()
#define DTL_BLACK			"\033[0;30m"
#define DTL_DARK_GRAY		"\033[1;30m"
#define DTL_BLUE			"\033[0;34m"
#define DTL_LIGHT_BLUE		"\033[1;34m"
#define DTL_GREEN			"\033[0;32m"
#define DTL_LIGHT_GREEN		"\033[1;32m"
#define DTL_CYAN			"\033[0;36m"
#define DTL_LIGHT_CYAN		"\033[1;36m"
#define DTL_RED				"\033[0;31m"
#define DTL_LIGHT_RED		"\033[1;31m"
#define DTL_PURPLE			"\033[0;35m"
#define DTL_LIGHT_PURPLE	"\033[1;35m"
#define DTL_BROWN			"\033[0;33m"
#define DTL_YELLOW			"\033[1;33m"
#define DTL_LIGHT_GRAY		"\033[0;37m"
#define DTL_WHITE			"\033[1;37m"
#define DTL_DEFAULT			"\0"
#define DTL_PROGRAM_TIME	0
#define DTL_SYSTEM_TIME		1
#define DTL_DONT_SHOW		2

namespace dtl
{
	class Logger
	{
		static Logger s_Log;
		bool m_shouldstayopen;
		int m_time_start;
		std::string::size_type findToken(const std::string& s) const;
		std::string m_colEntry;
		std::string m_colInfo;
		std::string m_colWarning;
		std::string m_colError;
		int m_timeFormat;
		template<typename T>
		void processToken(char c, const T& arg, bool isError) const
		{
			if (!isError)
			{
				if (c == '0') std::cout << arg;
				else if (c == 'x') std::cout << std::uppercase << std::hex << arg;
				else if (c == '8') std::cout << std::oct << arg;
				else if (c == 'i') std::cout << (int)arg;
				else if (c == 'f') std::cout << std::showpoint << (double)arg;
				else if (c == 's') std::cout << std::scientific << arg;
				else if (c == '2') std::cout << std::bitset<sizeof(arg) * 8>(arg);
				else std::cout << ":Unknown format specifier:";
			}
			else
			{
				if (c == '0') std::cerr << arg;
				else if (c == 'x') std::cerr << std::uppercase << std::hex << arg;
				else if (c == '8') std::cerr << std::oct << arg;
				else if (c == 'i') std::cerr << (int)arg;
				else if (c == 'f') std::cerr << std::showpoint << (double)arg;
				else if (c == 's') std::cerr << std::scientific << arg;
				else if (c == '2') std::cerr << std::bitset<sizeof(arg) * 8>(arg);
				else std::cerr << ":Unknown format specifier:";
			}
		}
		void passToken(char c, const char& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const unsigned char& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const short& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const ushort& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const int& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const uint& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const float& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const double& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const long& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const unsigned long& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const long long& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const unsigned long long& a, bool isError) { processToken(c, a, isError); }
		void passToken(char c, const std::string& a, bool isError)
		{
			if (!isError)
			{ if (c == '0') std::cout << a; else std::cout << ":Unknown format specifier:"; }
			else { if (c == '0') std::cerr << a; else std::cerr << ":Unknown format specifier:"; }
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
				passToken(text[a + 1], arg, false);
				std::cout << text.substr(a + 3) << '\n';
			}
		}
		template<typename T, typename ...Types>
		void output(const std::string& text, T&& arg, Types&& ...args)
		{
			auto a = findToken(text);
			std::cout << text.substr(0, a);
			passToken(text[a + 1], arg, false);
			output(text.substr(a + 3), std::forward<Types>(args)...);
		}
		void erroutput(const std::string& text);
		template<typename T>
		void erroutput(const std::string& text, T&& arg)
		{
			auto a = findToken(text);
			if (a == std::string::npos) { std::cerr << text << "\n"; }
			else
			{
				std::cerr << text.substr(0, a);
				passToken(text[a + 1], arg, true);
				std::cerr << text.substr(a + 3) << '\n';
			}
		}
		template<typename T, typename ...Types>
		void erroutput(const std::string& text, T&& arg, Types&& ...args)
		{
			auto a = findToken(text);
			std::cerr << text.substr(0, a);
			passToken(text[a + 1], arg, true);
			output(text.substr(a + 3), std::forward<Types>(args)...);
		}
		void showtime();
		Logger();
	public:
		Logger(const Logger&) = delete;
		~Logger();
		void settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, int consoleBehaviour);
		static Logger& GetInstance();
		template<typename ...Types>
		void entry(std::string message, Types&& ... args)
		{
			std::cout << m_colEntry;
			showtime();
			std::cout << "[ENT] ";
			output(message, std::forward<Types>(args)...);
			std::cout << "\033[0m";
		}
		template<typename ...Types>
		void error(std::string message, Types&& ... args)
		{
			std::cerr << m_colError;
			showtime();
			std::cerr << "[ERR] ";
			erroutput(message, std::forward<Types>(args)...);
			std::cerr << "\033[0m";
		}
		template<typename ...Types>
		void info(std::string message, Types&& ... args)
		{
			std::cout << m_colInfo;
			showtime();
			std::cout << "[INF] ";
			output(message, std::forward<Types>(args)...);
			std::cout << "\033[0m";
		}
		template<typename ...Types>
		void warning(std::string message, Types&& ... args)
		{
			std::cout << m_colWarning;
			showtime();
			std::cout << "[WAR] ";
			output(message, std::forward<Types>(args)...);
			std::cout << "\033[0m";
		}
	};



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

	void swap(short& a, short& b);
	void swap(ushort& a, ushort& b);
	void swap(int& a, int& b);
	void swap(uint& a, uint& b);
	void swap(float& a, float& b);
	void swap(double& a, double& b);
	void swap(long& a, long& b);
	void swap(unsigned long& a, unsigned long& b);
	void swap(long long& a, long long& b);
	void swap(unsigned long long& a, unsigned long long& b);
}
