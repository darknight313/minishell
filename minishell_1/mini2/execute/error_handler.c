/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 02:27:28 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/22 23:44:19 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_error(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("pipe error");
		obj->exit_code = 1;
		exit(1);
	}
}

int	fork_erro(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("fork error");
		obj->exit_code = 1;
		exit(1);
	}
	return (pid);
}

void	dup2_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup2 error");
		obj->exit_code = 1;
		exit(1);
	}
}


int	dup_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup error");
		obj->exit_code = 1;
		exit(1);
	}
	return (dup);
}
