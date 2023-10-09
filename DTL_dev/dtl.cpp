#include"dtl.h"


Logger Logger::s_Log;

void Logger::settings()
{



}

std::string::size_type Logger::findToken(const std::string& s) const
{
	auto t1 = s.find("[");
	auto t2 = s.find(']');
	if (t2 - t1 == 2) return t1;
	return std::string::npos;
}

void Logger::output(const std::string& text) { std::cout << text << '\n'; }
void Logger::erroutput(const std::string& text) { std::cerr << text << '\n'; }

void Logger::showtime()
{
	m_shouldstayopen = true;
	int ctime = (clock() - m_time_start) / 1000;
	std::cout << "[";
	if ((ctime / 3600) < 10) std::cout << "0";
	std::cout << (ctime / 3600);
	std::cout << ":";
	if ((ctime - ((ctime / 3600) * 3600)) / 60 < 10) std::cout << "0";
	std::cout << (ctime - ((ctime / 3600) * 3600)) / 60;
	std::cout << ":";
	if (ctime - ((ctime / 3600)) * 3600 - ((ctime - ((ctime / 3600) * 3600)) / 60) * 60 < 10) std::cout << "0";
	std::cout << ctime - (ctime / 3600) * 3600 - ((ctime - (ctime / 3600) * 3600) / 60) * 60;
	std::cout << "]";
}

Logger::Logger()
	:m_time_start(std::clock()) {}

Logger::~Logger() { if (m_shouldstayopen) system("PAUSE"); }

Logger& Logger::GetInstance() { return s_Log; }

Logger& Log = Logger::GetInstance();

dtl::Timer::Timer() {}
dtl::Timer::~Timer() {}

void dtl::Timer::Start() { m_begin = std::chrono::high_resolution_clock::now(); }
double dtl::Timer::Get() { return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_begin).count(); }
float dtl::round(float number) { return (float)((int)(number + 0.5)); }
double dtl::round(double number) { return (double)((int)(number + 0.5)); }
long double dtl::round(long double number) { return (long double)((int)(number + 0.5)); }


