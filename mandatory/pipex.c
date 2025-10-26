/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:39 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/26 11:58:12 by aphyo-ht         ###   ########.fr       */
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

void	first_process(t_env env, int *pipe_fd)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	*all_path;
	int		file_fd;

	close(pipe_fd[0]);
	all_path = get_all_path(env.envp);
	cmd_argv = ft_split(env.argv[2], ' ');
	cmd_path = get_exe_path(all_path, cmd_argv[0]);
	safe_open(&file_fd, env.argv[1], O_RDONLY, 0);
	safe_dup2(file_fd, STDIN_FILENO);
	safe_close(file_fd);
	safe_dup2(pipe_fd[1], STDOUT_FILENO);
	safe_close(pipe_fd[1]);
	execve(cmd_path, cmd_argv, env.envp);
	perror("Error on first child");
	exit(EXIT_FAILURE);
}

void	second_process(t_env env, int *pipe_fd)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	*all_path;
	int		outfile_fd;

	safe_open(&outfile_fd, env.argv[4], O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	all_path = get_all_path(env.envp);
	cmd_argv = ft_split(env.argv[3], ' ');
	cmd_path = get_exe_path(all_path, cmd_argv[0]);
	safe_close(pipe_fd[1]);
	safe_dup2(pipe_fd[0], STDIN_FILENO);
	safe_close(pipe_fd[0]);
	safe_dup2(outfile_fd, STDOUT_FILENO);
	safe_close(outfile_fd);
	execve(cmd_path, cmd_argv, env.envp);
	perror("Error on second Process");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	int		pipe_fd[2];
	pid_t	childs[2];
	int		status;

	if (argc != 5)
		exit(EXIT_FAILURE);
	set_env(&env, argc, argv, envp);
	if (pipe(pipe_fd) == -1)
		perror_exit("pipex: Error while creating pipe");
	childs[0] = fork();
	if (childs[0] == -1)
		perror_exit("pipex: Error while creating first child");
	if (childs[0] == 0)
		first_process(env, pipe_fd);
	childs[1] = fork();
	if (childs[1] == -1)
		perror_exit("pipex: Error while creating second child");
	if (childs[1] == 0)
		second_process(env, pipe_fd);
	safe_waitpid(childs[0], &status, WNOHANG);
	safe_waitpid(childs[0], &status, WNOHANG);
	while (wait(NULL) != -1)
		break ;
	return (status / 256);
}
