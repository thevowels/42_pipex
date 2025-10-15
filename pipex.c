/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:01:12 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/16 01:15:39 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_startswith(char *str, char *start)
{
	while(*str && *start)
	{
		if(*str != *start)
			return (0);
		str++;
		start++;
	}
	if(*start)
		return (0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	while(*envp)
	{
		if(ft_startswith(*envp,"PATH"))
		{
			printf("%s\n", (*envp) + 5);
		}
		envp++;
	}
	return (0);
}