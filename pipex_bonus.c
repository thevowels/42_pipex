/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:01:12 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/20 03:36:08 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void prog_end(char *err_message)
{
	printf("%s\n", err_message);
	exit(EXIT_FAILURE);
}

void check_IO_perms(char *infile)
{
	if(access(infile, F_OK | R_OK) == 0)
	{
		printf("File exists.\n");
	}
	else
	{
		prog_end("Problem reading input file.");
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t child_pids[argc];
	int	i;

	
	char *cat_path = "/usr/bin/cat";
	char *cat_argv[] = {"cat", "abc", NULL};

	
	if(argc != 5)
		prog_end("Usage: ./pipex file1 cmd1 cmd2 file2");
	check_IO_perms(argv[1]);
	
	i = 0;
	while(i < argc - 3)
	{
		child_pids[i] = fork();
		if(child_pids[i] == 0)
		{
			printf("Child process %i\n", i);
			exit(EXIT_SUCCESS);
		}
		else if(child_pids[i] > 0)
		{
			// printf("Parent process\n");
		}
		else
		{
			printf("Error while forking\n");
		}
		i++;
	}
	
	
	printf("Executed\n");
	return (0);
}
