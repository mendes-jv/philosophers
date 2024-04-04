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
static bool	set_forks(t_mutex *forks, ssize_t philo_count);
static void	set_philos(t_philo *philos, ssize_t philo_count, t_mutex *forks);

void	set_table(t_info *table, char **args)
{
	*table = (t_info){atod(args[0]), atod(args[1]) * 1000,
		atod(args[2]) * 1000, atod(args[3]) * 1000, atod(args[4]),
		get_time(), NULL, NULL};
	check_values(*table);
	table->philosophers = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philosophers)
		error(MALLOC_ERROR);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
	{
		free(table->philosophers)
		error(MALLOC_ERROR);
	}
	if (!set_forks(table->forks, table->philo_count))
	{
		free(table->forks)
		free(table->philosophers)
		error(MUTEX_ERROR);
	}
	set_philos(table->philosophers, table->philo_count, table->forks);
}

static void	check_values(t_info info)
{
	char	*message;

	message = NULL;
	if (info.philo_count < 1 || info.philo_count > 200)
		message = WRONG_PHILO_COUNT;
	if (info.time_to_die < 60)
		message = WRONG_TIME_TO_DIE;
	if (info.time_to_eat < 60)
		message = WRONG_TIME_TO_EAT;
	if (info.time_to_sleep < 60)
		message = WRONG_TIME_TO_SLEEP;
	if (info.meal_count < 0)
		message = WRONG_MEAL_COUNT;
	if (message)
		error(message);
}

static bool	set_forks(t_mutex *forks, ssize_t philo_count)
{
	int	index;

	index = 0;
	while (index < philo_count)
	{
		if (pthread_mutex_init(forks + index++, NULL))
		{
			while (index)
				pthread_mutex_destroy(forks + index--);
			return (false);
		}
	}
	return (true);
}

static void	set_philos(t_philo *philos, ssize_t philo_count, t_mutex *forks)
{
	int	index;

	index = 0;
	while (index < philo_count)
	{
		philos[index] = (t_philo){
			.meals = 0,
			.meal_time = get_time(),
			.left_fork = forks + index,
			.right_fork = forks + ((index + 1) % philo_count),
			.is_alive = true
		};
		index++;
	}
}
