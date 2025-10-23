/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:21:14 by aphyo-ht          #+#    #+#             */
/*   Updated: 2025/10/23 17:53:38 by aphyo-ht         ###   ########.fr       */
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

typedef struct s_env
{
	int argc;
	char **argv;
	char **envp;
	
} t_env;


#endif