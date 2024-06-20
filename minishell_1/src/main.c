/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:40 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:47:59 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_obj(t_obj *obj)
{
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
}

void	init_env(t_obj *obj, char **env)
{
	while (*env)
	{
		append_token2(&obj->env, *env);
		env++;
	}
}

void	init_tool(t_obj *obj)
{
	char	pwd[200];

	getcwd(pwd, 200);
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
}

int	main(int args, char **argv, char **env)
{
	(void)args;
	(void)argv;
	char	*str;
	t_obj	obj;

	init_obj(&obj);
	init_env(&obj, env);
	init_tool(&obj);
	obj.PID = fork();
	if (obj.PID == 0)
	{
		while (1)
		{
			str = readline("minishell -> ");
			parsing(&obj, str);
			free(str);
			// print_argv(obj.cmd);
			// if (executor(&obj) == -1)
			// {
			// 	printf("stop!\n");
			// 	free_cmd(&obj.cmd);
			// 	break ;
			// }
			free_cmd(&obj.cmd);
			free_env(&obj.env);
			free(obj.tool.oldpwd);
			free(obj.tool.pwd);
		}
	}
	wait(0);
	return (0);
}
