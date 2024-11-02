/* TASK:
Assignment name:    sandbox
Expected files:     sandbox.c
Allowed functions:  fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal, errno
--------------------------------------------------------------------------------
Write the following function:

#include <stdbool.h>
int sandbox(void(*f)(void), unsigned int timeout, bool verbose);

This function must test if the function f is a nice function or a bad function,
you will return 1 if it is nice, 0 if f is bad or -1 in case of an error in your
function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exits with any other exit code than 0 or if it times
out.

If verbose is true, you must write the appropriate message among the following:
"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal_description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

int	g_to;

void	handle_timeout(int sig)
{
	if (sig == SIGALRM)
		g_to = 1;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int pid;
	int status;
	struct sigaction sa_to;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		f();
		exit(0);
	}
	sa_to.sa_handler = handle_timeout;
	sigaction(SIGALRM, &sa_to, NULL);
	alarm(timeout);
	if (waitpid(pid, &status, 0) == -1)
	{
		while (1)
		{
			if (errno == EINTR)
			{
				if (g_to)
				{
					if (verbose)
						printf("Bad function: timed out after %u seconds\n", timeout);
					kill(pid, SIGKILL);
					if (waitpid(pid, &status, 0) == -1)
						return (-1);
					return (0);
				}
				continue;
			}
			else
				return (-1);
			break;
		}
	}
	if (WIFSIGNALED(status))
	{
		int signum = WTERMSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(signum));
		return (0);
	}
	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);
		if (exit_code)
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			return (0);
		}
		else
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
	}
	return (-1);
}
