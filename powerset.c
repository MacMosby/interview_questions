/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:25 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/23 13:14:26 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int sum_check(int x, int *subset, int len)
{
  int sum = 0;
  int i = 0;

  while (i < len)
  {
    sum += subset[i];
    i++;
  }
  if (x == sum)
    return (1);
  return (0);
}

void  print_sol(int *subset, int len)
{
  int i = 0;

  if (len == 0)
    return ;
  printf("Length: %d\n", len);
  printf("Result:");
  while (i < len)
  {
    printf(" %d", subset[i]);
    i++;
  }
  printf("\n");
}

void  gen_powerset(int x, int *set, int set_size)
{
    int counter = 0;
    int i = 0;
    int j = 0;
    int *subset = malloc(set_size * sizeof(int));
    unsigned int powerset_size = 1;

    while (i < set_size)
    {
      powerset_size *= 2;
      i++;
    }
    printf("size of powerset: %d\n", powerset_size);
    // Run from 0 to 2^set_size - 1
    while (counter < powerset_size)
    {
        // Check each element in the set
        i = 0;
        j = 0;
        while (j < set_size)
        {
            // Check if jth bit in the counter is set
            if (counter & (1 << j))
            {
                subset[i] = set[j];
                i++;
            }
            j++;
        }
        if (sum_check(x, subset, i))
          print_sol(subset, i);
        counter++;
    }
    free(subset);
}

int main() {
    int x = 0;
    int set[] = {1, 2, 3, 4};
    int set_size = sizeof(set) / sizeof(set[0]);

    gen_powerset(x, set, set_size);
    return 0;
}
