/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:01:12 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/16 01:42:55 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

int		ft_strexact(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(*s1 && *s2)
	{
		if(*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if(*s1 || *s2)
		return (0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{

	if(argc < 4)
	{
		ft_putstr("Usage: ./pipex file1 cmd1 cmd2 ... file2 ");
		ft_putstr("|| ./pippex here_doc LIMITER cmd cmd1 ... file \n");
		return (1);
	}
	if(ft_strexact(argv[1], "here_doc"))
	{
		ft_putstr("Heredoc style\n");
		return(0);
	}
	else
	{
		ft_putstr("Normal one\n");
		return (0);
	}

	return (0);
}