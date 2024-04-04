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

//#include "../includes/philosophers.h"
//
//bool	take_forks(t_philo *philo)
//{
//	if (pthread_mutex_trylock(philo->left_fork))
//		return (false);
//	note(philo->id, philo->id->philo_count, TAKEN_FORK);
//	if (philo->right_fork == philo->left_fork)
//		return (false);
//	if (pthread_mutex_trylock(philo->right_fork))
//	{
//		pthread_mutex_unlock(philo->left_fork);
//		return (false);
//	}
//	note(philo->id, philo->id->philo_count, TAKEN_FORK);
//	return (true);
//}
//
//void eat(t_philo *philo)
//{
//	note(philo->id, philo->id->philo_count, EATING);
//	usleep(philo->id->time_to_eat);
//	philo->meal_time = get_time();
//	philo->meals++;
//	pthread_mutex_unlock(philo->left_fork);
//	pthread_mutex_unlock(philo->right_fork);
//}
//
//void sleep_and_think(t_philo *philo)
//{
//	note(philo->id, philo->id->philo_count, SLEEPING);
//	usleep(philo->id->time_to_sleep);
//	note(philo->id, philo->id->philo_count, THINKING);
//}