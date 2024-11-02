#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct
{
	float	x;
	float	y;
}	City;

float distance(float x0, float y0, float x1, float y1)
{
	float diff[2] = {
	x1 - x0,
	y1 - y0
	};
	return sqrtf(diff[0] * diff[0] + diff[1] * diff[1]);
}

void  swap(City *a, City *b)
{
  City tmp = *a;
  *a = *b;
	*b = tmp;
}

float	calculate_path_len(City *cities, int n)
{
	float totalDist = 0;
	int i = 0;

	while (i < n - 1)
	{
		totalDist += distance(cities[i].x, cities[i].y, cities[i + 1].x, cities[i + 1].y);
		i++;
	}
	totalDist += distance(cities[n - 1].x, cities[n - 1].y, cities[0].x, cities[0].y);
	return (totalDist);
}

void	permute(City *cities, int start, int end, float *minDist)
{
	float	currDist;
	int		i = start;

	if (start == end)
	{
		currDist = calculate_path_len(cities, end + 1);
		if (currDist < *minDist)
			*minDist = currDist;
	}
	else
	{
		while (i <= end)
		{
			swap(&cities[start], &cities[i]);
			permute(cities, start + 1, end, minDist);
			swap(&cities[start], &cities[i]);
			i++;
		}
	}
}

int main()
{
	City	cities[11];
	int		n = 0;
	float	minDist = FLT_MAX;

	while(fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y) == 2)
		n++;
	permute(cities, 0, n - 1, &minDist);
	fprintf(stdout, "%.2f\n", minDist);
	return (0);
}
