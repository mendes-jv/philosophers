/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/31 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static ssize_t atod(char *arg);
static void check_values(t_table table);

void set_table(t_table *table, char **args)
{
	size_t mutex_count;

	mutex_count = 10;
	*table = (t_table) {atod(args[0]), atod(args[1]) * 1000,
		atod(args[2]) * 1000, atod(args[3]) * 1000, atod(args[4]),
						get_time(), NULL, PTHREAD_MUTEX_INITIALIZER,
						{PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
						 PTHREAD_MUTEX_INITIALIZER,
						 PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
						 PTHREAD_MUTEX_INITIALIZER,
						 PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER}};
	check_values(*table);
	table->philosophers = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philosophers)
		error(MALLOC_ERROR);
	pthread_mutex_init(&table->print, NULL);
	while (mutex_count--)
		pthread_mutex_init(table->infos + mutex_count, NULL);
}

static ssize_t atod(char *arg)
{
	ssize_t number;

	if (!arg)
		return (0);
	number = 0;
	while (*arg)
	{
		if (*arg < '0' || *arg > '9'
			|| (number * 10) > (ssize_t) (ULONG_MAX / 1000))
			return (-1);
		number = (number * 10) + (*arg++ - '0');
	}
	return (number);
}

static void check_values(t_table table)
{
	char	*message;

	message = NULL;
	if (table.philo_count < 1 || table.philo_count > 200)
		message = WRONG_PHILO_COUNT;
	if (table.time_to_die < 60)
		message = WRONG_TIME_TO_DIE;
	if (table.time_to_eat < 60)
		message = WRONG_TIME_TO_EAT;
	if (table.time_to_sleep < 60)
		message = WRONG_TIME_TO_SLEEP;
	if (table.meal_count < 0)
		message = WRONG_MEAL_COUNT;
	if (message)
		error(message);
}
