/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcrodenbusch <marcrodenbusch@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:36:24 by marcrodenbu       #+#    #+#             */
/*   Updated: 2024/10/30 14:47:40 by marcrodenbu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name:    sandbox
Expected files:     sandbox.c
Allowed functions:  fork, waitpid, exit, alarm, sigaction, kill, printf,
                    strsignal, errno
--------------------------------------------------------------------------------
Write the following function:

#include <stdbool.h>
int sandbox(void(*f)(void), unsigned int timeout, bool verbose);

This function must test if the function f is a nice function or a bad function,
you will return 1 if it is nice, 0 if f is bad or -1 in case of an error in your
function.

A function is considered
*/
