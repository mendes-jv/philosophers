/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:18:02 by jovicto2          #+#    #+#             */
/*   Updated: 2024/03/28 11:18:04 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//Includes
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Structs
typedef struct s_info
{
	size_t		philo_count;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	useconds_t	meal_count;
}	t_info;

//Definitions
# ifndef WRONG_ARG_COUNT
#  define WRONG_ARG_COUNT "Invalid number of arguments"
# endif //WRONG_ARG_COUNT

# ifndef WRONG_PHILO_COUNT
#  define WRONG_PHILO_COUNT "Invalid number of philosophers. Must be between 1 and 200."
# endif //WRONG_PHILO_COUNT

# ifndef WRONG_TIME_TO_DIE
#  define WRONG_TIME_TO_DIE "Invalid time to die. Must be between 60 and 1000000."
# endif //WRONG_TIME_TO_DIE

# ifndef WRONG_TIME_TO_EAT
#  define WRONG_TIME_TO_EAT "Invalid time to eat. Must be between 60 and 1000000."
# endif //WRONG_TIME_TO_EAT

# ifndef WRONG_TIME_TO_SLEEP
#  define WRONG_TIME_TO_SLEEP "Invalid time to sleep. Must be between 60 and 1000000."
# endif //WRONG_TIME_TO_SLEEP

# ifndef WRONG_MEAL_COUNT
#  define WRONG_MEAL_COUNT "Invalid number of meals. Must be between 0 and 200."
# endif //WRONG_MEAL_COUNT

// Prototypes
void	set_table(t_info *table, char **args);
void	manage_dinner(t_info *table);

#endif //PHILOSOPHERS_H
