
#include "pipex.h"
#include "libft.h"

// char *get_cmd(char *path, char *cmd)
// {
// 	char *tmp;
// 	char *
// }


/// @brief all path return str pointer but it is pointing to the envp address.
/// @param envp 
/// @return return if there is point variable exit failure if there is no path
char *get_all_path(char **envp)
{
	char *all_path;

	all_path = NULL;
	while(*envp)
	{
		if(ft_startswith(*envp, "PATH="))
		{
			all_path = (*envp) + 5;
			break;
		}
		envp++;
	}
	if(!all_path || !*all_path)
	{
		errno = ENOENT;
		perror("PATH Environment variable is not set");
		exit(EXIT_FAILURE);
	}
	return all_path;
}

char *construct_file_path(char *path, char *cmd)
{
	char *file_path;
	char *tmp;

	tmp = ft_strjoin(path, "/");
	if(!tmp)
		return (NULL);
	file_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if(!file_path)
		return (NULL);

	return (file_path);
}

char *get_exe_path(char **envp, char *cmd)
{
	char *all_path;
	char **path_arr;
	char **path_arr_ff;
	char *exe_path;
	
	all_path = get_all_path(envp);
	path_arr = ft_split(all_path, ':');
	path_arr_ff = path_arr;
	
	while(*path_arr)
	{
		exe_path = construct_file_path(*path_arr, cmd);
		if(!exe_path || !access(exe_path, F_OK | X_OK))
			break;
		free(exe_path);
		exe_path = NULL;
		path_arr++;
	}
	ft_sarr_free(path_arr_ff);
	if(!exe_path)
	{
		perror("Getting EXE PATH:");
		exit(EXIT_FAILURE);
	}
	return (exe_path);
}
