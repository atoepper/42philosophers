/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:55:57 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/21 11:46:08 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	main(int argc, char **argv)
{
	t_monitor		monitor;

	if (parse_args(argc, argv) == -1)
		return (1);
	if (init_monitor(&monitor, argc, argv) == -1)
		return (destroy_mutexes(&monitor), 1);
	if (init_forks(monitor.forks, monitor.phil_num) == -1)
		return (destroy_mutexes(&monitor), 1);
	init_philo(&monitor);
	if (start_monitor(&monitor) == -1)
		return (destroy_mutexes(&monitor), 1);
	destroy_mutexes(&monitor);
	return (0);
}
