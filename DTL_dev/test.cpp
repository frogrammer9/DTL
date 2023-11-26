#include"dtl.h"

int main()
{
	dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_CONSOLE);
	dtl::Log.setFile("errorLog.txt");
	dtl::Log.warning("{}, {0}, {00}", 7, 8, 9);
	dtl::Log.entry("{b}, {0}", 12.256f, 'c');
	dtl::Log.info("{b}, {0}");
	dtl::Log.error("test {0}", 6545145);
	DTL_ENT("macro test {0}, {i}", 7, 15.5f);

	return 0;
}
