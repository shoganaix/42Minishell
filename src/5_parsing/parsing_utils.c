/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:57:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 15:55:56 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * check quotes and return found word.
 * returns string (with quotes if there were any)
 * 
 */
char	*read_word(const char *input, int *i)
{
	char	*word;
	int		j;
	char	q_char;

	q_char = '\0';
	j = *i;
	while (input[j]
		&& ((!q_char && !(isreserved(input[j]) || is_space(input[j])))
			|| q_char))
	{
		if (!q_char && (input[j] == '"' || input[j] == '\''))
			q_char = input[j];
		else if (q_char && input[j] == q_char)
			q_char = '\0';
		j++;
	}
	if (q_char)
	{
		my_perror("syntax error: quote not finished.");
		return (*i = j, NULL);
	}
	word = ft_strndup(&input[*i], j - *i);
	if (!word)
		my_perror_exit("strndup: mem error.");
	return (*i = j, word);
}

void	free_tokens(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if (tokens[i].type == TKN_ENVAR || tokens[i].type == TKN_WORD)
			free(tokens[i].val);
		i++;
	}
}

void	read_file(t_token token, t_cmdnode *node,
	int is_infile, t_shcontext *env)
{
	char	*new_val;

	if (token.type == TKN_WORD || token.type == TKN_ENVAR)
		new_val = expand_text(token.val, env);
	if (is_infile)
		node->redir.infiles[node->redir.n_in].filename_delim = new_val;
	else
		node->redir.outfiles[node->redir.n_out].filename = new_val;
}
