/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:43:28 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/04 14:59:29 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ALLOC_ERROR 1
# define PATH_NOT_FOUND 2

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fds
{
	int		in;
	int		out;
}			t_fds;

typedef struct s_data
{
	int		pids[2];
	int		pipe[2];
	char	**cmd;
	char	*cmd_path;
	t_fds	fds;
	int		curr_input;
	int		curr_output;
	int		nb_cmds;
	char	**paths;
}			t_data;

void		exit_error(int error_status, t_data *data);
void		free_str_tab(char **tab);
void		init_data(t_data *d, char **av, int ac, char **env);
void		msg(char *str1, char *str2, int fd);
void		secure_fork(int *pid, t_data *d);
void		free_and_close_fds_data(t_data *d);
void		close_fds(t_data *d);
char		**empty_split(void);

#endif