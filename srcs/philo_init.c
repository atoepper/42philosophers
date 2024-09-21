/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:58:35 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 12:32:49 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_monitor(t_monitor *m, int argc, char **argv)
{
	m->end_flag = 0;
	m->phil_num = ft_atoi(argv[1]);
	m->time_to_die = (size_t)(ft_atoi(argv[2]));
	m->time_to_eat = (size_t)ft_atoi(argv[3]);
	m->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
		m->meals_to_eat = ft_atoi(argv[5]);
	else
		m->meals_to_eat = -1;
	m->finished = 0;
	m->start_time = 0;
	if (pthread_mutex_init(&m->write_lock, NULL) != 0
		|| pthread_mutex_init(&m->meal_lock, NULL) != 0
		|| pthread_mutex_init(&m->last_meal_lock, NULL) != 0
		|| pthread_mutex_init(&m->dead_lock, NULL) != 0)
		return (printf("Error while creating mutexes\n"), -1);
	return (0);
}

void	init_philo(t_monitor *monit)
{
	int	i;

	i = 0;
	while (i < monit->phil_num)
	{
		monit->philo[i].id = i + 1;
		monit->philo[i].finished_meals = 0;
		monit->philo[i].last_meal = 0;
		monit->philo[i].monit = monit;
		monit->philo[i].lfork = &monit->forks[i];
		if (i < monit->phil_num - 1)
			monit->philo[i].rfork = &monit->forks[i + 1];
		else
			monit->philo[i].rfork = &monit->forks[0];
		i++;
	}
}

int	init_forks(pthread_mutex_t *forks, int phil_num)
{
	int	i;

	i = 0;
	while (i < phil_num)
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
			return (printf("Error while creating mutexes\n"), -1);
	return (0);
}

void	destroy_mutexes(t_monitor *monit)
{
	int	i;

	i = 0;
	while (i < monit->phil_num)
		pthread_mutex_destroy(&monit->forks[i++]);
	pthread_mutex_destroy(&monit->write_lock);
	pthread_mutex_destroy(&monit->meal_lock);
	pthread_mutex_destroy(&monit->last_meal_lock);
	pthread_mutex_destroy(&monit->dead_lock);
}
