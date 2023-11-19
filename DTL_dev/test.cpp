#include"dtl.h"

int main()
{
	dtl::Log.settings(DTL_WHITE, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_SYSTEM_TIME, DTL_CONSOLE);
	dtl::Log.setFile("errorLog.txt");
	int a = 19, b = 18;
	dtl::swap(a, b);
	dtl::Log.warning("{tzw}, {0}", 7, 7, 7); //this is a bug to fix. {--1--} <-look for this in dtl.h
	dtl::Log.entry("[0]", "uwuowo");
	dtl::Log.error("haha [x]", 6545145);
	
	system("PAUSE");
	return 0;
}
