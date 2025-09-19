/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:30:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/22 15:55:02 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

void	ft_print_error(t_err err_type)
{
	if (err_type == ARG_NUM)
		ft_putstr_fd("Usage: <philnum> <die> <eat> <sleep> [<meals>]\n", 2);
	if (err_type == ARG_RANGE)
		ft_putstr_fd("Invalid argument. Only positive integers accepted\n", 2);
	if (err_type == MALLOC)
		ft_putstr_fd("Fatal: Malloc error\n", 2);
	if (err_type == THREAD)
		ft_putstr_fd("Fatal: Thread error\n", 2);
}
