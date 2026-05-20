/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:55:54 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/30 16:13:23 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Copies memory area with optimized word-aligned operations
 *
 * Copies n bytes from memory area src to memory area dest. The memory
 * areas must not overlap. Uses an optimized approach by copying 8-byte
 * chunks (unsigned long long) first, then copying remaining bytes
 * one by one for better performance on aligned data.
 *
 * @param dest Pointer to the destination memory area
 * @param src Pointer to the source memory area
 * @param n Number of bytes to copy
 * @return Pointer to dest
 * @note Memory areas must not overlap - use ft_memmove for overlapping areas
 * @note Optimized implementation using 8-byte word copying when possible
 * @warning Does not handle NULL pointers
	- undefined behavior if either parameter is NULL
 */

static void	*ft_rest(void *dest, const void *src, size_t n)
{
	unsigned char	*char_dest;
	unsigned char	*char_src;
	size_t			gl;
	size_t			i;

	gl = (n / sizeof(unsigned long long));
	i = gl * sizeof(unsigned long long);
	char_dest = (unsigned char *)dest;
	char_src = (unsigned char *)src;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				gl;
	size_t				i;
	unsigned long long	*tmp_dest;
	unsigned long long	*tmp_src;

	i = 0;
	gl = (n / sizeof(unsigned long long));
	tmp_dest = (unsigned long long *)dest;
	tmp_src = (unsigned long long *)src;
	while (i < gl)
	{
		tmp_dest[i] = tmp_src[i];
		i++;
	}
	return (ft_rest(dest, src, n));
}
