#include "common.h"

int main()
{
	execlp("expr", "expr","4", "+", "5", (char*)0);
	return 0;
}
