/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/28 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool get_visibility(t_table *table)
{
	bool open;

	pthread_mutex_lock(&table->infos[VISIBILITY]);
	open = table->is_visible;
	pthread_mutex_unlock(&table->infos[VISIBILITY]);
	return (open);
}

size_t get_duration(t_table *table)
{
	size_t duration;

	pthread_mutex_lock(&table->infos[START_TIME]);
	duration = get_time() - table->start_time;
	pthread_mutex_unlock(&table->infos[START_TIME]);
	return (duration);
}

size_t get_philo_count(t_table *table)
{
	size_t philo_count;

	pthread_mutex_lock(&table->infos[PHILO_COUNT]);
	philo_count = table->philo_count;
	pthread_mutex_unlock(&table->infos[PHILO_COUNT]);
	return (philo_count);
}

size_t get_time_to_eat(t_table *table)
{
	size_t time_to_eat;

	pthread_mutex_lock(&table->infos[TIME_TO_EAT]);
	time_to_eat = table->time_to_eat;
	pthread_mutex_unlock(&table->infos[TIME_TO_EAT]);
	return (time_to_eat);
}

size_t get_time_to_sleep(t_table *table)
{
	size_t time_to_sleep;

	pthread_mutex_lock(&table->infos[TIME_TO_SLEEP]);
	time_to_sleep = table->time_to_sleep;
	pthread_mutex_unlock(&table->infos[TIME_TO_SLEEP]);
	return (time_to_sleep);
}