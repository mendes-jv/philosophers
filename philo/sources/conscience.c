/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conscience.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/31 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void take_forks(t_philo *philo);
static void	eat(t_philo *philo);

static void drop_forks(t_philo *philo);
static void	sleep_and_think(t_philo *philo);

void	*conscience(void *arg)
{
	t_philo *philosopher;

	philosopher = ((t_philo *) arg);
	if (get_philo_count(philosopher->table) == 1) {
		note(philosopher, TAKEN_FORK);
		return (NULL);
	}
	while (get_visibility(philosopher->table))
	{
		take_forks(philosopher);
		eat(philosopher);
		drop_forks(philosopher);
		sleep_and_think(philosopher);
	}
	return (NULL);
}

static void take_forks(t_philo *philo)
{
	size_t philo_id;
	size_t last_philo;

	if (!get_visibility(philo->table))
		return;
	philo_id = get_philo_id(philo);
	last_philo = get_philo_id(philo) - 1;
	if (philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo_id == last_philo)
			pthread_mutex_lock(&philo->table->philosophers->fork);
		else
			pthread_mutex_lock(&philo->table->philosophers[philo_id + 1].fork);
	} else {
		if (philo_id == last_philo)
			pthread_mutex_lock(&philo->table->philosophers->fork);
		else
			pthread_mutex_lock(&philo->table->philosophers[philo_id + 1].fork);
		pthread_mutex_lock(&philo->fork);
	}
	note(philo, TAKEN_FORK);
	note(philo, TAKEN_FORK);
}

static void	eat(t_philo *philo)
{
	size_t time_to_eat;

	if (!get_visibility(philo->table))
		return;
	time_to_eat = get_time_to_eat(philo->table);
	pthread_mutex_lock(philo->table->infos + PHILO_LMEAL_TIME);
	philo->last_meal_time = note(philo, EATING);
	pthread_mutex_unlock(philo->table->infos + PHILO_LMEAL_TIME);
	usleep(time_to_eat);
	pthread_mutex_lock(philo->table->infos + PHILO_MEAL_COUNT);
	philo->meals_count++;
	pthread_mutex_unlock(philo->table->infos + PHILO_MEAL_COUNT);
}

static void drop_forks(t_philo *philo)
{
	size_t philo_id;
	size_t last_philo;

	philo_id = get_philo_id(philo);
	last_philo = get_philo_id(philo) - 1;
	if (philo_id % 2 == 0) {
		pthread_mutex_unlock(&philo->fork);
		if (philo_id == last_philo)
			pthread_mutex_unlock(&philo->table->philosophers->fork);
		else
			pthread_mutex_unlock(&philo->table->philosophers[philo_id + 1].fork);
	} else {
		if (philo_id == last_philo)
			pthread_mutex_unlock(&philo->table->philosophers->fork);
		else
			pthread_mutex_unlock(&philo->table->philosophers[philo_id + 1].fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

static void	sleep_and_think(t_philo *philo)
{
	size_t time_to_sleep;

	if (!get_visibility(philo->table))
		return;
	time_to_sleep = get_time_to_sleep(philo->table);
	note(philo, SLEEPING);
	usleep(time_to_sleep);
	if (!get_visibility(philo->table))
		return;
	note(philo, THINKING);
	usleep(1000);
}
