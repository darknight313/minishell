/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:37 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:42:05 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_argv(t_cmd **cmd , t_lexer *lexer , char **argv)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 1;
	tmp_cmd = *cmd;
	if (!tmp_cmd)
	{
		(*cmd) = malloc(sizeof(t_cmd));
		(*cmd)->argv = argv;
		(*cmd)->lexer = lexer;
		(*cmd)->next = NULL;
		(*cmd)->prev = NULL;
	}
	else
	{
		while (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = malloc(sizeof(t_cmd));
		tmp_cmd->next->argv = argv;
		tmp_cmd->next->lexer = lexer;
		tmp_cmd->next->next = NULL;
		tmp_cmd->next->prev = tmp_cmd;
	}
}

void	append_lexer(t_lexer **lexer , char *str, int i)
{
	t_lexer	*tmp_cmd;

	tmp_cmd = *lexer;
	if (!tmp_cmd)
	{
		(*lexer) = malloc(sizeof(t_lexer));
		(*lexer)->str = ft_strdup(str);
		(*lexer)->i = i;
		(*lexer)->next = NULL;
	}
	else
	{
		while (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = malloc(sizeof(t_lexer));
		tmp_cmd->next->str = ft_strdup(str);
		tmp_cmd->next->i = i;
		tmp_cmd->next->next = NULL;
	}
}

t_cmd	*create_list(t_token *token)
{
	t_cmd	*cmd;
	t_lexer	*lexer;
	char	**argv;
	int		i;

	cmd = NULL;
	while (token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(token) + 1));
		argv[argv_len(token)] = NULL;
		i = 0;
		while (token && ft_sep(token) != 2)
		{
			while (token && ft_sep(token) == 0)
			{
				argv[i++] = ft_strdup(token->str);
				token = token->next;
			}
			while (token && ft_sep(token) == 1)
			{
				append_lexer(&lexer, token->next->str, token->type);
				token = token->next->next;
			}
		}
		append_argv(&cmd, lexer, argv);
		if (token)
			token = token->next;
	}
	return (cmd);
}
