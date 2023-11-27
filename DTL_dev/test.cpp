#include"dtl.h"
#include<Windows.h>

#define DTL_LOG_ENT

void func(std::array<int, 3> arr)
{

}

int main()
{
	dtl::Log.settings(DTL_WHITE, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_PROGRAM_TIME, DTL_CONSOLE);
	dtl::Log.setFile("errorLog.txt");
	int a = 19, b = 18;
	std::swap(a, b);
	dtl::Log.warning("{}, {0}", 7, 8, 9);
	dtl::Log.warning("{0}, {0}", a, b);
	dtl::Log.entry("{b}, {0}", 12.256f, 'c');
	dtl::Log.error("haha [x]", 6545145);
	DTL_LOG_ENT("macro test {0}, {i}", 7, 15.5f);

	std::array<int, 3> vec = { 1, 2, 3 };
	
	dtl::Log.entry("{0}", vec);
	dtl::Log.entry("haha", vec, 12);
	
	

	system("PAUSE");
	return 0;
}