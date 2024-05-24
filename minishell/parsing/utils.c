/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:19:00 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/23 16:54:29 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sep(char *str)
{
	if (*str == ' ')
		return (1);
	if ((ft_strncmp(str, ">>", 2) == 0) || (ft_strncmp(str, "<<", 2) == 0))
		return (2);
	else if (*str == '>' || *str == '<' || *str == '|' || *str == ';')
		return (3);
	return (0);
}

void	skip_space(char **str)
{
	while (*(*str) == ' ' || *(*str) == '\t' \
		|| *(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
}

void	append_token(t_token **token, char *str)
{
	t_token	*tmp_token;

	tmp_token = *token;
	if (!tmp_token)
	{
		(*token) = malloc(sizeof(t_token));
		(*token)->str= ft_strdup(str);
		(*token)->next = NULL;
		(*token)->prev = NULL;
	}
	else
	{
		while (tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = malloc(sizeof(t_token));
		tmp_token->next->prev = tmp_token;
		tmp_token->next->str = ft_strdup(str);
		tmp_token->next->next = NULL;
	}
}

void	free_stack(t_token **stack)
{
	t_token	*current;
	t_token	*next;

	current = *stack;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}

int	quotes(char *str)
{
	char	c;

	c = 0;
	skip_space(&str);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str == '\0')
			{
				printf("minishell: syntax error with open quotes\n");
				return (1);
			}
		}
		str++;
	}
	return (0);
}

int	alloc_mem(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (check_sep(str) == 1)
		return (1);
	else if (check_sep(str) == 3)
		return (2);
	if (*str == '\'' || *str == '\"')
	{
		c = *str;
		str++;
	}
	while (*str && *str != c)
	{
		if (check_sep(str) != 0)
			break ;
		i++;
		str++;
	}
	return (i);
}












