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

static bool	check_life(t_philo *philo);
static bool	take_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleep_and_think(t_philo *philo);

void	*conscience(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	if (philo->id % 2)
		usleep(100);
	while (check_life(philo))
	{
		if (!take_forks(philo))
			return (NULL);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

static bool	check_life(t_philo *philo)
{
	bool is_alive;
	pthread_mutex_lock(philo->life);
	is_alive = philo->is_alive;
	pthread_mutex_unlock(philo->life);
	return (is_alive);
}

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	note(philo->start_time, philo->id, TAKEN_FORK, philo->print);
	if (philo->right_fork == philo->left_fork)
	{
		usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	pthread_mutex_lock(philo->right_fork);
	note(philo->start_time, philo->id, TAKEN_FORK, philo->print);
	return (true);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	note(philo->start_time, philo->id, EATING, philo->print);
	philo->meal_time = get_time();
	philo->meals_count--;
	pthread_mutex_unlock(philo->meal);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	sleep_and_think(t_philo *philo)
{
	note(philo->start_time, philo->id, SLEEPING, philo->print);
	usleep(philo->time_to_sleep);
	note(philo->start_time, philo->id, THINKING, philo->print);
}
