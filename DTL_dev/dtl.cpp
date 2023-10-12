#include"dtl.h"


Logger Logger::s_Log;



std::string::size_type Logger::findToken(const std::string& s) const
{
	auto t1 = s.find("[");
	auto t2 = s.find(']');
	if (t2 - t1 == 2) return t1;
	return std::string::npos;
}

void Logger::output(const std::string& text) { std::cout << text << '\n'; }
void Logger::erroutput(const std::string& text) { std::cerr << text << '\n'; }

//todo Implement time zones
void Logger::showtime()
{
	if (m_timeFormat == DTL_PROGRAM_TIME) 
	{
		int ctime = (clock() - m_time_start) / 1000;
		std::cout
			<< "[" << std::setfill('0') << std::setw(2) << (ctime / 3600) << ":"
			<< std::setw(2) << ctime % 3600 / 60 << ":" << std::setw(2) << ctime % 60 << "]"; 
		return; 
	}
	else if (m_timeFormat == DTL_SYSTEM_TIME)
	{ std::cout << "[" << std::setfill('0')<<
		std::setw(2) << (time(0) / 60 / 60) % 24 + /*get rid of this 2 (time zone offset)*/2 << ":" << 
		std::setw(2) << (time(0) / 60) % 60 << ":" << 
		std::setw(2) << time(0) % 60 << "]";
		return;
	}
	else if (m_timeFormat == DTL_DONT_SHOW) { return; }
	else std::cout << "[ERROR]";
}

Logger::Logger()
	:m_shouldstayopen(false), m_time_start(std::clock()), m_colEntry(DTL_WHITE), 
	m_colInfo(DTL_GREEN), m_colWarning(DTL_YELLOW), m_colError(DTL_RED), m_timeFormat(0) {}

Logger::~Logger() { if (m_shouldstayopen) system("PAUSE"); }

Logger& Logger::GetInstance() { return s_Log; }

Logger& Log = Logger::GetInstance();

void Logger::settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, int consoleBehaviour)
{
	if (entryCol != "\0") m_colEntry = entryCol;
	if (infoCol != "\0") m_colInfo = infoCol;
	if (warningCol != "\0") m_colWarning = warningCol;
	if (errorCol != "\0") m_colError = errorCol;
	m_timeFormat = timeFormat;
}

dtl::Timer::Timer() {}
dtl::Timer::~Timer() {}

void dtl::Timer::Start() { m_begin = std::chrono::high_resolution_clock::now(); }
double dtl::Timer::Get() { return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_begin).count(); }
float dtl::round(float number) { return (float)((int)(number + 0.5)); }
double dtl::round(double number) { return (double)((int)(number + 0.5)); }
long double dtl::round(long double number) { return (long double)((int)(number + 0.5)); }


