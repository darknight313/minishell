/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:15:58 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/18 17:10:34 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_env(char *str, t_env **env)
{
	int		i;
	t_env	*env_t;

	env_t = *env;
	i = 0;
	int equal2 = check_equal(str);
	if (equal2 == 0)
		return ;
	else if (equal2 == -1)
	{
		printf("export: not valid in this context: %s\n", str);
		return ;
	}
	while (env_t)
	{
		int equal = check_equal(env_t->value);
		if ((ft_strncmp(str, env_t->value, equal2) == 0 && ft_strncmp(env_t->value, str, equal) == 0))
		{
			free(env_t->value);
			env_t->value = NULL;
			env_t->value = ft_strdup(str);
			return ;
		}
		env_t = env_t->next;
	}
	append_token2(env, str);
	return ;
}

int	ft_export(char **argv, t_obj *obj)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		append_env(argv[i], &obj->env);
		i++;
	}
	return (0);
}
