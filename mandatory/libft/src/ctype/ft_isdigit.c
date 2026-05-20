/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:06:07 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:11:25 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is a decimal digit
 * 
 * Uses bitwise operations to efficiently test if the character is a digit
 * from '0' to '9' by subtracting '0' and checking if the result is less than 10.
 * 
 * @param i The character to check (as int)
 * @return 1 if the character is a digit, 0 otherwise
 * @note Efficient implementation using unsigned arithmetic
 */
int	ft_isdigit(int i)
{
	return ((unsigned)i - '0' < 10);
}
