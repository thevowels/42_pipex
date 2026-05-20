/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:34 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 01:13:01 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is a whitespace character
 * 
 * Tests if the character is one of the standard whitespace characters:
 * - Tab (\t) = 9
 * - Newline (\n) = 10
 * - Vertical tab (\v) = 11
 * - Form feed (\f) = 12
 * - Carriage return (\r) = 13
 * - Space = 32
 * 
 * @param c The character to check (as int)
 * @return 1 if the character is whitespace, 0 otherwise
 * @note Covers all standard whitespace characters defined in C
 */
int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
