/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:14:05 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:23:46 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_type(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = *token;
	while (token_tmp->next)
		token_tmp = token_tmp->next;
	if (ft_strcmp(token_tmp->str, "") == 0)
		token_tmp->type = EMPTY;
	else if (ft_strcmp(token_tmp->str, "|") == 0)
		token_tmp->type = PIPE;
	else if (ft_strcmp(token_tmp->str, ">") == 0)
		token_tmp->type = TRUNC;
	else if (ft_strcmp(token_tmp->str, "<") == 0)
		token_tmp->type = INPUT;
	else if (ft_strcmp(token_tmp->str, ">>") == 0)
		token_tmp->type = APPEND;
	else if (ft_strcmp(token_tmp->str, "<<") == 0)
		token_tmp->type = heredoc;
	else if (token_tmp->prev == NULL || token_tmp->prev->type == PIPE)
		token_tmp->type = COMMAND;
	else if (token_tmp->prev->prev && token_tmp->prev->prev->type == heredoc)
		token_tmp->type = COMMAND;
	else
		token_tmp->type = ARG;
}

char	*get_token(char **str)
{
	char	*line;
	int		i;
	char	c;

	i = 0;
	c  = 0;
	line = NULL;
	line = (char *)malloc(alloc_mem(*str) + 1);
	while (*(*str))
	{
		if (*(*str) == '\"' || *(*str) == '\'')
		{
			if (*(*str) == c)
				c = 0;
			else
				c = *(*str);
		}
		line[i] = *(*str);
		i++;
		if (check_sep(str, c) != 0)
			break ;
		(*str)++;
	}
	line[i] = '\0';
	return (line);
}

t_token	*tokenize(char **str)
{
	t_token	*token;
	char	*line;

	line = NULL;
	token = NULL;
	while (*(*str))
	{
		skip_space(str);
		line = get_token(str);
		append_token(&token, line);
		token_type(&token);
		free(line);
		if (*(*str) == '\0')
			break ;
		(*str)++;
		skip_space(str);
	}
	return (token);
}

int	parsing(t_obj *obj, char *str)
{
	if (str == NULL)
		return (0);
	else if (quotes(str) == FAILURE)
		return (FAILURE);
	obj->token = tokenize(&str);
	if (ft_syntax(obj->token) == FAILURE)
	{
		free_token(&obj->token);
		return (FAILURE);
	}
	expand(obj);
	obj->cmd = create_list(obj->token);
	free_token(&obj->token);
	return (0);
}
