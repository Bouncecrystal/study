#include "common.h"
#include <unistd.h>

int main()
{
	pid_t pid, ppid, pgid;

	pid = getpid();
	ppid = getppid();
	pgid = getpgid(pid);

	printf("pid=%d\nppid=%d\npgid=%d\n", pid, ppid, pgid);

	return 0;
}
