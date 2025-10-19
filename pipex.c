/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 03:37:52 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/20 04:04:25 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void ft_putstr_fd(char *str, int fd)
{
	int	i;
	i = 0;
	while(str[i])
	{
		i++;
	}
	write(fd,str,i);
}


// Fail the fork and set the error number accordingly
// pid_t test_fork(void) {
//     errno = EAGAIN;   // or ENOMEM, EINVAL, whatever you want to test
//     return -1;
// }

//Fail the pipe and set errno
// int test_pipe(int fd[2])
// {
// 	errno = ENFILE;
// 	return -1;
// }

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t pid[argc];
	int c_status[argc];

	if(argc == 5)
	{
		if(pipe(fd) == -1)
		{
			perror("Error while Creating Pipe");
			exit(EXIT_FAILURE);
		}
		pid[0] = fork();
		if(pid[0] == 0)
		{
			//Child
		}
		else if(pid[0] == -1)
		{
			//Error while forking for child 1
			perror("Error while Forking");
			exit(EXIT_FAILURE);
		}
		pid[1] = fork();
		if(pid[1] == 0)
		{
			//Child

		}
		else if(pid[1] == -1)
		{
			//Error while creating child 2
			perror("Error while Forking");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		errno = EINVAL;
		perror("Bad Arguments");
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(EXIT_FAILURE);
	}
	
	return (0);
}