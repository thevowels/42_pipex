/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:09:21 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/27 12:23:23 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdio.h>

char	*get_all_path(char **envp)
{
	char	*all_path;

	all_path = NULL;
	while (*envp)
	{
		if (ft_startswith(*envp, "PATH="))
		{
			all_path = (*envp) + 5;
			break ;
		}
		envp++;
	}
	if (!all_path || !*all_path)
	{
		errno = ENOENT;
		perror("command not found");
		exit(127);
	}
	return (all_path);
}

char	*construct_file_path(char *path, char *cmd)
{
	char	*file_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	file_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!file_path)
		return (NULL);
	return (file_path);
}

/**
 * @brief Get the exe path
 * @param all_path
 * @param cmd
 * @return char*
 *
 * @note now its ok as we want to find only shell commands
 * @note if its not just shell commands to execute , we should also search for
 *		the command in current directory. at that time, we have to check access
		with just the filename without constructing path for first time.
 */
char	*get_exe_path(char *all_path, char **cmd_argv, int close_on_error)
{
	char	**path_arr;
	char	**path_arr_ff;
	char	*exe_path;

	path_arr = ft_split(all_path, ':');
	path_arr_ff = path_arr;
	while (*path_arr)
	{
		exe_path = construct_file_path(*path_arr, cmd_argv[0]);
		if (!exe_path || !access(exe_path, F_OK | X_OK))
			break ;
		free(exe_path);
		exe_path = NULL;
		path_arr++;
	}
	ft_sarr_free(path_arr_ff);
	if (!exe_path)
	{
		safe_close(close_on_error, 1);
		ft_sarr_free(cmd_argv);
		perror("command not found");
		exit(127);
	}
	return (exe_path);
}
