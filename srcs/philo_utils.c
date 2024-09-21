/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:55:59 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 14:30:49 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	is_num(char *arg)
{
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (0);
		arg++;
	}
	return (1);
}

int	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("%s%s%s", USAGE_1, USAGE_2, USAGE_3), -1);
	while (i < argc)
	{
		if (!is_num(argv[i]))
			return (printf("%s%s%s", USAGE_1, USAGE_2, USAGE_3), -1);
		i++;
	}
	if (ft_atoi(argv[1]) > PHIL_MAX)
		return (printf("Number of philosophers exceeding maximum"), -1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\v' || *str == '\f' )
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (sign * nbr);
}

void	philo_write(char *str, t_phil *phil, size_t time_stamp)
{
	pthread_mutex_lock(&phil->monit->write_lock);
	if (!check_end_flag(phil->monit))
	{
		printf("%s%li %s%i %s%s\n", YELLOW,
			time_stamp, BYELLOW, phil->id, NC, str);
	}
	pthread_mutex_unlock(&phil->monit->write_lock);
}

int	check_end_flag(t_monitor *m)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&m->dead_lock);
	if (m->end_flag)
		i = 1;
	pthread_mutex_unlock(&m->dead_lock);
	return (i);
}
