/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:06:14 by aphyo-ht          #+#    #+#             */
/*   Updated: 2026/04/18 11:19:48 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*p1 = (const unsigned char *)s1;
	const unsigned char	*p2 = (const unsigned char *)s2;

	if (n == 0)
		return (0);
	while (*p1 && *p2 && n > 0)
	{
		if (*p1 != *p2)
			break ;
		n--;
		p1++;
		p2++;
	}
	if (n == 0)
		return (0);
	return (*p1 - *p2);
}
