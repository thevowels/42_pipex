/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iseven.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:29:20 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/11 08:42:18 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if an integer is even
 * 
 * Uses bitwise AND operation to efficiently test if the least significant
 * bit is 0 (indicating an even number).
 * 
 * @param i The integer to check
 * @return 1 if the number is even, 0 if odd
 * @note Efficient implementation using bitwise operation
 */
int	ft_iseven(int i)
{
	return (!(i & 0x1));
}
