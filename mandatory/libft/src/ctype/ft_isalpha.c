/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 07:41:42 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/11 08:45:01 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is alphabetic
 * 
 * Uses bitwise operations to efficiently test if the character is a letter
 * (either uppercase or lowercase) by converting to lowercase and checking
 * if it falls within the 'a' to 'z' range.
 * 
 * @param c The character to check (as int)
 * @return 1 if the character is alphabetic, 0 otherwise
 * @note Efficient implementation using bitwise operation
 */
int	ft_isalpha(int c)
{
	return (((unsigned)c | 32) - 'a' < 26);
}
