/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:21:24 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 18:49:03 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	*get_value(char **env, char *str)
{
	char	*new_str;
	char	*str_cpy;
	int		equal;
	int	i = 0;

	str_cpy = NULL;
	new_str = NULL;
	equal = 0;
	while (env[i])
	{
		str_cpy = NULL;
		equal = check_equal(env[i], '=');
		str_cpy = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		str_cpy[ft_strlen(env[i])] = '\0';
		str_cpy = ft_strncpy(str_cpy, env[i], equal);
		if ((ft_strncmp(str_cpy, str, ft_strlen(str_cpy))) == 0 && (ft_strncmp(str, str_cpy, ft_strlen(str)) == 0))
		{
			new_str = ft_strdup(env[i] + (equal + 1));
			break ;
		}
		i++;
	}
	return (new_str);
}

int	expand(t_token **token, char **env)
{
	t_token	*token_t;
	char	**argv;
	char	*val;
	char	*result;

	token_t = *token;
	argv = NULL;
	val = NULL;
	while (token_t)
	{
		if (ft_strchr(token_t->str, '$'))
		{
			argv = ft_split(token_t->str, ' ');
			int i = 0;
			while (argv[i])
			{
				if (ft_strchr(argv[i], '$'))
				{
					val = get_value(env, argv[i] + 1);
					argv[i] = ft_strdup(val);
				}
				i++;
			}
			i = 0;
			while (argv[i])
			{
				result = ft_strjoin(val, argv[i]);
				i++;
			}
			token_t->str = ft_strdup(result);
		}
		token_t = token_t->next;
	}
	return (1);
}
