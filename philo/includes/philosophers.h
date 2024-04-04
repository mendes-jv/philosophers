/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
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
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Structs
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	pthread_t	tid;
	size_t		meals;
	size_t		meal_time;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	bool		is_alive;
}	t_philo;

typedef struct s_info
{
	ssize_t	philo_count;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	meal_count;
	size_t	start_time;
	t_philo	*philosophers;
	t_mutex	*forks;
}	t_info;

typedef struct s_arg {
	t_info	*table;
	int		index;
}	t_arg;

//Definitions
# ifndef WRONG_ARG_COUNT
#  define WRONG_ARG_COUNT "\
\033[0;31mInvalid number of arguments.\nUsage: ./philo \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[optional_number_of_meals]\033[0m"
# endif //WRONG_ARG_COUNT

# ifndef WRONG_PHILO_COUNT
#  define WRONG_PHILO_COUNT "\
\033[0;31mInvalid number of philosophers. Must be a digit \
between 1 and 200.\033[0m"
# endif //WRONG_PHILO_COUNT

# ifndef WRONG_TIME_TO_DIE
#  define WRONG_TIME_TO_DIE "\
\033[0;31mInvalid time to die. Must be a digit between 60 \
and SIZE_T_MAX/1000.\033[0m"
# endif //WRONG_TIME_TO_DIE

# ifndef WRONG_TIME_TO_EAT
#  define WRONG_TIME_TO_EAT "\
\033[0;31mInvalid time to eat. Must be a digit between 60 \
and SIZE_T_MAX/1000.\033[0m"
# endif //WRONG_TIME_TO_EAT

# ifndef WRONG_TIME_TO_SLEEP
#  define WRONG_TIME_TO_SLEEP "\
\033[0;31mInvalid time to sleep. Must be a digit between 60 \
and SIZE_T_MAX/1000.\033[0m"
# endif //WRONG_TIME_TO_SLEEP

# ifndef WRONG_MEAL_COUNT
#  define WRONG_MEAL_COUNT "\
\033[0;31mInvalid number of meals. Must be between 0 and SIZE_T_MAX/1000.\033[0m"
# endif //WRONG_MEAL_COUNT

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "\033[0;31mError allocating memory.\033[0m"
# endif //MALLOC_ERROR

# ifndef MUTEX_ERROR
#  define MUTEX_ERROR "\033[0;31mError creating mutex.\033[0m"
# endif //MUTEX_ERROR

# ifndef TAKEN_FORK
#  define TAKEN_FORK "\033[0;32m has taken a fork.\033[0m"
# endif //TAKEN_FORK

# ifndef EATING
#  define EATING "\033[0;32m is eating.\033[0m"
# endif //EATING

# ifndef SLEEPING
#  define SLEEPING "\033[0;32m is sleeping.\033[0m"
# endif //SLEEPING

# ifndef THINKING
#  define THINKING "\033[0;32m is thinking.\033[0m"
# endif //THINKING

# ifndef DEAD
#  define DEAD "\033[0;31m died.\033[0m"
# endif //DEAD

// Prototypes
ssize_t	atod(char *arg);
void	error(char *message);
size_t	get_time(void);
void	manage_dinner(t_info *table);
void	note(t_info *id, int ego, char *message);
void	set_table(t_info *table, char **args);

#endif //PHILOSOPHERS_H
