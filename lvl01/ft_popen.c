/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcrodenbusch <marcrodenbusch@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:56:18 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/31 13:02:14 by marcrodenbu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name: ft_popen
Allowed functions: pipe, fork, dup2, execvp, close, exit

Write the following function:

int ft_popen(const char *file, const char *argv[], char type);

The function must launch the executable file with the arguments argv (using execvp).
If type is 'r' the function must return a file descriptor connected to the output of the command.
If type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

For example the function could be used like that:

int main()
{
    int fd = ft_popen("ls", (const char *[]) {"ls", NULL}, 'r');
    char *line;
    while ((line = get_next_line(fd)))
        ft_putstr(line);
}

Hints:
Do not leak file descriptors.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_popen(char *file, char *argv[], char type)
{
	int	fd[2];
	int pid;

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit (-1);
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit (-1);
		}
		close(fd[0]);
		close(fd[1]);
		if (execvp(file, argv) == -1)
			exit (-1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}
