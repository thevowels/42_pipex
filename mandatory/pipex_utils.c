/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 06:28:13 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/26 13:25:55 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	set_env(t_env *env, int argc, char **argv, char **envp)
{
	env->argc = argc;
	env->argv = argv;
	env->envp = envp;
}

void	perror_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	safe_dup2(int old, int new, int exit_on_fail)
{
	if (dup2(old, new) == -1)
	{
		perror("pipex: Error while duplicating fd");
		if (exit_on_fail)
		{
			exit(EXIT_FAILURE);
		}
	}
}

void	safe_close(int fd, int exit_on_fail)
{
	if (close(fd) == -1)
	{
		perror("pipex: Error while closing fd");
		if (exit_on_fail)
		{
			exit(EXIT_FAILURE);
		}
	}
}

void	safe_waitpid(pid_t pid, int *status, int options)
{
	if (waitpid(pid, status, options) == -1)
	{
		perror("pipex:Error while waiting process");
	}
}
