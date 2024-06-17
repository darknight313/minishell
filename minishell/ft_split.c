/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:14:49 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/17 17:34:49 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c);
static void	free_split(char **mem, int size);
static int	word_len(char const *str, char c);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	int		word_length;
	char	**split_array;

	i = -1;
	word_count = count_words(s, c);
	split_array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split_array)
		return (split_array);
	while (++i < word_count)
	{
		word_length = word_len(s, c);
		split_array[i] = (char *)malloc(word_length + 1);
		if (!split_array[i])
		{
			free_split(split_array, i);
			return (0);
		}
		ft_strlcpy(*(split_array + i), s, word_length + 1);
		s += word_length;
	}
	split_array[i] = NULL;
	return (split_array);
}


static int	word_len(char const *str, char c)
{
	int		count;
	char	d;

	count = 0;
	d = 0;
	if (*str == '\'' || *str == '\"')
	{
		str++;
		return (1);
	}
	else if (*str == c || *str == '\'' || *str == '\"')
	{
		while (*str == c)
		{
			count++;
			str++;
		}
	}
	else
	{
		if (*str == '$')
		{
			count++;
			str++;
		}
		while (*str && *str != c && *str != '\'' && *str != '\"' && *str++ != '$')
			count++;
	}
	return (count);
}

static int	count_words(const char *str, char c)
{
	int		count;
	char	l;

	count = 0;
	l = 0;
	while (*str)
	{
		if (*str == c || *str == '\'' || *str == '\"')
		{
			while (*str == c)
				str++;
			if (*str == '\'' || *str == '\"')
				str++;
			count++;
		}
		else if (*str)
		{
			if (*str == '$')
				str++;
			while (*str && *str != c && *str != '\'' && *str != '\"' && *str != '$')
				str++;
			count++;
		}
	}
	return (count);
}

static void	free_split(char **result, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(result[i]);
		i++;
	}
	free(result);
}
