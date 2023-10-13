#include"dtl.h"

int main()
{
	DTL_LOG.settings(DTL_WHITE, DTL_PURPLE, DTL_DEFAULT, DTL_RED, DTL_PROGRAM_TIME, 1);
	
	int a = 3, b = 7;
	dtl::swap(a, b);
	DTL_LOG.entry("[0], [0]", a, b);
	DTL_LOG.entry("[2]", 12);
	DTL_LOG.error("haha [x]", 6545145);
	
	system("PAUSE");
	return 0;
}
