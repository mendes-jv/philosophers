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
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_count;
}	t_info;

//Definitions
# ifndef WRONG_ARG_COUNT
#  define WRONG_ARG_COUNT "\033[0;31mInvalid number of arguments.\nUsage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [optional_number_of_meals]\n\033[0m"
# endif //WRONG_ARG_COUNT

# ifndef WRONG_PHILO_COUNT
#  define WRONG_PHILO_COUNT "\033[0;31mInvalid number of philosophers. Must be a digit between 1 and 200.\n\033[0m"
# endif //WRONG_PHILO_COUNT

# ifndef WRONG_TIME_TO_DIE
#  define WRONG_TIME_TO_DIE "\033[0;31mInvalid time to die. Must be a digit between 60 and 1000000.\n\033[0m"
# endif //WRONG_TIME_TO_DIE

# ifndef WRONG_TIME_TO_EAT
#  define WRONG_TIME_TO_EAT "\033[0;31mInvalid time to eat. Must be a digit between 60 and 1000000.\n\033[0m"
# endif //WRONG_TIME_TO_EAT

# ifndef WRONG_TIME_TO_SLEEP
#  define WRONG_TIME_TO_SLEEP "\033[0;31mInvalid time to sleep. Must be a digit between 60 and 1000000.\n\033[0m"
# endif //WRONG_TIME_TO_SLEEP

# ifndef WRONG_MEAL_COUNT
#  define WRONG_MEAL_COUNT "\033[0;31mInvalid number of meals. Must be between 0 and 200.\n\033[0m"
# endif //WRONG_MEAL_COUNT

// Prototypes
void	set_table(t_info *table, char **args);
void	manage_dinner(t_info *table);
void	print_error(char *message);
size_t	alen(const char *s);
int		atod(char *arg);

#endif //PHILOSOPHERS_H
