#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>

int main()
{
	// Get the PID of the current process
	pid_t current_pid = getpid();

	// Calculate the maximum PID based on the number of bits in a PID
	unsigned long max_pid = 1UL << (sizeof(pid_t) * CHAR_BIT);

	printf("Current PID: %d\n", current_pid);
	printf("Maximum PID: %lu\n", max_pid);

	return 0;
}
