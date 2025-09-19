/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:15:00 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/22 15:45:12 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_check_argtype(char *str)
{
	size_t	nbr;

	nbr = 0;
	while (*str)
	{
		if (!is_digit(str))
			return (ERROR);
		nbr *= 10;
		nbr += (*str - '0');
		if (nbr > INT_MAX)
			return (ERROR);
		str++;
	}
	if (nbr == 0)
		return (ERROR);
	else
		return (nbr);
}

int	parse_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_print_error(ARG_NUM), FAILURE);
	while (--argc > 0)
		if ((int)ft_check_argtype(argv[argc]) == ERROR)
			return (ft_print_error(ARG_RANGE), FAILURE);
	return (SUCCESS);
}
