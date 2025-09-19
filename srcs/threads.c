/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:53:46 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/22 16:10:03 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_monitor *monitor, t_philo *philo)
{
	int		i;
	int		philo_create_status;

	i = -1;
	pthread_mutex_lock(&monitor->m_start_time);
	monitor->start_time = get_cur_time();
	while (++i < (int)monitor->phil_num)
	{
		philo[i].last_meal = monitor->start_time;
		if (i % 2 == 1)
			philo_create_status = \
				pthread_create(monitor->philo[i], NULL, \
										philo_even, &philo[i]);
		else
			philo_create_status = \
				pthread_create(monitor->philo[i], NULL, \
										philo_odd, &philo[i]);
	}
	pthread_mutex_unlock(&monitor->m_start_time);
	return (SUCCESS);
}
