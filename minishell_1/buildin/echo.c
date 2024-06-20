/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:10:13 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/20 14:36:41 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_leak(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

char	*ft_cat(char **argv)
{
	char	*str;
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	str = NULL;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		new_line = !new_line;
		i++;
	}
	while (argv[i])
	{
		str = ft_handle_leak(str, argv[i]);
		if (argv[i + 1])
			str = ft_handle_leak(str, " ");
		i++;
	}
	if (new_line)
		str = ft_handle_leak(str, "\n");
	return (str);
}

int	ft_echo(char **argv, t_obj *obj)
{
	char	*str;
	int		new_line;

	(void)obj;
	new_line = 1;
	str = ft_cat(argv);
	printf("%s", str);
	free(str);
	return (0);
}
