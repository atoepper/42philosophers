/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:23:55 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/23 10:34:56 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	int		i;
	int		phil_num;
	size_t	time_to_die;
	size_t	passed_time;

	phil_num = philo->monit->phil_num;
	time_to_die = philo->monit->time_to_die;
	i = -1;
	while (++i < phil_num)
	{
		pthread_mutex_lock(&philo[i].m_last_meal);
		passed_time = get_cur_time() - philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].m_last_meal);
		if (passed_time >= time_to_die)
		{
			pthread_mutex_lock(&philo->monit->m_write);
			printf("%zu %d died\n", get_cur_time() - \
				philo->monit->start_time, i + 1);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	check_finished_meals(t_philo *philo)
{
	int	i;
	int	phil_num;
	int	meals_to_eat;

	phil_num = philo->monit->phil_num;
	meals_to_eat = philo->monit->meals_to_eat;
	i = -1;
	while (++i < phil_num)
	{
		pthread_mutex_lock(&philo[i].m_finished_meals);
		if (philo[i].finished_meals < meals_to_eat)
		{
			pthread_mutex_unlock(&philo[i].m_finished_meals);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo[i].m_finished_meals);
	}
	pthread_mutex_lock(&philo->monit->m_write);
	printf("%zu Everyone finished %i meals\n", \
		get_cur_time() - philo->monit->start_time, meals_to_eat);
	return (TRUE);
}

void	start_simulation(t_philo *philo, int argc)
{
	int		i;

	if (argc == 6)
		while (check_dead(philo) == FALSE \
				&& check_finished_meals(philo) == FALSE)
			usleep(500);
	else
		while (check_dead(philo) == FALSE)
			usleep(500);
	pthread_mutex_lock(&philo->monit->m_endflag);
	philo->monit->end_flag = TRUE;
	pthread_mutex_unlock(&philo->monit->m_endflag);
	pthread_mutex_unlock(&philo->monit->m_write);
	i = -1;
	while (++i < (int)philo->monit->phil_num)
		pthread_join(*philo->monit->philo[i], NULL);
}
