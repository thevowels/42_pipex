/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:10:11 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:11:39 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is an uppercase letter
 * 
 * Uses efficient arithmetic to test if the character falls within the
 * uppercase letter range 'A' to 'Z' by subtracting 'A' and checking
 * if the result is less than 26.
 * 
 * @param c The character to check (as int)
 * @return 1 if the character is uppercase, 0 otherwise
 * @note Efficient implementation using unsigned arithmetic
 */
int	ft_isupper(int c)
{
	return ((unsigned)c - 'A' < 26);
}
