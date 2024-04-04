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

static void	*conscience(void *arg);

void	manage_dinner(t_info *table)
{
	int index;

	index = 0;
	while (index < table->philo_count)
		pthread_create(&table->philosophers[index].tid, NULL,
					   conscience, &(t_arg) {table, index}), index++;
	index = 0;
	while (index < table->philo_count)
		pthread_join(table->philosophers[index++].tid, NULL);
	index = 0;
	while (index < table->philo_count)
		pthread_mutex_destroy(&table->forks[index++]);
}

static void	*conscience(void *arg)
{
	t_philo	*superego;
	t_info	*id;
	int 	ego;

	ego = ((t_arg*)arg)->index;
	id = ((t_arg *)arg)->table;
	superego = id->philosophers + ego;
	while (superego->is_alive)
	{
		pthread_mutex_lock(superego->left_fork);
		note(id, ego, TAKEN_FORK);
		if (superego->right_fork == superego->left_fork)
			return (usleep(id->time_to_die), note(id, ego, DEAD), (NULL));
		pthread_mutex_lock(superego->right_fork), note(id, ego, TAKEN_FORK);
		note(id, ego, EATING), usleep(id->time_to_eat);
		superego->meal_time = get_time();
		superego->meals++;
		pthread_mutex_unlock(superego->left_fork);
		pthread_mutex_unlock(superego->right_fork);
		note(id, ego, SLEEPING);
		usleep(id->time_to_sleep);
		note(id, ego, THINKING);
	}
	return (NULL);
}