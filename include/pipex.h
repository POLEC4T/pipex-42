/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:43:28 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 13:31:40 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1
# ifndef BONUS
#  define BONUS 0
# endif
# define BONUS_USAGE_1 "./pipex infile cmd1 cmd2 ... cmdn outfile"
# define BONUS_USAGE_2 "./pipex is_here_doc LIMITER cmd1 cmd2 ... cmdn outfile"
# define MANDATORY_USAGE "./pipex infile cmd1 cmd2 outfile"
# define HEREDOC_FILENAME ".build/.here_doc_tmp"
# define ERR_FILE_NAME ".build/.err_file_"

# include "../libft/get_next_line.h"
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
	int		**pipes;
	int		*pids;
	int		nb_cmds;
	int		is_here_doc;
	char	**cmd;
	char	**err_file_names;
	char	**paths;
	char	*cmd_path;
	t_fds	fds;
}			t_data;

// inits
void		init_data(t_data *d, char **av, int ac, char **env);
void		set_err_file_names(t_data *d);

// exit
void		exit_process(int error_status, t_data *data);

// output
void		msg(char *str1, char *str2, char *str3, int fd);
void		display_errors(t_data *d);

// close
void		close_fds_and_pipes(t_data *d);
void		close_fds_in_out(t_data *d);
void		close_pipes(t_data *d);
void		my_close(int *fd);

// env check
char		*get_cmd_path(t_data *d, char *cmd);
char		**get_paths(char **env);

// utils
void		secure_fork(int *pid, t_data *d);
char		**empty_split(void);
void		redirect(int input, int output, t_data *d);

// children
void		process_child(t_data *d, char **av, char **env, int i_cmds);

// parent
void		start_children(t_data *d, char **av, char **env);
int			wait_children(t_data *d);

// here_doc
void		process_here_doc(t_data *d, char *limiter);

#endif