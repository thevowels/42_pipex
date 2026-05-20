/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:46:46 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:12:16 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief Converts a lowercase letter to uppercase
 *
 * Uses bitwise AND operation with ~32 to efficiently convert lowercase
 * letters to uppercase. The mask ~32 clears the 5th bit (position 32)
 * which distinguishes between uppercase and lowercase in ASCII encoding.
 *
 * @param c The character to convert (as int)
 * @return The uppercase equivalent if c is lowercase, otherwise c unchanged
 * @note Uses ft_islower() to check if conversion is needed
 * @note Efficient bitwise implementation: lowercase & ~32 = uppercase
 */
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c & ~32);
	return (c);
}
