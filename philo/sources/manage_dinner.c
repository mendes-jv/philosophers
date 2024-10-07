/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/31 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	check_life(t_table *table, size_t philo_count);
static bool	is_all_fed(t_table *table, size_t meal_count, size_t philo_count);
static void	end_threads(t_table *table, pthread_t observer_tid);

void	manage_dinner(t_table *table)
{
	pthread_t	observer_tid;
	size_t		philo_count;
	size_t		i;

	i = -1;
	philo_count = get_philo_count(table);
	table->start_time = get_time();
	while (++i < philo_count)
	{
		pthread_mutex_init(&table->philosophers[i].fork, NULL);
		table->philosophers[i].meals_count = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].id = i;
		table->philosophers[i].table = table;
	}
	pthread_create(&observer_tid, NULL, observer, table);
	i = -1;
	while (++i < philo_count)
		pthread_create(&table->philosophers[i].tid,
			NULL, conscience, table->philosophers + i);
	end_threads(table, observer_tid);
}

void	*observer(void *arg)
{
	t_table	*table;
	size_t	meal_count;
	size_t	philo_count;

	table = (t_table *) arg;
	meal_count = get_meal_count(table);
	philo_count = get_philo_count(table);
	while (check_life(table, philo_count)
		&& !is_all_fed(table, meal_count, philo_count))
		;
	pthread_mutex_lock(table->infos + VISIBILITY);
	table->is_visible = false;
	pthread_mutex_unlock(table->infos + VISIBILITY);
	return (NULL);
}

static bool	check_life(t_table *table, size_t philo_count)
{
	size_t	index;

	index = -1;
	while (++index < philo_count)
	{
		if (get_duration(table)
			- get_philo_last_meal_time(table->philosophers + index)
			>= get_time_to_die(table))
		{
			note(table->philosophers + index, DEAD);
			return (false);
		}
	}
	return (true);
}

static bool	is_all_fed(t_table *table, size_t meal_count, size_t philo_count)
{
	size_t	index;

	index = -1;
	while (++index < philo_count)
		if (get_philo_meal_count(table->philosophers + index) < meal_count)
			return (false);
	return (true);
}

static void	end_threads(t_table *table, pthread_t observer_tid)
{
	size_t	index;
	size_t	philo_count;

	index = -1;
	philo_count = get_philo_count(table);
	pthread_join(observer_tid, NULL);
	while (++index < philo_count)
		pthread_join(table->philosophers[index].tid, NULL);
	index = -1;
	while (++index < philo_count)
		pthread_mutex_destroy(&table->philosophers[index].fork);
	index = -1;
	while (++index < INFO_MUTEX_COUNT)
		pthread_mutex_destroy(table->infos + index);
	pthread_mutex_destroy(&table->print);
	free(table->philosophers);
}
