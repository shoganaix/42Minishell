/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 19:39:06 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * print if var has value
 */
void	print_env_style(char *line)
{
	int	pos;

	pos = ft_strchri(line, '=');
	if (pos != -1)
		ft_printf("%s\n", line);
}

int	exec_env(t_cmdnode node, t_shcontext *env)
{
	int	i;

	(void)node;
	i = 0;
	while (env->env[i])
	{
		print_env_style(env->env[i]);
		i++;
	}
	return (0);
}
