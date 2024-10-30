/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcrodenbusch <marcrodenbusch@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:50:35 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/30 14:59:01 by marcrodenbu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name: rip
Expected files: *.c *.h
Allowed functions: puts, write
Write a program that will take as argument a string containing only parenthesis.
If parenthesis are unbalanced (for example "())") your program shall remove the minimum number of parenthesis for the expression to be balanced.
By removing we mean replacing by spaces.
You will print all the solutions (can be more than one).
The order of the solutions is not important.
For example this should work:
(For readability reasons the '_' means space and the spaces are for readability only.)
$> ./rip '( ( )' | cat -e
_ ( ) $
( _ ) $
$> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
( ( ( ) ( ) ( ) ) ( ) ) $
$> ./rip '( ) ( ) ) ( )' | cat -e
( ) ( ) _ ( ) $
( ) ( _ ) ( ) $
( _ ( ) ) ( ) $
$> ./rip '( ( ) ( ( ) (' | cat -e
( ( ) _ _ ) _ $
( _ ) ( _ ) _ $
( _ ) _ ( ) _ $
_ ( ) ( _ ) _ $
_ ( ) _ ( ) _ $
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_balanced(char *str, int index, int left_rem, int right_rem, int pair, char *buffer, int buffer_index) {
    int len = strlen(str);
	if (index == len) {
        if (left_rem == 0 && right_rem == 0 && pair == 0) {
            buffer[buffer_index] = '\0';
            printf("%s\n", buffer);
        }
        return;
    }

    if (str[index] == '(') {
        if (left_rem > 0) {
            generate_balanced(str, index + 1, left_rem - 1, right_rem, pair, buffer, buffer_index);
        }
        buffer[buffer_index] = '(';
        generate_balanced(str, index + 1, left_rem, right_rem, pair + 1, buffer, buffer_index + 1);
    } else if (str[index] == ')') {
        if (right_rem > 0) {
            generate_balanced(str, index + 1, left_rem, right_rem - 1, pair, buffer, buffer_index);
        }
        if (pair > 0) {
            buffer[buffer_index] = ')';
            generate_balanced(str, index + 1, left_rem, right_rem, pair - 1, buffer, buffer_index + 1);
        }
    } else {
        buffer[buffer_index] = str[index];
        generate_balanced(str, index + 1, left_rem, right_rem, pair, buffer, buffer_index + 1);
    }
}

void remove_invalid_parentheses(char *str) {
    int left_rem = 0, right_rem = 0;
	int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            left_rem++;
        } else if (str[i] == ')') {
            if (left_rem > 0) {
                left_rem--;
            } else {
                right_rem++;
            }
        }
    }

    char *buffer = (char *)malloc(strlen(str) + 1);
    generate_balanced(str, 0, left_rem, right_rem, 0, buffer, 0);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Usage: ./rip <parentheses_string>");
        return 1;
    }

    char *input = argv[1];
    remove_invalid_parentheses(input);
    return 0;
}