/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:40 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 14:53:25 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("%d : %s\n", token->type, token->str);
		token = token->next;
	}
}

int	main(int args, char **argv, char **env)
{
	t_token	*token;
	int		id;

	token = NULL;
	id = fork();
	if (id == 0)
	{
		while (1)
		{
			char *str = readline("minishell -> ");
			if (parsing(&token, str, env) == 0)
			{
				free(str);
				free_stack(&token);
				break ;
			}
			// print_token(token);
			free(str);
			free_stack(&token);
		}
	}
	wait(NULL);
	return (0);
}
