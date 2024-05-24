/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:14:05 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 18:49:13 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		parsing(t_token **token, char *str, char **env);
void	tokenize(t_token **token, char **str);
char	*get_token(char **str);
void	token_type(t_token **token);

int	parsing(t_token **token, char *str, char **env)
{
	t_cmd	*command;

	command = NULL;
	if (str == NULL)
		return (1);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (0);
	if (quotes(str))
		return (1);
	tokenize(token, &str);
	expand(token, env);
	while (*token)
	{
		printf("%s\n", (*token)->str);
		*token = (*token)->next;
	}
	command = create_list(*token);
	return (1);
}

void	tokenize(t_token **token, char **str)
{
	char	*line;

	line = NULL;
	if (*str == NULL)
		return ;
	while (*(*str))
	{
		skip_space(str);
		line = get_token(str);
		append_token(token, line);
		free(line);
		token_type(token);
		if (*(*str) == '\0')
			break ;
		(*str)++;
	}
}

char	*get_token(char **str)
{
	char	*line;
	int		i;
	char	c;

	i = 0;
	c  = 0;
	if (*str == NULL)
		return (NULL);
	line = (char *)malloc(alloc_mem(*str) + 1);
	if (!line)
		return (NULL);
	if (*(*str) == '\'' || *(*str) == '\"')
	{
		c = *(*str);
		(*str)++;
	}
	while (*(*str) && *(*str) != c)
	{
		line[i] = *(*str);
		i++;
		if (check_sep(*str) == 2 && !c)
		{
			(*str)++;
			line[i] = *(*str);
			i++;
			break ;
		}
		if ((check_sep(*str) == 1 || check_sep(*str) == 3) && !c)
			break;
		else if (check_sep(*str + 1) != 0 && !c)
			break ;
		(*str)++;
	}
	line[i] = '\0';
	return (line);
}

void	token_type(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = *token;
	while (token_tmp->next)
		token_tmp = token_tmp->next;
	if (ft_strncmp(token_tmp->str, "", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = EMPTY;
	else if (ft_strncmp(token_tmp->str, "|", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = PIPE;
	else if (ft_strncmp(token_tmp->str, ">", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = TRUNC;
	else if (ft_strncmp(token_tmp->str, "<", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = INPUT;
	else if (ft_strncmp(token_tmp->str, ">>", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = APPEND;
	else if (ft_strncmp(token_tmp->str, "<<", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = heredoc;
	else if (ft_strncmp(token_tmp->str, ";", ft_strlen(token_tmp->str)) == 0)
		token_tmp->type = END;
	else if (token_tmp->prev == NULL || token_tmp->prev->type == PIPE || token_tmp->prev->type == END)
		token_tmp->type = COMMAND;
	else
		token_tmp->type = ARG;
}









