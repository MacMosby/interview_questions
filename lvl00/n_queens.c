/* TASK:
Given a number n, you have to place n queens on a chess board with the size n*n
while the queens cannot attack each other.

You have to print all the different solutions in the following format:
1 3 0 2
2 0 3 1
*/

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
	if (argc != 2)
		return (0);
	else
	{
		int n = atoi(argv[1]);
		if (n < 1)
			return (0);
		int arr[n];
		solveNQ(arr, n, 0);
	}
	return (0);
}
