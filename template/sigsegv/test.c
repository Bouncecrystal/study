#include "common.h"
#include "sigsegv.h"

void function(char *p)
{
	*p=10;
}

void function1(char *p)
{
	p++;
	function(p);
}

int main()
{
	setup_sigsegv();
	char *s="hello";
	function1(s);
	return 0;
}
