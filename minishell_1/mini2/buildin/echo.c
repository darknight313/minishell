/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:10:13 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 12:00:47 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cat(char **argv)
{
	char	*str;
	int		i;
	int		new_line;

	i = 1;
	new_line = 0;
	str = NULL;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		new_line = !new_line;
		i++;
	}
	if (argv[i] == NULL)
		return (ft_strdup(""));
	while (argv[i])
	{
		str = ft_strjoin2(str, argv[i], 1);
		if (argv[i + 1])
			str = ft_strjoin2(str, " ", 1);
		i++;
	}
	if (!new_line)
		str = ft_strjoin2(str, "\n", 1);
	return (str);
}

int	ft_echo(char **argv, t_obj *obj)
{
	char	*str;

	(void)obj;
	str = ft_cat(argv);
	printf("%s", str);
	free(str);
	return (0);
}
