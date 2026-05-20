/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:09:39 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:11:31 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is a lowercase letter
 * 
 * Uses efficient arithmetic to test if the character falls within the
 * lowercase letter range 'a' to 'z' by subtracting 'a' and checking
 * if the result is less than 26.
 * 
 * @param c The character to check (as int)
 * @return 1 if the character is lowercase, 0 otherwise
 * @note Efficient implementation using unsigned arithmetic
 */
int	ft_islower(int c)
{
	return ((unsigned)c - 'a' < 26);
}
