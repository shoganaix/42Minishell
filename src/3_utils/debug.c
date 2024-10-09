/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:44 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/02 18:35:56 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	debug(char *msg)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_int(char *name_desc, int n)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " ", 1);
	ft_putnbr_fd(n, 2);
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_str(char *name_desc, char *str)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " ", 1);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_env(t_shcontext *env)
{
	int	i;

	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_CYAN "", 2);
	i = 0;
	while (i < env->n_env)
	{
		ft_printf("%s\n", env->env[i]);
		i++;
	}
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}
