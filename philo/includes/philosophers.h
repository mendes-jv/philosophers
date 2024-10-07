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
typedef pthread_t		t_tid;
typedef struct s_philo	t_philo;

typedef enum e_info {
	VISIBILITY = 0,
	START_TIME,
	PHILO_COUNT,
	MEALS_COUNT,
	TIME_TO_EAT,
	TIME_TO_DIE,
	TIME_TO_SLEEP,
	PHILO_ID,
	PHILO_MEAL_COUNT,
	PHILO_LMEAL_TIME,
	INFO_MUTEX_COUNT
}	t_info;

typedef struct s_table
{
	bool	is_visible;
	ssize_t	philo_count;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	meal_count;
	size_t	start_time;
	t_philo	*philosophers;
	t_mutex	print;
	t_mutex	infos[10];
}	t_table;

struct s_philo {
	size_t	id;
	size_t	meals_count;
	size_t	last_meal_time;
	t_table	*table;
	t_tid	tid;
	t_mutex	fork;
};

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
\033[0;31mInvalid number of meals_count. Must be between 0 and \
SIZE_T_MAX/1000.\033[0m"
# endif //WRONG_MEAL_COUNT

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "\033[0;31mError allocating memory.\033[0m"
# endif //MALLOC_ERROR

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
void	set_table(t_table *table, char **args);
void	manage_dinner(t_table *table);
void	*conscience(void *arg);
void	*observer(void *arg);
void	error(char *message);
size_t	note(t_philo *philo, char *message);
size_t	get_time(void);
size_t	get_meal_count(t_table *table);
size_t	get_philo_count(t_table *table);
size_t	get_time_to_eat(t_table *table);
size_t	get_time_to_sleep(t_table *table);
size_t	get_time_to_die(t_table *table);
size_t	get_philo_id(t_philo *philo);
size_t	get_philo_meal_count(t_philo *philo);
size_t	get_philo_last_meal_time(t_philo *philo);
size_t	get_duration(t_table *table);
bool	get_visibility(t_table *table);

#endif //PHILOSOPHERS_H
