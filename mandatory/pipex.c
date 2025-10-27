/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:39 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/27 12:26:27 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>

void	safe_open(int *fd, const char *pathname, int flags, mode_t mode)
{
	*fd = open(pathname, flags, mode);
	if (*fd == -1)
	{
		perror(pathname);
		exit(EXIT_FAILURE);
	}
}

void	first_process(t_env env)
{
	char	*cmd_path;
	char	**cmd_argv;
	int		file_fd;

	close(env.pipe_fd[0]);
	safe_dup2(env.pipe_fd[1], STDOUT_FILENO, 1);
	safe_close(env.pipe_fd[1], 1);
	safe_open(&file_fd, env.argv[1], O_RDONLY, 0);
	safe_dup2(file_fd, STDIN_FILENO, 1);
	safe_close(file_fd, 1);
	cmd_argv = ft_split(env.argv[2], ' ');
	cmd_path = get_exe_path(env.all_path, cmd_argv, STDOUT_FILENO);
	execve(cmd_path, cmd_argv, env.envp);
	perror("Error on first child");
	exit(EXIT_FAILURE);
}

void	last_process(t_env env)
{
	char	*cmd_path;
	char	**cmd_argv;
	int		outfile_fd;

	safe_close(env.pipe_fd[1], 1);
	safe_dup2(env.pipe_fd[0], STDIN_FILENO, 1);
	safe_close(env.pipe_fd[0], 1);
	safe_open(&outfile_fd, env.argv[4], O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	safe_dup2(outfile_fd, STDOUT_FILENO, 1);
	safe_close(outfile_fd, 1);
	cmd_argv = ft_split(env.argv[3], ' ');
	cmd_path = get_exe_path(env.all_path, cmd_argv, STDIN_FILENO);
	execve(cmd_path, cmd_argv, env.envp);
	exit(EXIT_FAILURE);
}

void	init_env(t_env *env, int argc, char **argv, char **envp)
{
	if (argc != 5)
		exit(EXIT_FAILURE);
	env->argc = argc;
	env->argv = argv;
	env->envp = envp;
	env->all_path = get_all_path(envp);
	if (pipe(env->pipe_fd) == -1)
		perror_exit("pipex: Error while creating pipe");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	init_env(&env, argc, argv, envp);
	env.childs[0] = fork();
	if (env.childs[0] == -1)
		perror_exit("pipex: Error while creating first child");
	if (env.childs[0] == 0)
		first_process(env);
	env.childs[1] = fork();
	if (env.childs[1] == -1)
		perror_exit("pipex: Error while creating last child");
	if (env.childs[1] == 0)
		last_process(env);
	safe_close(env.pipe_fd[0], 1);
	safe_close(env.pipe_fd[1], 1);
	safe_waitpid(env.childs[1], &(env.last_status), 0);
	while (wait(NULL) != -1)
		continue ;
	return (env.last_status >> 8);
}
