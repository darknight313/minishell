/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:19:00 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:36:54 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_token2(t_env **token, char *str)
{
	t_env	*tmp_token;

	tmp_token = *token;
	if (!tmp_token)
	{
		(*token) = malloc(sizeof(t_env));
		(*token)->value = ft_strdup(str);
		(*token)->prev = NULL;
		(*token)->next = NULL;
	}
	else
	{
		while (tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = malloc(sizeof(t_env));
		tmp_token->next->value = ft_strdup(str);
		tmp_token->next->prev = tmp_token;
		tmp_token->next->next = NULL;
	}
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("%d : %s\n", token->type, token->str);
		token = token->next;
	}
}

void	print_argv(t_cmd *cmd)
{
	t_lexer	*lexer;

	while (cmd)
	{
		int j = 0;
		while (cmd->argv[j])
		{
			printf("%s", cmd->argv[j]);
			fflush(0);
			if (cmd->prev)
			{
				printf("prev %s ", cmd->prev->argv[0]);
			}
			j++;
		}
		printf("\n");
		lexer = cmd->lexer;
		while (lexer)
		{
			printf("i = %d  fd = %s\n", lexer->i, lexer->str);
			lexer = lexer->next;
		}
		cmd = cmd->next;
	}
}

int	check_sep(char **str, char c)
{
	if (c != 0)
		return (0);
	else if ((*(*str) == '>' || *(*str) == '<'))
	{
		if (*(*str + 1) == *(*str))
			return (0);
		return (1);
	}
	else if ((*(*str) == ' ' || *(*str) == '|' || *(*str) == ';'))
		return (1);
	else if ((*(*str + 1) == ' ' || *(*str + 1) == '|' || *(*str + 1) == '>' || *(*str + 1) == '<'|| *(*str + 1) == ';'))
		return (1);
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

int	check_redirection(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && (!token->next || !token->prev))
			return (-2);
		if ((token->type ==  APPEND || token->type == INPUT || token->type == TRUNC \
			|| token->type == heredoc) && (!token->next || token->next->type > ARG))
			return (-3);
		else if ((ft_strchr(token->str, '\"') == NULL && ft_strchr(token->str, '\'') == NULL) && \
				(ft_strnstr(token->str, ">>>", ft_strlen(token->str)) \
				||  ft_strnstr(token->str, "<<<", ft_strlen(token->str))))
			return (-4);
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_syntax(t_token *token)
{
	int	n;

	n = check_redirection(token);
	if (n != 0)
	{
		if (n == -2)
			printf("bash: syntax error near unexpected token `|'\n");
		else if (n == -3)
			printf("bash: syntax error near unexpected token `newline'\n");
		return (FAILURE);
	}
	return (SUCCESS);
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
				return (FAILURE);
			}
		}
		str++;
	}
	return (SUCCESS);
}

int	alloc_mem(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			c = *str;
		i++;
		if (check_sep(&str, c) != 0)
			break ;
		str++;
	}
	return (i);
}



int	ft_sep(t_token *token)
{
	if (token->type == TRUNC)
		return (1);
	else if (token->type == APPEND)
		return (1);
	else if (token->type == INPUT)
		return (1);
	else if (token->type == heredoc)
		return (1);
	else if (token->type == PIPE)
		return (2);
	return (0);
}

int	argv_len(t_token *token)
{
	int	count;

	count = 0;
	while (token && ft_sep(token) != 2)
	{
		while (token && ft_sep(token) == 0)
		{
			count++;
			token = token->next;
		}
		while (token && ft_sep(token) == 1)
			token = token->next->next;
	}
	return (count);
}



