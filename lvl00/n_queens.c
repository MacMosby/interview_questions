/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcrodenbusch <marcrodenbusch@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:33:34 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/22 20:53:08 by marcrodenbu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	safeQ(int *arr, int col, int row)
{
	int i = 0;

	while (i < col)
	{
		if (arr[i] == row)
			return (0);
		if (arr[i] - i == row - col)
			return (0);
		if (arr[i] + i == row + col)
			return (0);
		i++;
	}
	return (1);
}

void	print_sol(int *arr, int n)
{
	int i = 0;

	while (i < n)
	{
		if (i == 0)
			printf("%d", arr[i]);
		else
			printf(" %d", arr[i]);
		i++;
	}
	printf("\n");
}

void	solveNQ(int *arr, int n, int col)
{
	int i = 0;

	if (col == n)
	{
		print_sol(arr, n);
		return ;
	}
	while (i < n)
	{
		if (safeQ(arr, col, i))
		{
			arr[col] = i;
			solveNQ(arr, n, col + 1);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	int *arr;

	if (argc != 2)
		return (0);
	else
	{
		int n = atoi(argv[1]);
		if (n < 1)
			return (0);
		arr = malloc(n * sizeof(int));
		solveNQ(arr, n, 0);
	}
	free(arr);
	return (0);
}
