/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:28:43 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/18 14:06:30 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delete_var(char *str, t_env **env)
{
	int		i;
	int		equal2;
	t_env	*env_t;
	t_env	*tmp;

	env_t = *env;
	i = 0;
	equal2 = check_equal(str);
	if (equal2 > 0)
	{
		printf("unset: %s: invalid parameter name\n", str);
		return (-1);
	}
	else if (equal2 == -1)
	{
		printf("unset: not valid in this context: %s\n", str);
		return (-1);
	}
	while (env_t)
	{
		int equal = check_equal(env_t->value);
		if ((ft_strncmp(str, env_t->value, ft_strlen(str)) == 0 && ft_strncmp(env_t->value, str, equal) == 0))
		{
			tmp = env_t;
			if (env_t->prev == NULL)
			{
				*env = env_t->next;
				(*env)->prev = NULL;
			}
			else if (env_t->next == NULL)
				env_t->prev->next = NULL;
			else if (env_t->prev && env_t->next)
				env_t->prev->next = env_t->next;
			free(tmp);
			break ;
		}
		env_t = env_t->next;
	}
	return (0);
}

int	ft_unset(char **argv, t_obj *obj)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (delete_var(argv[i], &obj->env) != 0)
			return (-1);
		i++;
	}
	return (0);
}
