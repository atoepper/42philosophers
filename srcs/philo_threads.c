/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:35 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 12:26:44 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	create_threads(t_monitor *m, void *(*philo_routine)(void *))
{
	int	i;

	i = 0;
	while (i < m->phil_num)
	{
		if (pthread_create(&m->philo[i].thread, NULL,
				philo_routine, &m->philo[i]) != 0)
			return (printf("Error while creating threads\n"), -1);
		pthread_mutex_lock(&m->last_meal_lock);
		m->philo[i++].last_meal = get_time();
		pthread_mutex_unlock(&m->last_meal_lock);
	}
	return (0);
}

int	join_threads(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->phil_num)
		if (pthread_join(m->philo[i++].thread, NULL) != 0)
			return (printf("Error while joining threads\n"), -1);
	return (0);
}
