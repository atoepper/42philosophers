/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:51:48 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/22 15:52:24 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monitor	monit;
	t_philo		*philo;

	if (parse_arguments(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	philo = NULL;
	if (init_simulation(&monit, &philo, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (create_philo_threads(&monit, philo) == SUCCESS)
		start_simulation(philo, argc);
	free_resources(&monit, &philo);
	return (EXIT_SUCCESS);
}
