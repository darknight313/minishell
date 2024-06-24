/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:28:40 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/23 22:44:06 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pp_check_full_path(char *path_elemt, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*full_path;

	if (path_elemt == NULL || cmd == NULL)
		return (NULL);
	path_len = ft_strlen(path_elemt);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(sizeof(char) * (path_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path_elemt, path_len + 1);
	ft_strlcpy(full_path + path_len, "/", 2);
	ft_strlcpy(full_path + path_len + 1, cmd, cmd_len + 1);
	return (full_path);
}

char	*pp_get_path_env(t_obj *obj, char *cmd)
{
	t_env	*env_temp;
	char	**path_array;
	char	*cmd_path;
	int		i;

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
	i = 0;
	while (path_array[i])
	{
		cmd_path = pp_check_full_path(path_array[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
		free (cmd_path);
	}
	return (NULL);
}

void	child_porcess(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2], char **env)
{
	char	*full_path;

	if (curr_cmd->next != NULL)
	{
		close(fd_pipe[0]);
		dup2_error(obj, dup2(fd_pipe[1], STDOUT_FILENO));
		close(fd_pipe[1]);
	}
	set_redirections(curr_cmd);
	if (curr_cmd->argv[0] && check_buildings(curr_cmd->argv))
		run_buildings(obj, curr_cmd->argv);
	else
	{
		if (access(curr_cmd->argv[0], X_OK) == 0)
			full_path = curr_cmd->argv[0];
		else
		{
			full_path = pp_get_path_env(obj, curr_cmd->argv[0]);
			if (full_path == NULL)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		execve(full_path, curr_cmd->argv, env);
		perror("execve");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	parent_process(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2])
{
	if (curr_cmd->next == NULL)
		close(STDIN_FILENO);
	else
	{
		close(fd_pipe[1]);
		dup2_error(obj, dup2(fd_pipe[0], STDIN_FILENO));
		close(fd_pipe[0]);
	}
}
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
void	execution_loop(t_obj *obj, int main_fd_in, int main_fd_out, char **env)
{
	t_cmd	*curr_cmd;
	int		pid;
	int		fd_pipe[2];

	curr_cmd = obj->cmd;
	pid = 0;
	obj->pid = malloc(sizeof(int) * count_cmds(obj));
	while (curr_cmd)
	{
		pipe_error(obj, pipe(fd_pipe));
		obj->pid[pid] = fork_erro(obj, fork());
		if (obj->pid[pid] == 0)
		{
			close(main_fd_in);
			close(main_fd_out);
			child_porcess(obj, curr_cmd, fd_pipe, env);
		}
		else
		{
			parent_process(obj, curr_cmd, fd_pipe);
			curr_cmd = curr_cmd->next;
			pid++;
		}
	}
}
void	ft_wait_all(t_obj *obj, int *status)
{
	int	i;
	int	cmd_count;

	i = -1;
	cmd_count = count_cmds(obj);
	while (++i < cmd_count)
		waitpid(obj->pid[i], status, 0);
	free(obj->pid);
}

int	executor(t_obj *obj, char **env)
{
	int		status;
	t_cmd	*curr_cmd;
	int		std_in;
	int		std_out;

	std_in = dup_error(obj, dup(STDIN_FILENO));
	std_out = dup_error(obj, dup(STDOUT_FILENO));
	curr_cmd = obj->cmd;
	ft_heredoc(obj);
	if (curr_cmd && curr_cmd->argv[0] && check_buildings(curr_cmd->argv) \
		&& curr_cmd->next == NULL)
	{
		set_redirections(curr_cmd);
		run_buildings(obj, curr_cmd->argv);
	}
	else
	{
		execution_loop(obj, std_in, std_out, env);
		ft_wait_all(obj, &status);
	}
	dup2_error(obj, dup2(std_in, STDIN_FILENO));
	close(std_in);
	dup2_error(obj, dup2(std_out, STDOUT_FILENO));
	close(std_out);
	return (1);
}
