/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:54:24 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/18 17:36:59 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_obj *obj)
{
	t_cmd	*cmd_temp;
	int		count;

	count = 0;
	cmd_temp = obj->cmd;
	while (cmd_temp)
	{
		count++;
		cmd_temp = cmd_temp->next;
	}
	return (count);
}

char	**get_path_env(t_obj *obj)
{
	t_env	*env_temp;
	char	**path_array;

	env_temp = obj->env;
	path_array = NULL;
	while (env_temp && !path_array)
	{
		if (ft_strncmp(env_temp->value, "PATH=", 5) == 0)
			path_array = ft_split_simple(env_temp->value + 5, ':');
		env_temp = env_temp->next;
	}
	if (!path_array)
	{
		printf("couldns find path variables");
		exit (-1);
	}
	return (path_array);
}


void	single_cmd(t_cmd *cmd, t_obj *obj)
{
	pid_t	pid;
	int		status;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (check_buildings(obj, cmd->argv))
			return ;
		else
			execvp(cmd->argv[0], cmd->argv);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}


void pipex_executor(t_obj *obj, int cmd_count)
{
	int i;
	int pipe_fds[2];
	t_cmd *curr_cmd;
	int fd_in = STDIN_FILENO;

	curr_cmd = obj->cmd;
	for (i = 0; i < cmd_count - 1; i++)
	{
		set_redirections(curr_cmd);

		if (pipe(pipe_fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		if (fork() == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			if (curr_cmd->next != NULL)
			{
				dup2(pipe_fds[1], STDOUT_FILENO);
			}
			close(pipe_fds[0]);
			if (check_buildings(obj, curr_cmd->argv))
				return ;
			else
				execvp(curr_cmd->argv[0], curr_cmd->argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(pipe_fds[1]);
			fd_in = pipe_fds[0];
			curr_cmd = curr_cmd->next;
		}
	}
	if (fork() == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		execvp(curr_cmd->argv[0], curr_cmd->argv);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

int	executor(t_obj *obj)
{
	int		cmd_count;
	t_cmd	*curr_cmd;

	curr_cmd = obj->cmd;
	cmd_count = count_cmds(obj);
	if (cmd_count == 1)
	{
		set_redirections(curr_cmd);
		single_cmd(curr_cmd, obj);
	}
	else
	{
	    pipex_executor(obj, cmd_count);
	}

    return (0);
}
