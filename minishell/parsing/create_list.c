/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:37 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 13:09:04 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_len(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	command_len(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			break ;
		count++;
		token = token->next;
	}
	return (count);
}

void	append_command(t_cmd **command, t_cmd *command_t)
{
	t_cmd	*tmp_token;

	tmp_token = *command;
	if (!tmp_token)
	{
		(*command) = command_t;
		(*command)->next = NULL;
	}
	else
	{
		while (tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = command_t;
		tmp_token->next->next = NULL;
	}
}


t_cmd	*create_list(t_token *token)
{
	t_cmd	*command;
	t_cmd	*command_t;
	int		i;
	int		j;
	int		len;

	i = 0;
	command = NULL;
	command_t = NULL;
	len = pipe_len(token) + 1;
	while (i < len)
	{
		command_t = malloc(sizeof(t_cmd));
		command_t->argv = (char **)malloc(sizeof(char *) * (command_len(token) + 1));
		j = 0;
		while (token && token->type != PIPE)
		{
			command_t->argv[j] = ft_strdup(token->str);
			token = token->next;
			j++;
		}
		if (token->type == PIPE)
			token = token->next;
		command_t->argv[j] = NULL;
		append_command(&command, command_t);
		i++;
	}
	return (command);
}
