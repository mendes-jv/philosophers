/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/28 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_error(char *message)
{
	if (write(STDERR_FILENO, message, alen(message)) == -1)
		perror("write");
	exit(EXIT_FAILURE);
}

size_t alen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	atod(char *arg)
{
	int	number;

	if (!arg)
		return (0);
	number = 0;
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (-1);
		number = (number * 10) + (*arg++ - '0');
	}
	return (number);
}
