/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:08:49 by aphyo-ht          #+#    #+#             */
/*   Updated: 2026/04/18 11:26:46 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static void	do_split(char **result, char *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			k = 0;
			while (str[i + k] && str[i + k] != c)
				k++;
			result[j++] = ft_substr(str, i, k);
			i += k;
		}
	}
	result[j] = NULL;
}

char	**ft_split(char *str, char c)
{
	char	**result;

	if (!str)
		return (NULL);
	result = (char **)malloc((ft_count_words(str, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	do_split(result, str, c);
	return (result);
}
