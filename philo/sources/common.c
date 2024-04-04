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

ssize_t	atod(char *arg)
{
	ssize_t	number;

	if (!arg)
		return (0);
	number = 0;
	while (*arg)
	{
		if (*arg < '0' || *arg > '9' || (number * 10) > (ssize_t)(ULONG_MAX / 1000))
			return (-1);
		number = (number * 10) + (*arg++ - '0');
	}
	return (number);
}

void	error(char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	note(t_info *id, int ego, char *message)
{
	printf("%zu %d %s\n", get_time() - id->start_time, ++ego, message);
}