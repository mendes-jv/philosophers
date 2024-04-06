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

bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->right_fork == philo->left_fork)
	{
		usleep(philo->time_to_die);
		philo->is_alive = false;
	}
	if (pthread_mutex_trylock(philo->right_fork))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	note(philo->start_time, philo->id, TAKEN_FORK, philo->print);
	note(philo->start_time, philo->id, TAKEN_FORK, philo->print);
	return (true);
}

//pthread_mutex_lock(superego->left_fork);
//note(id, ego, TAKEN_FORK);
//if (superego->right_fork == superego->left_fork)
//{
//usleep(id->time_to_die);
//note(id, ego, DEAD);
//return (NULL);
//}
//pthread_mutex_lock(superego->right_fork);
//note(id, ego, TAKEN_FORK);

void	eat(t_philo *philo)
{
	note(philo->start_time, philo->id, EATING, philo->print);
	usleep(philo->time_to_eat);
	philo->meal_time = get_time();
	philo->meals_count--;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	note(philo->start_time, philo->id, SLEEPING, philo->print);
	usleep(philo->time_to_sleep);
	note(philo->start_time, philo->id, THINKING, philo->print);
}
