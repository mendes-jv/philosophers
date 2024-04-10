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

static void	*observer(void *arg);
static bool	set_possible_death(t_info *table);
static bool	check_starvation(t_philo *philo);
static bool	is_all_fed(t_info *table);

void	manage_dinner(t_info *table)
{
	pthread_t	observer_tid;
	int			index;

	index = 0;
	if (pthread_create(&observer_tid, NULL, observer, table))
		error(""); //TODO: error message and thread creation and join check
	while (index < table->philo_count)
	{
		pthread_create(&table->philosophers[index].tid, NULL,
			conscience, table->philosophers + index);
		index++;
	}
	index = 0;
	while (index < table->philo_count)
		pthread_join(table->philosophers[index++].tid, NULL);
	index = 0;
	while (index < table->philo_count)
		pthread_mutex_destroy(&table->forks[index++]);
	pthread_mutex_destroy(table->philosophers->print);
}

static void	*observer(void *arg)
{
	t_info	*table;

	table = (t_info *)arg;
	while (set_possible_death(table) && !is_all_fed(table))
		usleep(1000);
	return (NULL);
}

static bool	set_possible_death(t_info *table)
{
	t_philo	*philosophers;
	int		index;

	index = 0;
	philosophers = table->philosophers;
	while (index < table->philo_count)
	{
		if (check_starvation(philosophers + index))
		{
			note(philosophers->start_time, philosophers[index].id, DEAD,
				 philosophers->print);
			pthread_mutex_lock(philosophers->life);
			philosophers[index].is_alive = false;
			pthread_mutex_unlock(philosophers->life);
		}
		index++;
	}
}

static bool check_starvation(t_philo *philo)
{
	bool	is_starving;

	is_starving = false;
	pthread_mutex_lock(philo->meal);
	if (get_time() - philo->meal_time >= (size_t)philo->time_to_die)
		is_starving = true;
	pthread_mutex_unlock(philo->meal);
	return (is_starving);
}

static bool	is_all_fed(t_info *table)
{
	bool	is_all_fed;
	int		index;
	int		fed_count;

	is_all_fed = false;
	index = 0;
	fed_count = 0;
	//TODO: check if time_to_eat is really setted or if it is not passed as an argument
	while (index < table->philo_count)
	{
		pthread_mutex_lock(table->philosophers[index].meal);
		if (!table->philosophers[index].meals_count)
			fed_count++;
		pthread_mutex_unlock(table->philosophers[index].meal);
		index++;
	}
	if (fed_count == table->philo_count)
	{
		pthread_mutex_lock(table->philosophers->meal);
		table->philosophers->is_alive = false;
		pthread_mutex_unlock(table->philosophers->meal);
		is_all_fed = true;
	}
	return (is_all_fed);
}
