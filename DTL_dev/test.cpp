#include"dtl.h"

int main()
{
	Log.settings(DTL_DARK_GRAY, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_SYSTEM_TIME, 1);
	
	Log.entry("test1");
	Log.info("test2");
	Log.warning("test3");
	Log.error("test4");


	//	Log.entry("");


	system("PAUSE");
	return 0;
}
