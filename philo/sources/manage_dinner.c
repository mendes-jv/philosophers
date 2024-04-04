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
	int	index;

	index = 0;
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
}

static void	*conscience(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);

	//TODO: try to put sleep here with odd-even strategy
	while (philo->is_alive)
	{
		if (!take_forks(philo))
			return (NULL);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
