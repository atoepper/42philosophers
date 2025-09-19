/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:19:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/23 10:01:30 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_lfork(t_philo *philo)
{
	pthread_mutex_lock(philo->monit->forks[philo->lfork]);
	philo->monit->fork_status[philo->lfork] = LOCK;
	philo_write(philo, philo->id, "has taken a fork");
}

void	take_rfork(t_philo *philo)
{
	pthread_mutex_lock(philo->monit->forks[philo->rfork]);
	philo->monit->fork_status[philo->rfork] = LOCK;
	philo_write(philo, philo->id, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	size_t	time_to_finish;

	time_to_finish = get_cur_time() + philo->monit->time_to_eat;
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_cur_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	philo_write(philo, philo->id, "is eating");
	while (get_cur_time() < time_to_finish)
		usleep(300);
	pthread_mutex_lock(&philo->m_finished_meals);
	philo->finished_meals++;
	pthread_mutex_unlock(&philo->m_finished_meals);
	philo->monit->fork_status[philo->lfork] = UNLOCK;
	philo->monit->fork_status[philo->rfork] = UNLOCK;
	pthread_mutex_unlock(philo->monit->forks[philo->lfork]);
	pthread_mutex_unlock(philo->monit->forks[philo->rfork]);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time_to_wakeup;

	time_to_wakeup = get_cur_time() + philo->monit->time_to_sleep;
	philo_write(philo, philo->id, "is sleeping");
	while (get_cur_time() < time_to_wakeup)
		usleep(300);
}

void	philo_think(t_philo *philo)
{
	philo_write(philo, philo->id, "is thinking");
}
