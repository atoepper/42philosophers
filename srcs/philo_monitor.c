/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:53:19 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 14:29:21 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	set_end_flag(t_monitor *m)
{
	pthread_mutex_lock(&m->dead_lock);
	m->end_flag = 1;
	pthread_mutex_unlock(&m->dead_lock);
}

void	monitor_routine(t_monitor *m, t_phil *philo)
{
	int			i;

	i = 0;
	m->start_time = get_time ();
	while (!check_end_flag(m))
	{
		i = 0;
		while (i < m->phil_num && !check_end_flag(m))
		{
			pthread_mutex_lock(&m->last_meal_lock);
			if ((get_time () - philo[i].last_meal) > m->time_to_die)
			{
				philo_write("died", &m->philo[i], get_time());
				set_end_flag(m);
			}
			pthread_mutex_unlock(&m->last_meal_lock);
			i++;
		}
		if (m->finished == m->phil_num)
			set_end_flag(m);
	}
}

int	start_monitor(t_monitor *m)
{
	if (create_threads(m, philo_routine) == -1)
		return (-1);
	monitor_routine(m, m->philo);
	join_threads(m);
	return (0);
}
