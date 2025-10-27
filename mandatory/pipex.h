/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:14 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/27 10:32:56 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// For fork & pipe
// # include <sys/types.h>
// # include <unistd.h>

// // for perror
// # include <errno.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <sys/wait.h>
# include <sys/types.h>

typedef struct s_env
{
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	childs[2];
	int		pipe_fd[2];
	int		last_status;

}			t_env;

char		*get_all_path(char **envp);
char		*construct_file_path(char *path, char *cmd);
char		*get_exe_path(char *all_path, char *cmd, char **cmd_argv, int close_on_error);
void		set_env(t_env *env, int argc, char **argv, char **envp);
void		perror_exit(char *s);

void		safe_dup2(int old, int new, int exit_on_fail);
void		safe_close(int fd, int exit_on_fail);
void		safe_waitpid(pid_t pid, int *status, int options);

#endif