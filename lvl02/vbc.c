/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:43:27 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/10/25 13:16:39 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int evaluate_expression(char **expr);

int parse_number(char **expr)
{
	int num = 0;
	if(**expr > 47 && **expr < 58)
	{
		num = (**expr) - 48;
		(*expr)++;
	}
	return (num);
}

int parse_factor(char **expr)
{
	int result;
	if (**expr == '(')
	{
		(*expr)++;
		result = evaluate_expression(expr);
		(*expr)++;
	}
	else
	{
		result = parse_number(expr);
	}
	return (result);
}

int parse_term(char **expr)
{
	int result = parse_factor(expr);
	while (**expr == '*')
	{
		(*expr)++;
		result *= parse_factor(expr);
	}
	return (result);
}

int evaluate_expression(char **expr)
{
	int result = parse_term(expr);
	while (**expr == '+')
	{
		(*expr)++;
		result += parse_term(expr);
	}
	return (result);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char *expr = argv[1];
	int result = evaluate_expression(&expr);

	printf("%d\n", result);
	return (0);
}
