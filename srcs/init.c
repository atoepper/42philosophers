/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:04:37 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/22 15:53:03 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_resources(t_monitor *monit, t_philo **philo)
{
	int	phil_num;
	int	i;

	phil_num = monit->phil_num;
	monit->fork_status = (int *)ft_calloc(sizeof(int) * phil_num);
	monit->philo = (pthread_t **)malloc(sizeof(pthread_t *) * phil_num);
	monit->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) \
		* phil_num);
	*philo = (t_philo *)ft_calloc(sizeof(t_philo) * phil_num);
	if ((*philo == NULL) || (monit->philo == NULL) \
		|| (monit->forks == NULL) || (monit->fork_status == NULL))
		return (ft_print_error(MALLOC), FAILURE);
	i = -1;
	while (++i < phil_num)
	{
		monit->philo[i] = (pthread_t *)malloc(sizeof(pthread_t));
		monit->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if ((monit->philo[i] == NULL) || (monit->forks[i] == NULL))
			return (ft_print_error(MALLOC), FAILURE);
	}
	return (SUCCESS);
}

void	assign_args(t_monitor *monit, int argc, char **argv)
{
	monit->phil_num = ft_check_argtype(argv[1]);
	monit->time_to_die = ft_check_argtype(argv[2]);
	monit->time_to_eat = ft_check_argtype(argv[3]);
	monit->time_to_sleep = ft_check_argtype(argv[4]);
	if (argc == 6)
		monit->meals_to_eat = ft_check_argtype(argv[5]);
}

void	init_resources(t_monitor *monit, t_philo *philo)
{
	size_t	i;

	pthread_mutex_init(&monit->m_write, NULL);
	pthread_mutex_init(&monit->m_start_time, NULL);
	pthread_mutex_init(&monit->m_endflag, NULL);
	i = -1;
	while (++i < monit->phil_num)
	{
		philo[i].id = i + 1;
		philo[i].rfork = (i + 1) % monit->phil_num;
		philo[i].lfork = i;
		philo[i].monit = monit;
		pthread_mutex_init(monit->forks[i], NULL);
		pthread_mutex_init(&philo[i].m_finished_meals, NULL);
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
	}
}

int	init_simulation(t_monitor *monit, t_philo **philo, int argc, char **argv)
{
	memset(monit, 0, sizeof(t_monitor));
	assign_args(monit, argc, argv);
	if (malloc_resources(monit, philo) == FAILURE)
	{
		free_resources(monit, philo);
		return (FAILURE);
	}
	init_resources(monit, *philo);
	return (SUCCESS);
}
