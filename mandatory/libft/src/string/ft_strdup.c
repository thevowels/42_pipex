/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:12:24 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/30 16:20:38 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	n;
	char	*res;

	n = ft_strlen(str);
	res = (char *) malloc((sizeof(char) * (n + 1)));
	ft_memcpy(res, str, n);
	res[n] = 0;
	return (res);
}
