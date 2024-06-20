/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buldins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:51:29 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/18 17:36:38 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_inisialisation_of_format(t_bulding g_format_specifiers[])
{
	g_format_specifiers[0] = (t_bulding){"cd", ft_cd};
	g_format_specifiers[1] = (t_bulding){"echo", ft_echo};
	g_format_specifiers[2] = (t_bulding){"export", ft_export};
	g_format_specifiers[3] = (t_bulding){"unset", ft_unset};
	g_format_specifiers[4] = (t_bulding){"pwd", ft_pwd};
	g_format_specifiers[5] = (t_bulding){"env", ft_env};
	// g_format_specifiers[6] = (t_bulding){'exit', ft_exit};
}


int	check_buildings(t_obj *obj, char **argv)
{
	t_bulding	buldings[6];
	int			i;

	ft_inisialisation_of_format(buldings);
	i = 0;
	while (i < 6)
	{
		if (ft_strcmp( buldings[i].str, argv[0]) == 0)
		{
			buldings[i].function(argv, obj);
			return (1);
		}
		i++;
	}
	return (0);
}