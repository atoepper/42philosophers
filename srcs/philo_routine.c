/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:38:21 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 14:32:01 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	grab_forks(t_phil *philo)
{
	pthread_mutex_lock(philo->lfork);
	philo_write("has taken a fork", philo, get_time ());
	pthread_mutex_lock(philo->rfork);
	philo_write("has taken a fork", philo, get_time ());
}

void	philo_eat(t_phil *philo)
{
	t_monitor	*m;

	m = philo->monit;
	philo_write("is eating", philo, get_time());
	pthread_mutex_lock(&philo->monit->last_meal_lock);
	philo->last_meal = get_time ();
	pthread_mutex_unlock(&philo->monit->last_meal_lock);
	ft_sleep(m->time_to_eat, m);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	philo->finished_meals++;
	if (m->meals_to_eat != -1)
	{
		if (philo->finished_meals == m->meals_to_eat)
		{
			pthread_mutex_lock(&m->meal_lock);
			philo->monit->finished++;
			pthread_mutex_unlock(&m->meal_lock);
		}
	}
}

void	philo_sleep(t_phil *philo)
{
	philo_write("is sleeping", philo, get_time ());
	ft_sleep(philo->monit->time_to_sleep, philo->monit);
}

void	philo_think(t_phil *philo)
{
	philo_write("is thinking", philo, get_time());
	if (!check_end_flag(philo->monit))
		grab_forks(philo);
}

void	*philo_routine(void *data)
{
	t_phil		*philo;
	t_monitor	*m;

	philo = (t_phil *)data;
	m = philo->monit;
	if (m->phil_num == 1)
	{
		philo_write("has taken a fork", philo, get_time ());
		ft_sleep(m->time_to_die, m);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!check_end_flag(m))
	{
		philo_think(philo);
		if (!check_end_flag(m))
			philo_eat(philo);
		if (!check_end_flag(m))
			philo_sleep(philo);
	}
	return (NULL);
}
