/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:58:04 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 19:57:08 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_word_and_vars(t_token token, t_cmdnode *node,
	t_shcontext *env)
{
	char	*new_val;

	if (token.type == TKN_WORD || token.type == TKN_ENVAR)
	{
		new_val = expand_text(token.val, env);
		if (!node->cmd)
		{
			node->cmd = new_val;
			node->argv[0] = ft_strdup(new_val);
			node->argc = 1;
		}
		else
		{
			node->argv[node->argc] = new_val;
			node->argc++;
			if (node->argc >= MAX_ARGS)
			{
				my_perror("error: too many args!");
				return (-1);
			}
		}
	}
	return (0);
}

static int	check_infiles(t_tkdata *tkd, t_cmdnode *node, t_shcontext *env)
{
	if (tkd->tokens[*(tkd->cur)].type == TKN_LT
		|| tkd->tokens[*(tkd->cur)].type == TKN_HRDC)
	{
		if (tkd->tokens[*(tkd->cur)].type == TKN_LT)
			node->redir.infiles[node->redir.n_in].type = F_IN;
		if (tkd->tokens[*(tkd->cur)].type == TKN_HRDC)
			node->redir.infiles[node->redir.n_in].type = F_HEREDOC;
		if (++(*(tkd->cur)) >= tkd->n_tokens)
		{
			my_perror("syntax error: missing value after `<'/'<<' at the end!");
			return (-1);
		}
		if (tkd->tokens[*(tkd->cur)].type == TKN_WORD
			|| tkd->tokens[*(tkd->cur)].type == TKN_ENVAR)
			read_file(tkd->tokens[*(tkd->cur)], node, 1, env);
		else
		{
			my_perror("syntax error: missing value after `<'/'<<'!");
			return (-1);
		}
		node->redir.n_in++;
		if (node->redir.n_in >= MAX_FILES)
			return (my_perror("error: too many infiles!"), -1);
	}
	return (0);
}

static int	check_outfiles(t_tkdata *tkd, t_cmdnode *node, t_shcontext *env)
{
	if (tkd->tokens[*(tkd->cur)].type == TKN_GT
		|| tkd->tokens[*(tkd->cur)].type == TKN_APPD)
	{
		if (tkd->tokens[*(tkd->cur)].type == TKN_GT)
			node->redir.outfiles[node->redir.n_out].type = F_OUT;
		if (tkd->tokens[*(tkd->cur)].type == TKN_APPD)
			node->redir.outfiles[node->redir.n_out].type = F_APPEND;
		if (++(*(tkd->cur)) >= tkd->n_tokens)
		{
			my_perror("syntax error: missing file after `>'/'>>' at the end!");
			return (-1);
		}
		if (tkd->tokens[*(tkd->cur)].type == TKN_WORD
			|| tkd->tokens[*(tkd->cur)].type == TKN_ENVAR)
			read_file(tkd->tokens[*(tkd->cur)], node, 0, env);
		else
		{
			my_perror("syntax error: missing file after `>'/'>>'!");
			return (-1);
		}
		node->redir.n_out++;
		if (node->redir.n_out >= MAX_FILES)
			return (my_perror("error: too many outfiles!"), -1);
	}
	return (0);
}

static int	check_pipe(t_token *tokens, int t, int n_tokens, int *n)
{
	if ((t == 0 && tokens[t].type == TKN_PIPE)
		|| (t == n_tokens - 1 && tokens[t].type == TKN_PIPE))
	{
		my_perror("syntax error: bad pipe usage!");
		return (-1);
	}
	if (tokens[t].type == TKN_PIPE)
	{
		if (t + 1 < n_tokens && tokens[t + 1].type == TKN_PIPE)
		{
			my_perror("syntax error: bad pipe usage!");
			return (-1);
		}
		(*n)++;
		if (*n >= MAX_NODES)
			return (my_perror("error: too many command nodes!"), -1);
	}
	return (0);
}

/**
 * PARSER
 * It builds command nodes using the tokens.
 * It identifies some syntax errors.
 * @returns number of nodes created, -1 if grammar fails
 */
int	parse_tokens(t_token *tokens, int n_tokens, t_cmdnode *nodes,
	t_shcontext *env)
{
	int			t;
	int			n;
	int			ok;
	t_tkdata	tkdata;

	ft_memset(nodes, '\0', sizeof(t_cmdnode) * MAX_NODES);
	n = 0;
	t = 0;
	ok = 1;
	tkdata.cur = &t;
	tkdata.tokens = tokens;
	tkdata.n_tokens = n_tokens;
	while (t < n_tokens && ok)
	{
		ok = ok && (check_word_and_vars(tokens[t], &nodes[n], env) == 0);
		ok = ok && (check_infiles(&tkdata, &nodes[n], env) == 0);
		ok = ok && (check_outfiles(&tkdata, &nodes[n], env) == 0);
		ok = ok && (check_pipe(tokens, t, n_tokens, &n) == 0);
		t++;
	}
	n++;
	if (!ok)
		return (-1);
	return (n);
}
