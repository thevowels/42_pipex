/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:10:20 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/21 05:01:28 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a string starts with a given prefix
 * 
 * Compares the beginning of the main string with the prefix string
 * character by character. Returns true if the main string starts
 * with the entire prefix string, false otherwise.
 * 
 * @param str The main string to check
 * @param start The prefix string to search for at the beginning
 * @return 1 if str starts with start, 0 otherwise
 * @note Returns 0 if either parameter is NULL
 * @note Empty prefix returns 1 (every string starts with empty string)
 * @note Case-sensitive comparison
 */

int	ft_startswith(char *str, char *start)
{
	if (!str || !start)
	{
		return (-1);
	}
	while (*str && *start)
	{
		if (*str != *start)
			return (0);
		str++;
		start++;
	}
	if (*start)
		return (0);
	return (1);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *str = "PATH=/bin:/usr/bin";
// 	char *start = "PATH=";

// 	printf("%i\n", ft_startswith(NULL,NULL));
// 	printf("%i\n", ft_startswith(NULL,start));
// 	printf("%i\n", ft_startswith(str,NULL));
// 	printf("%i\n", ft_startswith("abc",start));
// 	printf("%i\n", ft_startswith(str,start));
// }