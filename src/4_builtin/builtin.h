/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:47 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 13:33:35 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../2_structs/structs.h"
# include "../3_utils/utils.h"

# define PATH_MAX 1000

int		exec_echo(t_cmdnode node, t_shcontext *env);
int		exec_exit(t_cmdnode node, t_shcontext *env);
int		exec_cd(t_cmdnode node, t_shcontext *env);
int		exec_env(t_cmdnode node, t_shcontext *env);
int		exec_export(t_cmdnode node, t_shcontext *env);
int		exec_unset(t_cmdnode node, t_shcontext *env);
int		exec_pwd(t_cmdnode node, t_shcontext *env);
char	*expand_text(char *code, t_shcontext *env);
char	*expand_dollar(char *text, int *i, t_shcontext *env);
char	*get_env_var(char *var_key, t_shcontext *env);
int		envvar_index(char *key_srch, t_shcontext *env);
void	env_add_one(t_shcontext *env, char *var);
void	update_envvar(char *key, char *value, t_shcontext *env);
void	get_kv(char *line, char **key, char **value);
void	print_export_style(char *line);

#endif