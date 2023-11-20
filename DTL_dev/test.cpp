#include"dtl.h"
#include<Windows.h>

int main()
{
	dtl::Log.settings(DTL_WHITE, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_PROGRAM_TIME, DTL_CONSOLE);
	dtl::Log.setFile("errorLog.txt");
	int a = 19, b = 18;
	dtl::swap(a, b);
	dtl::Log.warning("{}, {0}", 7);
	dtl::Log.entry("{b}, {0}", 12.256f, 'c');
	dtl::Log.error("haha [x]", 6545145);
	
	dtl::Timer time;
	time.Start();
	for (int i = 0; i < 2000; i++)
	{
		dtl::Log.warning("{}, {b}, {aa}, {b}", i, 7, 258);
	}
	dtl::Timer time3;
	time3.Start();
	for (int i = 0; i < 2000; i++)
	{
		std::cout << i;
	}
	dtl::Log.entry("Log time was {0}", time.Get() - time3.Get());
	dtl::Log.entry("cout time was {0}", time3.Get());

	system("PAUSE");
	return 0;
}
