/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:37:28 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:12:02 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Converts an uppercase letter to lowercase
 *
 * Uses bitwise OR operation with 32 to efficiently convert uppercase
 * letters to lowercase. The 5th bit (32 in decimal) distinguishes
 * between uppercase and lowercase in ASCII encoding.
 *
 * @param c The character to convert (as int)
 * @return The lowercase equivalent if c is uppercase, otherwise c unchanged
 * @note Uses ft_isupper() to check if conversion is needed
 * @note Efficient bitwise implementation: uppercase | 32 = lowercase
 */
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c | 32);
	return (c);
}
