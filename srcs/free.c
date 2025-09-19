/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:55:28 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/23 09:52:49 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_monitor *monit)
{
	int	i;

	i = -1;
	while (++i < (int)monit->phil_num)
	{
		pthread_mutex_destroy(monit->forks[i]);
	}
	pthread_mutex_destroy(&monit->m_write);
	pthread_mutex_destroy(&monit->m_start_time);
	pthread_mutex_destroy(&monit->m_endflag);
}

void	free_resources(t_monitor *monit, t_philo **philo)
{
	int	phil_num;
	int	i;

	phil_num = monit->phil_num;
	destroy_all_mutex(monit);
	if (monit->fork_status != NULL)
		free(monit->fork_status);
	if (*philo != NULL)
		free(*philo);
	i = -1;
	if (monit->philo != NULL)
	{
		while ((++i < phil_num) && monit->philo[i])
			free(monit->philo[i]);
		free(monit->philo);
	}
	i = -1;
	if (monit->forks != NULL)
	{
		while ((++i < phil_num) && monit->forks[i])
			free(monit->forks[i]);
		free(monit->forks);
	}
}
