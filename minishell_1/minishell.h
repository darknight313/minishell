/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:03:55 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:48:37 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <string.h>

#include "libft/libft.h"

#define SUCCESS 0
#define FAILURE -1

#define EMPTY 0
#define COMMAND 1
#define ARG 3
#define	APPEND 4 // >>
#define INPUT 5 // <
#define TRUNC 6 // >
#define heredoc 7 // <<
#define PIPE 8 // |


typedef struct s_token
{
	char	*str;
	int		type;
	struct	s_token *next;
	struct	s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char	*str;
	int		i;
	struct	s_lexer *next;
}	t_lexer;

typedef struct t_cmd
{
	char			**argv;
	t_lexer			*lexer;
	struct t_cmd	*next;
	struct t_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char	*value;
	struct	s_env *next;
	struct	s_env *prev;
}	t_env;


typedef struct s_tool
{
	char	*pwd;
	char	*oldpwd;
}	t_tool;


typedef struct s_obj
{
	t_token	*token;

	t_cmd	*cmd;
	t_env	*env;
	t_tool	tool;
	int		PID;
}	t_obj;

typedef struct s_bulding
{
	char	*str;
	int		(*function)(char **argv, t_obj *obj);
}	t_bulding;


// parsing
int		parsing(t_obj *obj, char *str);
t_token	*tokenize(char **str);
char	*get_token(char **str);
int		ft_syntax(t_token *token);
void	token_type(t_token **token);
void	expand(t_obj *obj);
char	*get_value(t_env *env, char *str);
int		check_equal(char *str);
t_cmd	*create_list(t_token *token);

//utils.c
void	append_token(t_token **token, char *str);
void	skip_space(char **str);
int		quotes(char *str);
int		alloc_mem(char *str);
int		check_sep(char **str, char c);
void	print_argv(t_cmd *cmd);
void	print_token(t_token *token);
int		check_equal(char *str);
void	append_token2(t_env **token, char *str);
int		ft_sep(t_token *token);
int		argv_len(t_token *token);
char	*advanced_strjoin(char *s1, char *s2);


// free static memory
void	free_argv(char **argv);
void	free_token(t_token **token);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);


//buildin
int		check_buildings(t_obj *obj, char **argv);
int		ft_echo(char **argv, t_obj *obj);
int		ft_pwd(char **argv, t_obj *obj);
int		ft_export(char **argv, t_obj *obj);
int		ft_unset(char **argv, t_obj *obj);
int		ft_env(char **argv, t_obj *obj);
int		ft_cd(char **argv, t_obj *obj);
void	append_env(char *str, t_env **env);
int		len(char **argv);

//execute
int		executor(t_obj *obj);
int		pipex_excutor(t_obj *obj, int count_cmds);
char	**ft_split_simple(char const *str, char charset);
int		set_redirections(t_cmd *cmd);
char	*check_full_path(char *path_elemt, char *cmd);
char	*get_full_path(char **env_path, char *cmd);

#endif
