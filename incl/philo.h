/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:54:35 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/23 10:23:43 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define LOCK 1
# define UNLOCK 0

typedef enum e_err
{
	ARG_NUM,
	ARG_RANGE,
	MALLOC,
	THREAD
}	t_err;

typedef struct s_monitor
{
	int				end_flag;
	size_t			phil_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meals_to_eat;
	size_t			start_time;
	int				*fork_status;
	pthread_t		**philo;
	pthread_mutex_t	**forks;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_start_time;
	pthread_mutex_t	m_endflag;
}	t_monitor;

typedef struct s_philo
{
	size_t			id;
	size_t			last_meal;
	int				rfork;
	int				lfork;
	int				finished_meals;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	m_finished_meals;
	t_monitor		*monit;
}	t_philo;

/* error.c */
void	ft_print_error(t_err err_type);

/* free.c */
void	destroy_all_mutex(t_monitor *monit);
void	free_resources(t_monitor *monit, t_philo **philos);

/* init.c */
int		init_simulation(t_monitor *monit, t_philo **philo,
			int argc, char **argv);
int		malloc_resources(t_monitor *monit, t_philo **philo);
void	assign_args(t_monitor *monit, int argc, char **argv);
void	init_resources(t_monitor *monit, t_philo *philo);

/* monitor.c */
void	start_simulation(t_philo *philo, int argc);
int		check_finished_meals(t_philo *philo);
int		check_dead(t_philo *philo);

/* parse.c */
int		parse_arguments(int argc, char **argv);
size_t	ft_check_argtype(char *str);

/* philo_routine.c */
void	*philo_odd(void *philoptr);
void	*philo_even(void *philoptr);
void	philo_write(t_philo *philo, size_t philo_id, char *msg);
int		is_end_of_sim(t_monitor *monit);
void	ft_one_philo(t_philo *philo);

/* philo_routine_2.c */
void	take_lfork(t_philo *philo);
void	take_rfork(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);

/* threads.c */
int		create_philo_threads(t_monitor *monitor, t_philo *philo);

/* time.c */
size_t	get_cur_time(void);

/* utils.c */
void	*ft_calloc(size_t size);
int		is_digit(char *str);

#endif