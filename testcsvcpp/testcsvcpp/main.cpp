#include "uniqsconfig.h"

extern void main2();
extern void main3();

int main()
{
	UniqsLoadAllConfigDatas("./");

	main2();
	main3();

	return 0;
}
