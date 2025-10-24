/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 06:28:13 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/25 06:30:53 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

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
		perror("PATH Environment variable is not set");
		return (NULL);
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

char	*get_exe_path(char *all_path, char *cmd)
{
	char	**path_arr;
	char	**path_arr_ff;
	char	*exe_path;

	path_arr = ft_split(all_path, ':');
	path_arr_ff = path_arr;
	while (*path_arr)
	{
		exe_path = construct_file_path(*path_arr, cmd);
		if (!exe_path || !access(exe_path, F_OK | X_OK))
			break ;
		free(exe_path);
		exe_path = NULL;
		path_arr++;
	}
	ft_sarr_free(path_arr_ff);
	if (!exe_path)
	{
		perror("Getting EXE PATH:");
		exit(EXIT_FAILURE);
	}
	return (exe_path);
}
