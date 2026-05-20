/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isodd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:39:21 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/11 08:45:01 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if an integer is odd
 * 
 * Uses bitwise AND operation to efficiently test if the least significant
 * bit is 1 (indicating an odd number).
 * 
 * @param i The integer to check
 * @return 1 if the number is odd, 0 if even
 * @note Efficient implementation using bitwise operation
 */
int	ft_isodd(int i)
{
	return (i & 0x1);
}
