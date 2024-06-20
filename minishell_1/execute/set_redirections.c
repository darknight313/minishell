/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:13:39 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/17 14:20:25 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_red_input(t_lexer *red)
{
	int		fd;

	fd = open(red->str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell Err, infile, No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Error: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	set_red_append(t_lexer *red)
{
	int	fd;

	fd = open(red->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell Err, outfile\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Err: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	set_red_trunc(t_lexer *red)
{
	int	fd;

	fd = open(red->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell Err, outfile\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Err: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	set_redirections(t_cmd *cmd)
{
	t_lexer	*red_temp;

	red_temp = cmd->lexer;
	while (red_temp)
	{
		if (red_temp->i == INPUT)
		{
			if (set_red_input(red_temp) == EXIT_FAILURE)
				exit (-1);
		}
		if (red_temp->i == TRUNC)
		{
			if (set_red_trunc(red_temp) == EXIT_FAILURE)
				exit (-1);
		}
		if (red_temp->i == APPEND)
		{
			if (set_red_append(red_temp) == EXIT_FAILURE)
				exit (-1);
		}
		red_temp = red_temp->next;
	}
	return (0);
}
