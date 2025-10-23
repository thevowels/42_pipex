/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:39 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/23 20:45:21 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>


char *get_path(char **envp)
{
	
}

void set_requirements(t_env env, char *cmd)
{
	// char *tmp_path;
	// char *cmd_path;
	// char **cmd_argv;
	

	// if(0)
	// {
	// 	errno = EINVAL;
	// 	perror("Error while parsing cmd");
	// 	exit(EXIT_FAILURE);	
	// }
}

void	first_process(t_env env, int(pipe_fd)[2])
{
	char	*path;
	char	*argv[] = {"sleep", "10", NULL};
	char	**argv;
	
	int		file_fd;

	file_fd = open("pipex.c", O_RDONLY);
	path = "/usr/bin/sleep";
	// duplicating file_fd to STDIN_FILENO
	dup2(file_fd, STDIN_FILENO);
	// Now we've two fd pointing to input file
	// We've to close the unused one.
	close(file_fd);
	// Now, we are writing into the STDOUT_FILENO.
	// when we call execve it will write output to either
	// STDOUT_FILENO or STDERR_FILENO.
	// We've to make that STDOUT_FILENO point into our pipe's write end
	dup2(pipe_fd[1], STDOUT_FILENO);
	// Now we've two fd pointing to write end of pipe.
	// We've to close unused one. as its necessary to make sure the pipe closed
	// When our execve finished or crashed.
	close(pipe_fd[1]);
	// This child process will take the input from the file so we don't use
	// the read end of pipe. we've to close that too.
	close(pipe_fd[0]);
	execve(path, argv, env.envp);
	perror("Error on first child");
	exit(EXIT_FAILURE);
}

void	second_process(t_env env, int(pipe_fd)[2])
{
	char	*path;
	char	*argv[] = {"wc", "-l", NULL};
	int		outfile_fd;

	outfile_fd = open("output", O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	path = "/usr/bin/wc";

	// We are gonna output to file and not gonna use the write end of pipe
	close(pipe_fd[1]);
	
	// We are gonna read the input from the pipe.
	// so we've to dup2 the pipe's read end to STD_FILEIN0
	dup2(pipe_fd[0], STDIN_FILENO);
	// Now we've two fd pointing to the read end of pipe.
	// So, we've to close the unsed one.
	close(pipe_fd[0]);

	// We want the output to be in the output file.
	// So, we've to swap the pointing of STDOUT_FILENO into outfile.
	dup2(outfile_fd, STDOUT_FILENO);

	// Now we've to pointing to same one.
	// We've to close.
	close(outfile_fd);
	execve(path,argv, env.envp);
	perror("Error on second Process");
	exit(EXIT_FAILURE);
	
}

void	set_env(t_env *env, int argc, char **argv, char **envp)
{
	env->argc = argc;
	env->argv = argv;
	env->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_env env;
	int pipe_fd[2];
	pid_t childs[2];
	int wstatus[2];

	set_env(&env, argc, argv, envp);
	childs[0] = 0;
	childs[1] = 0;
	if (pipe(pipe_fd) == -1)
	{
		perror("main: Error while creating pipe ");
		exit(EXIT_FAILURE);
	}
	printf("Pipe write end fd: %d\n", pipe_fd[0]);
	printf("Pipe read end fd : %d\n", pipe_fd[1]);
	childs[0] = fork();
	if (childs[0] == -1)
	{
		perror("main: Error while creating first child ");
		exit(EXIT_FAILURE);
	}
	if (childs[0] == 0)
	{
		// Child process
		// Execute
		first_process(env, pipe_fd);
	}
	childs[1] = fork();
	if (childs[1] == -1)
	{
		perror("main: Error while creating first child ");
	}
	if (childs[1] == 0)
	{
		// Child 2
		// Execute
		second_process(env, pipe_fd);
		perror("Error on Last Child");
	}
	waitpid(childs[0], wstatus, WNOHANG);
	// sleep(3);
}