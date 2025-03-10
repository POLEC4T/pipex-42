/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:03:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 11:21:51 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	msg_exit_here_doc(char *text, t_data *d)
{
	msg(text, ": ", strerror(errno), STDERR_FILENO);
	exit_process(EXIT_FAILURE, d);
}

/**
 * @brief process the here_doc feature
 * @details read the input from the user until the limiter is found
 * and write it to a file
 */
void	process_here_doc(t_data *d, char *limiter)
{
	int		i;
	char	*str;
	int		hd_fd;

	str = NULL;
	hd_fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == -1)
		msg_exit_here_doc(HEREDOC_FILENAME, d);
	while (1)
	{
		if (str)
			free(str);
		i = -1;
		while (++i < d->nb_cmds - 1)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "heredoc> ", 9);
		str = get_next_line(STDIN_FILENO);
		str[ft_strlen(str) - 1] = '\0';
		if (ft_strncmp(str, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		ft_putendl_fd(str, hd_fd);
	}
	close(hd_fd);
	free(str);
}
