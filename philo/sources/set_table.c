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

static void	check_values(t_info info);

void	set_table(t_info *table, char **args)
{
	*table = (t_info){
			atod(args[0]),
			atod(args[1]),
			atod(args[2]),
			atod(args[3]),
			atod(args[4]),
			NULL,
			NULL
	};
	check_values(*table);
	table->philosophers = malloc(sizeof(pthread_t) * table->philo_count);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->philosophers || !table->forks)
		error(MALLOC_ERROR);
}

static void	check_values(t_info info)
{
	char	*message;

	message = NULL;
	if (info.philo_count < 1 || info.philo_count > 200)
		message = WRONG_PHILO_COUNT;
	if (info.time_to_die < 60 || info.time_to_die > 1000000)
		message = WRONG_TIME_TO_DIE;
	if (info.time_to_eat < 60 || info.time_to_eat > 1000000)
		message = WRONG_TIME_TO_EAT;
	if (info.time_to_sleep < 60 || info.time_to_sleep > 1000000)
		message = WRONG_TIME_TO_SLEEP;
	if (info.meal_count < 0 || info.meal_count > 200)
		message = WRONG_MEAL_COUNT;
	if (message)
		error(message);
}
