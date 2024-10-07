/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/28 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	get_time_to_die(t_table *table)
{
	size_t	time_to_die;

	pthread_mutex_lock(table->infos + TIME_TO_DIE);
	time_to_die = table->time_to_die;
	pthread_mutex_unlock(table->infos + TIME_TO_DIE);
	return (time_to_die);
}

size_t	get_meal_count(t_table *table)
{
	size_t	meals_count;

	meals_count = __SIZE_MAX__;
	pthread_mutex_lock(table->infos + MEALS_COUNT);
	if (table->meal_count)
		meals_count = table->meal_count;
	pthread_mutex_unlock(table->infos + MEALS_COUNT);
	return (meals_count);
}

size_t	get_philo_id(t_philo *philo)
{
	size_t	id;

	pthread_mutex_lock(philo->table->infos + PHILO_ID);
	id = philo->id;
	pthread_mutex_unlock(philo->table->infos + PHILO_ID);
	return (id);
}

size_t	get_philo_meal_count(t_philo *philo)
{
	size_t	plates;

	pthread_mutex_lock(philo->table->infos + PHILO_MEAL_COUNT);
	plates = philo->meals_count;
	pthread_mutex_unlock(philo->table->infos + PHILO_MEAL_COUNT);
	return (plates);
}

size_t	get_philo_last_meal_time(t_philo *philo)
{
	size_t	last_meal_time;

	pthread_mutex_lock(philo->table->infos + PHILO_LMEAL_TIME);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(philo->table->infos + PHILO_LMEAL_TIME);
	return (last_meal_time);
}
