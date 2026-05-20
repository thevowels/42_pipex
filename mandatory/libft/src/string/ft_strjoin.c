/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:45:09 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/25 03:12:38 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2)
				+ 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen((char *)s1));
	ft_memcpy(str + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	str[ft_strlen((char *)s1) + ft_strlen((char *)s2)] = 0;
	return (str);
}
