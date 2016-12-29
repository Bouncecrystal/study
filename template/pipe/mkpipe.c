#include "common.h"

int main()
{
	if(access("myfifo", F_OK) == 0)
	{
		DEBUG("myfifo already exist");
	}
	else
		mkfifo("myfifo", 0666);
	return 0;
}
