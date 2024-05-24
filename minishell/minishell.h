/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:03:55 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 18:34:15 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <string.h>

#define EMPTY 0
#define COMMAND 1
#define ARG 3
#define	APPEND 4
#define INPUT 5
#define TRUNC 6
#define heredoc 7
#define PIPE 8
#define END 9

typedef struct t_token
{
	char	*str;
	int		type;
	struct	t_token *next;
	struct	t_token	*prev;
}	t_token;

typedef struct t_cmd
{
	char	**argv;
	int		index;
	struct	t_cmd *next;
}	t_cmd;

//tokenize
int		parsing(t_token **token, char *str, char **env);
void	tokenize(t_token **token, char **str);
char	*get_token(char **str);
void	token_type(t_token **token);

//utils.c
void	free_stack(t_token **stack);
void	append_token(t_token **token, char *str);
void	skip_space(char **str);
int		quotes(char *str);
int		alloc_mem(char *str);
int		check_sep(char *str);
int		check(char *str, int c);

//create_list
t_cmd	*create_list(t_token *token);

//expand
int		expand(t_token **token, char **env);

#endif
