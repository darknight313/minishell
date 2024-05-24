/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:03:18 by ashirzad          #+#    #+#             */
/*   Updated: 2024/05/24 18:35:02 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int args, char **argv, char **env)
{
	char	*str;

	str = get_value(env, "MY_VA");
	printf("%s\n", str);
}
