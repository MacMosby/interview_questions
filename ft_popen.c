/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcrodenbusch <marcrodenbusch@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:56:18 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/26 23:06:52 by marcrodenbu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
