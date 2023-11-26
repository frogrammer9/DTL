#include"dtl.h"
#include<time.h>

dtl::Logger dtl::Logger::s_Log;
namespace dtl
{
	dtl::Logger& Log = dtl::Logger::GetInstance();
}

bool dtl::Logger::findToken(const std::string& s, size_t* t1, size_t* t2)
{
	*t1 = s.find('{');
	*t2 = s.find('}');
	return (*t2 - *t1 == 2);
}

void dtl::Logger::output(const std::string& text) { m_msg << text << '\n'; }

//todo Implement time zones
void dtl::Logger::showtime()
{
	if (m_timeFormat == DTL_PROGRAM_TIME)
	{
		int ctime = (clock() - m_time_start) / 1000;
		m_msg
			<< "[" << std::setfill('0') << std::setw(2) << (ctime / 3600) << ":"
			<< std::setw(2) << ctime % 3600 / 60 << ":" << std::setw(2) << ctime % 60 << "]";
	}
	else if (m_timeFormat == DTL_SYSTEM_TIME)
	{
		auto t = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		m_msg << "[" << std::setfill('0') <<
			std::setw(2) << (t / 60 / 60) % 24 << ":" <<
			std::setw(2) << (t / 60) % 60 << ":" <<
			std::setw(2) << t % 60 << "]";
	}
	else if (m_timeFormat == DTL_DONT_SHOW) { return; }
	else m_msg << "[ERROR]";
}

dtl::Logger::Logger()
	:m_shouldstayopen(false), m_time_start(std::clock()), m_mode(0), m_colEntry(DTL_WHITE),
	m_colInfo(DTL_GREEN), m_colWarning(DTL_YELLOW), m_colError(DTL_RED), m_timeFormat(0)
{}

dtl::Logger::~Logger()
{
	if (m_shouldstayopen) system("PAUSE");
	if (!m_msg.str().empty() && m_mode == DTL_FILE)
	{
		m_outf.open(m_filepath, std::ofstream::out);
		if (m_outf.is_open())
		{
			m_outf << m_msg.str();
			m_outf.close();
		}
	}
}

dtl::Logger& dtl::Logger::GetInstance() { return s_Log; }

void dtl::Logger::settings(std::string entryCol, std::string infoCol, std::string warningCol, std::string errorCol, int timeFormat, int logLocation)
{
	if (entryCol != "\0") m_colEntry = entryCol;
	if (infoCol != "\0") m_colInfo = infoCol;
	if (warningCol != "\0") m_colWarning = warningCol;
	if (errorCol != "\0") m_colError = errorCol;
	m_timeFormat = timeFormat;
	m_mode = logLocation;
}

void dtl::Logger::setFile(const std::string& filePath) { m_filepath = filePath; }

dtl::Timer::Timer() {}
dtl::Timer::~Timer() {}

void dtl::Timer::Start() { m_begin = std::chrono::high_resolution_clock::now(); }
double dtl::Timer::Get() { return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_begin).count(); }
float dtl::round(float number) { return (float)((int)(number + 0.5)); }
double dtl::round(double number) { return (double)((int)(number + 0.5)); }
long double dtl::round(long double number) { return (long double)((int)(number + 0.5)); }

void dtl::swap(short& a, short& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(ushort& a, ushort& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(uint& a, uint& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(int& a, int& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(float& a, float& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(double& a, double& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(long& a, long& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(unsigned long& a, unsigned long& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(long long& a, long long& b) { a = a + b; b = a - b; a = a - b; }
void dtl::swap(unsigned long long& a, unsigned long long& b) { a = a + b; b = a - b; a = a - b; }