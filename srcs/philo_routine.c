/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:29:40 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/23 10:35:51 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end_of_sim(t_monitor *monit)
{
	pthread_mutex_lock(&monit->m_endflag);
	if (monit->end_flag == TRUE)
	{
		pthread_mutex_unlock(&monit->m_endflag);
		return (TRUE);
	}
	return (FALSE);
}

void	*philo_even(void *philoptr)
{
	t_philo	*philo;

	philo = (t_philo *)philoptr;
	pthread_mutex_lock(&philo->monit->m_start_time);
	pthread_mutex_unlock(&philo->monit->m_start_time);
	while (1)
	{
		if (is_end_of_sim(philo->monit) == TRUE)
			return (NULL);
		pthread_mutex_unlock(&philo->monit->m_endflag);
		take_lfork(philo);
		take_rfork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*philo_odd(void *philoptr)
{
	t_philo	*philo;

	philo = (t_philo *)philoptr;
	pthread_mutex_lock(&philo->monit->m_start_time);
	pthread_mutex_unlock(&philo->monit->m_start_time);
	usleep(1000);
	while (1)
	{
		if (is_end_of_sim(philo->monit) == TRUE)
			return (NULL);
		pthread_mutex_unlock(&philo->monit->m_endflag);
		take_rfork(philo);
		if (philo->monit->phil_num == 1)
			ft_one_philo(philo);
		else
		{
			take_lfork(philo);
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
			usleep(300);
		}
	}
	return (NULL);
}

void	philo_write(t_philo *philo, size_t philo_id, char *msg)
{
	size_t	time_stamp;

	pthread_mutex_lock(&philo->monit->m_write);
	if (philo->monit->end_flag == TRUE)
	{
		pthread_mutex_unlock(&philo->monit->m_write);
		return ;
	}
	time_stamp = get_cur_time() - philo->monit->start_time;
	printf("%zu %zu %s\n", time_stamp, philo_id, msg);
	pthread_mutex_unlock(&philo->monit->m_write);
}

void	ft_one_philo(t_philo *philo)
{
	size_t	start_time;

	start_time = get_cur_time ();
	while ((get_cur_time () - start_time) <= philo->monit->time_to_die)
		usleep(50);
	pthread_mutex_unlock(philo->monit->forks[philo->lfork]);
}
