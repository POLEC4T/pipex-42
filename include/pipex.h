/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miloniemaz <mniemaz@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:43:28 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/01 04:29:24 by miloniemaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ALLOC_ERROR 1
# define PATH_NOT_FOUND 2

# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fds
{
    int in;
    int out;
} t_fds;

typedef struct s_data
{
    int		pids[2];
    int		pipe[2];
    char	**cmd;
    char	*cmd_path;
    t_fds	fds;
    int		curr_input;
    int		curr_output;
    char	**paths;
} t_data;


void	free_str_tab(char **tab);
void	init_data(t_data *d, char *infile, char *outfile, char **env);
void	msg(char *str1, char *str2, int fd);
void	secure_fork(int *pid);

#endif