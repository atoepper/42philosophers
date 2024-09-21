/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:53:45 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 12:38:24 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"

# define USAGE_1 "Usage: <num_of_phil> <time_to_die>"
# define USAGE_2 " <time_to_eat> <time_to_sleep> "
# define USAGE_3 "[<number_of_times_each_philosopher_must_eat>]\n"

# ifndef PHIL_MAX
#  define PHIL_MAX 200
# endif

struct	s_monitor;

typedef struct s_phil
{
	pthread_t			thread;
	int					id;
	int					finished_meals;
	size_t				last_meal;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	struct s_monitor	*monit;
}	t_phil;

typedef struct s_monitor
{
	int				end_flag;
	int				phil_num;
	int				time_to_eat;
	int				time_to_sleep;
	size_t			time_to_die;
	int				meals_to_eat;
	int				finished;
	size_t			start_time;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	dead_lock;
	t_phil			philo[250];
}	t_monitor;

/* philo_init */
int		init_monitor(t_monitor *m, int argc, char **argv);
void	init_philo(t_monitor *monit);
int		init_forks(pthread_mutex_t *forks, int phil_num);
void	destroy_mutexes(t_monitor *monit);

/* philo_utils */
int		is_num(char *arg);
int		parse_args(int argc, char **argv);
int		ft_atoi(const char *str);
void	philo_write(char *str, t_phil *phil, size_t time_stamp);
int		check_end_flag(t_monitor *m);

/* philo_time */
size_t	get_time(void);
void	ft_sleep(size_t millisec, t_monitor *m);

/* philo_routine */
void	philo_eat(t_phil *philo);
void	philo_sleep(t_phil *philo);
void	philo_think(t_phil *philo);
void	*philo_routine(void *data);

/* threads */
int		create_threads(t_monitor *m, void *(*philo_routine)(void *));
int		join_threads(t_monitor *m);

/* philo_monitor */
int		start_monitor(t_monitor *m);

#endif