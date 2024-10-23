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
#include <math.h>

void printPowerset(int *set, int set_size) {
    unsigned int powerset_size = pow(2, set_size);
    int counter, j;

    // Run from 0 to 2^set_size - 1
    for (counter = 0; counter < powerset_size; counter++) {
        printf("{ ");
        // Check each element in the set
        for (j = 0; j < set_size; j++) {
            // Check if jth bit in the counter is set
            if (counter & (1 << j)) {
                printf("%d ", set[j]);
            }
        }
        printf("}\n");
    }
}

int main() {
    int set[] = {1, 2, 3, 4};
    int set_size = sizeof(set) / sizeof(set[0]);

    printPowerset(set, set_size);

    return 0;
}
