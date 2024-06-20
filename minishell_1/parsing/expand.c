/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:21:24 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:38:43 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(t_env *env, char *str)
{
	char	*value;
	int		equal;

	equal = 0;
	value = NULL;
	if (*str == '\0')
		value = ft_strdup("$");
	if (*str == '$')
		value = ft_strdup(ft_itoa(getpid()));
	while (env && value == NULL)
	{
		equal = check_equal(env->value);
		if ((ft_strncmp(str, env->value, ft_strlen(str)) == 0 \
			&& ft_strncmp(env->value, str, equal) == 0))
			value = ft_strdup(ft_strchr(env->value, '=') + 1);
		env = env->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

char	*single_quotes(char **argv, int *i)
{
	char	*str;

	str = NULL;
	(*i)++;
	while (argv[*i] && ft_strcmp(argv[*i], "\'"))
	{
		str = ft_strjoin(str, argv[*i]);
		(*i)++;
	}
	(*i)++;
	return (str);
}

char	*double_quotes(t_env *env, char **argv, int *i)
{
	char	*str;
	char	*value;

	value = NULL;
	str = NULL;
	(*i)++;
	while (argv[*i] && ft_strcmp(argv[*i], "\""))
	{
		if (ft_strchr(argv[*i], '$'))
		{
			value = get_value(env, argv[*i] + 1);
			str = ft_strjoin(str, value);
			free(value);
		}
		else
			str = ft_strjoin(str, argv[*i]);
		(*i)++;
	}
	(*i)++;
	return (str);
}

char	*no_quotes(t_env *env, char **argv, int *i)
{
	char	*str;
	char	*value;

	str = NULL;
	value = NULL;
	while (argv[*i] && ft_strcmp(argv[*i], "\"") && ft_strcmp(argv[*i], "\'"))
	{
		if (ft_strchr(argv[*i], '$'))
		{
			value = get_value(env, argv[*i] + 1);
			str = ft_strjoin(str, value);
			free(value);
		}
		else
			str = ft_strjoin(str, argv[*i]);
		(*i)++;
	}
	return (str);
}

void	expand(t_obj *obj)
{
	t_token	*token;
	char	**argv;
	int		i;

	token = obj->token;
	while (token)
	{
		i = 0;
		argv = ft_split(token->str, ' ');
		free(token->str);
		token->str = NULL;
		while (argv[i])
		{
			if (ft_strcmp(argv[i], "\'") == 0)
				token->str = advanced_strjoin(token->str, single_quotes(argv, &i));
			else if (ft_strcmp(argv[i], "\"") == 0)
				token->str = advanced_strjoin(token->str, double_quotes(obj->env, argv, &i));
			else
				token->str = advanced_strjoin(token->str, no_quotes(obj->env, argv, &i));
		}
		free_argv(argv);
		token = token->next;
	}
}
