/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:14 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/25 04:17:17 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// For fork & pipe
#include <sys/types.h>
#include <unistd.h>


// for perror
#include <stdio.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <errno.h>

typedef struct s_env
{
	int argc;
	char **argv;
	char **envp;
	
} t_env;

char	**ft_split(char *str, char c);
int	ft_startswith(char *str, char *start);
char *get_all_path(char **envp);
char *construct_file_path(char *path, char *cmd);
char *get_exe_path(char **envp, char *cmd);

#endif