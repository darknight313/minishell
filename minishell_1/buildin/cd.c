/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:59 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/17 14:49:53 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	update_env(t_obj *obj)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strjoin("PWD=", obj->tool.pwd);
	oldpwd = ft_strjoin("OLDPWD=", obj->tool.oldpwd);
	append_env(pwd, &obj->env);
	append_env(oldpwd, &obj->env);
	free(pwd);
	free(oldpwd);
}

int	ft_cd(char **argv, t_obj *obj)
{
	char	*tmp;
	int		i;

	i = 1;
	if (len(argv) > 2)
	{
		printf("cd: no such file or directory: %s\n", argv[1]);
		return (-1);
	}
	else if (len(argv) == 1)
		return (0);
	if (ft_strcmp(argv[1], "-") == 0)
	{
		if (chdir(obj->tool.oldpwd) != 0)
		{
			printf("cd: no such file or directory: %s\n", obj->tool.oldpwd);
			return (-1);
		}
		tmp = ft_strdup(obj->tool.oldpwd);
		free(obj->tool.oldpwd);
		obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
		free(obj->tool.pwd);
		obj->tool.pwd = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			printf("cd: no such file or directory: %s\n", argv[1]);
			return (-1);
		}
		free(obj->tool.oldpwd);
		obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
		free(obj->tool.pwd);
		obj->tool.pwd = ft_strdup(argv[1]);
	}
	update_env(obj);
	return (0);
}
