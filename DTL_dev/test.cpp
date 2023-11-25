#include"dtl.h"
#include<Windows.h>

#define DTL_LOG_ENT

int main()
{
	dtl::Log.settings(DTL_WHITE, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_PROGRAM_TIME, DTL_CONSOLE);
	dtl::Log.setFile("errorLog.txt");
	int a = 19, b = 18;
	dtl::swap(a, b);
	dtl::Log.warning("{}, {0}", 7, 8, 9);
	dtl::Log.entry("{b}, {0}", 12.256f, 'c');
	dtl::Log.error("haha [x]", 6545145);
	DTL_LOG_ENT("macro test {0}, {i}", 7, 15.5f);





	system("PAUSE");
	return 0;
}
