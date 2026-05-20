/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 03:44:02 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/26 04:08:23 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <errno.h>

/**
 * @brief Writes a string to a file descriptor
 * 
 * This function writes the string pointed to by str to the file descriptor fd.
 * It calculates the length of the string and writes the entire string in one
 * write() system call.
 * 
 * @param str Pointer to the null-terminated string to write. If NULL, the
 *            function sets errno to EFAULT (14) and returns -1.
 * @param fd  File descriptor where the string should be written
 * 
 * @return The number of bytes written on success, or -1 on error.
 *         On error, errno is set appropriately:
 *         - EFAULT (14): str is NULL
 *         - Other errno values may be set by the write() system call
 * 
 * @note The function does not add a newline character at the end
 * @note The string must be null-terminated
 * 
 * @see write(2), ft_putstr(), ft_strlen()
 */
size_t	ft_putstr_fd(char *str, int fd)
{
	size_t	str_len;

	str_len = 0;
	if (!str)
	{
		errno = 14;
		return (-1);
	}
	while (str[str_len])
		str_len++;
	return (write(fd, str, str_len));
}
