/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:35:16 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/18 17:10:01 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **argv, t_obj *obj)
{
	char	path[200];

	(void)obj;
	(void)argv;
	if (getcwd(path, 200))
	{
		printf("%s\n", path);
		return (0);
	}
	return (-1);
}
